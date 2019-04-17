
// Fill out your copyright notice in the Description page of Project Settings.

#include "Bear.h"
//클라 헤더
#include "UObject/ConstructorHelpers.h" // 경로 탐색 헤더
#include "BearAIController.h" //곰 AI 컨트롤러 헤더
#include "Components/SkeletalMeshComponent.h" //스켈레탈 메쉬 헤더
#include "Kismet/GameplayStatics.h" //각종 유틸 헤더
#include "Client/Monster/Manager/AIManager.h" //AI담당 컴포넌트 헤더
#include "Client/MyCharacter/PC/MyCharacter.h" //캐릭터들 부모
#include "GameFrameWork/CharacterMovementComponent.h" //캐릭터 속도 관련 헤더
#include "BearAnimInstance.h" //곰 애님 인스턴스 헤더
#include "Kismet/KismetSystemLibrary.h"  //라인 트레이스 헤더 관련 헤더
#include "Kismet/KismetMathLibrary.h" //수학 관련 헤더
#include "Components/CapsuleComponent.h" //캡슐 컴포넌트 헤더

//서버 헤더

ABear::ABear()
{
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = ABearAIController::StaticClass();

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>SK_Bear(TEXT("SkeletalMesh'/Game/Assets/Monster/InfinityBladeAdversaries/Enemy/Enemy_Bear/Enemy_Bear.Enemy_Bear'"));

	if (SK_Bear.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_Bear.Object);
	}

	// 애님블루프린트 찾아 메쉬에 세팅
	static ConstructorHelpers::FObjectFinder<UClass>ABP_Bear(TEXT("AnimBlueprint'/Game/Blueprints/Monster/StageOne/Bear/Blueprints/ABP_CompleteBear.ABP_CompleteBear_C'"));

	if (ABP_Bear.Succeeded())  //찾는것에 성공햇으면
	{
		UClass* BearAnimBlueprint = ABP_Bear.Object; //오브젝트를 구하고

		if (BearAnimBlueprint)
		{
			//메쉬에 사용할 애니메이션을 블루프린트로 정한다.
			GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
			GetMesh()->SetAnimInstanceClass(BearAnimBlueprint);  //찾은 애니메이션블루프린트를 넣어준다.
		}
	}

	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	GetCharacterMovement()->MaxWalkSpeed = 510.0f;
}

void ABear::BeginPlay()
{
	Super::BeginPlay();

	//MaxHP = 100.0f;
	//CurrentHP = MaxHP;
	init();

	TargetLimitDistance = 150.0f;
	AttackInfo.SetAttackInfo(150.0f, 80.0f, 120.0f);

	CurrentState = EBearState::Idle;

	Target = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	BearAnimInstance = Cast<UBearAnimInstance>(GetMesh()->GetAnimInstance());

	if (BearAnimInstance)
	{
		BearAnimInstance->OnMonsterAttackHit.AddDynamic(this, &ABear::AttackHit);
		BearAnimInstance->OnMonsterComboSave.AddDynamic(this, &ABear::OnComboSave);
		BearAnimInstance->OnMonsterAttackEnded.AddDynamic(this, &ABear::OnMonsterAttackEnded);
		BearAnimInstance->OnDeath.AddDynamic(this, &ABear::Death);
	}
}

void ABear::Tick(float DeltaTime)
{
	if (Target)
	{
		float Distance = AIManager->DistanceCalculate(this, Target);
	
		switch (CurrentState)
		{
		case EBearState::Ready:
			break;
		case EBearState::Idle:
			CurrentState = EBearState::Chase;
			break;
		case EBearState::Chase:
		{
			EPathFollowingRequestResult::Type GoalResult = AIManager->TargetChase(BearAIController, Target, TargetLimitDistance);

			switch (GoalResult)
			{
			case EPathFollowingRequestResult::AlreadyAtGoal:
				//GLog->Log(FString::Printf(TEXT("골에 도착")));
				CurrentState = EBearState::Attack;
				break;
			case EPathFollowingRequestResult::Failed:
				//GLog->Log(FString::Printf(TEXT("요청 실패")));
				break;
			case EPathFollowingRequestResult::RequestSuccessful:
				//GLog->Log(FString::Printf(TEXT("성공")));
				CurrentState = EBearState::Chase;
				break;
			}

		}
		break;
		case EBearState::Attack:
		{
			if (IsAttack)
			{
				IsCombo = true;
			}
			else
			{
				GLog->Log(FString::Printf(TEXT("곰 처음 공격")));
				IsAttack = true;

				if (BearAnimInstance)
				{
					BearAnimInstance->PlayAttackMontage(0);
					CurrentCombo += 1;
					BearAnimInstance->JumpAttackMontageSection(0,CurrentCombo);
				}
			}

			FRotator BearRotator = GetActorRotation();
			FRotator LooAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Target->GetActorLocation());

			//곰 에서 바라본 캐릭터의 로테이션
			FRotator ToCharacterRotator = UKismetMathLibrary::NormalizedDeltaRotator(LooAtRotation, BearRotator);

			//GLog->Log(FString::Printf(TEXT("ToCharacterRotator Yaw :%f\n"), ToCharacterRotator.Yaw));

			//GLog->Log(FString::Printf(TEXT("Pitch : %f Yaw : %f"), LooAtRotation.Pitch, LooAtRotation.Yaw));
			SetActorRotation(LooAtRotation);

			if (Distance > TargetLimitDistance*2.0f)
			{
				IsCombo = false;
				CurrentState = EBearState::Chase;
			}
		}
		break;
		case EBearState::Death:
			DeathInVisibleValue += 0.01;
			GetMesh()->SetScalarParameterValueOnMaterials(TEXT("Amount"), DeathInVisibleValue);

			if (DeathFlag)
			{
				//We Not Use Destroy Function
				//Destroy();
				bisActive = false;
				
				Monster_SetActive(this, bisActive);
				DeathFlag = true;
			}
			break;
		}
	}
	else
	{
		GLog->Log(FString::Printf(TEXT("곰 : 타겟이 존재하지 않음")));
	}
}

void ABear::init()
{
	Super::init();
	/*MaxHP = 100.0f;
	CurrentHP = MaxHP;*/
}

void ABear::SetAIController(AMonsterAIController * NewAIController)
{
	BearAIController = Cast<ABearAIController>(NewAIController);
}

EBearState ABear::GetCurrentState()
{
	return CurrentState;
}

void ABear::AttackHit()
{
	AIManager->AttackMeleeHitCreate(this, AttackInfo,false);
}

void ABear::OnMonsterAttackEnded()
{
	Super::OnMonsterAttackEnded();
}

void ABear::OnComboSave()
{
	GLog->Log(FString::Printf(TEXT("곰 콤보 공격 시작")));
	if (IsCombo)
	{
		IsCombo = false;

		if (BearAnimInstance)
		{
			BearAnimInstance->PlayAttackMontage(0);
			CurrentCombo += 1;
			BearAnimInstance->JumpAttackMontageSection(0, CurrentCombo);
		}
	}
}

void ABear::Death()
{
	DeathFlag = true;
}

float ABear::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	CurrentHP -= DamageAmount;

	if (CurrentHP <= 0)
	{
		SetActorEnableCollision(false);
		CurrentHP = 0;
		CurrentState = EBearState::Death;
	}

	return DamageAmount;
}