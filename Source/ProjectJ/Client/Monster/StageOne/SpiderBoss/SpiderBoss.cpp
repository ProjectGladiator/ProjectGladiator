// Fill out your copyright notice in the Description page of Project Settings.

#include "SpiderBoss.h"
//클라 헤더
#include "UObject/ConstructorHelpers.h" //경로 탐색 헤더
#include "Components/SkeletalMeshComponent.h" //스켈레탈 메쉬 헤더
#include "SpiderBossAIController.h" //거미 보스 AI 컨트롤러 헤더
#include "Client/Monster/Manager/AIManager.h" //AI담당 컴포넌트 헤더
#include "SpiderBossAnimInstance.h" //거미 보스 애님 인스턴스 헤더
#include "GameFrameWork/CharacterMovementComponent.h" //캐릭터 속도 관련 헤더
#include "Kismet/KismetMathLibrary.h" //수학 관련 헤더
#include "Client/MyCharacter/PC/MyCharacter.h" //캐릭터들 부모

//서버 헤더

ASpiderBoss::ASpiderBoss()
{
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = ASpiderBossAIController::StaticClass();

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>SK_SpiderBoss(TEXT("SkeletalMesh'/Game/Assets/Monster/InfinityBladeAdversaries/Enemy/Enemy_Greater_Spider_Boss/SK_Greater_Spider_Boss.SK_Greater_Spider_Boss'"));

	if (SK_SpiderBoss.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_SpiderBoss.Object);
	}

	// 애님블루프린트 찾아 메쉬에 세팅
	static ConstructorHelpers::FObjectFinder<UClass>ABP_BossSpider(TEXT("AnimBlueprint'/Game/Blueprints/Monster/StageOne/SpiderBoss/Blueprints/ABP_SpiderBoss.ABP_SpiderBoss_C'"));

	if (ABP_BossSpider.Succeeded())  //찾는것에 성공햇으면
	{
		UClass* SpiderBossAnimBlueprint = ABP_BossSpider.Object; //오브젝트를 구하고

		if (SpiderBossAnimBlueprint)
		{
			//메쉬에 사용할 애니메이션을 블루프린트로 정한다.
			GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
			GetMesh()->SetAnimInstanceClass(SpiderBossAnimBlueprint);  //찾은 애니메이션블루프린트를 넣어준다.
		}
	}

	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	GetCharacterMovement()->MaxWalkSpeed = 500.0f;

	DeathFlag = false;
	MaxHP = 100;
}

void ASpiderBoss::BeginPlay()
{
	Super::BeginPlay();

	//init();

	TargetLimitDistance = 150.0f;
	AttackInfo.SetAttackInfo(150.0f, 80.0f, 100.0f);

	CurrentState = ESpiderBossState::Idle;

	SpiderBossAnimInstance = Cast<USpiderBossAnimInstance>(GetMesh()->GetAnimInstance());

	if (SpiderBossAnimInstance)
	{
		SpiderBossAnimInstance->OnMonsterAttackHit.AddDynamic(this, &ASpiderBoss::AttackHit);
		SpiderBossAnimInstance->OnMonsterComboSave.AddDynamic(this, &ASpiderBoss::OnComboSave);
		SpiderBossAnimInstance->OnMonsterAttackEnded.AddDynamic(this, &ASpiderBoss::OnMonsterAttackEnded);
		//기본 공격 스폰 차지 어택 정하는 부분이 없음 지금 오직 기본 공격만 함
		SpiderBossAnimInstance->OnDeath.AddDynamic(this, &ASpiderBoss::Death);
	}

	Target = AIManager->GetTarget();

	StartLocation = GetActorLocation();
}

void ASpiderBoss::Tick(float DeltaTime)
{
	if (Target)
	{
		float Distance = AIManager->DistanceCalculate(this, Target);

		switch (CurrentState)
		{
		case ESpiderBossState::Ready:
			if(DeathFlag)
			{
				//init으로 초기화
			}
			break;
		case ESpiderBossState::Idle:
			if (!DeathFlag)
			{
				CurrentState = ESpiderBossState::Chase;
			}
			break;
		case ESpiderBossState::Chase:
		{
			EPathFollowingRequestResult::Type GoalResult = AIManager->TargetChase(SpiderBossAIController, Target, TargetLimitDistance);

			switch (GoalResult)
			{
			case EPathFollowingRequestResult::AlreadyAtGoal:
				CurrentState = ESpiderBossState::Attack;
				CurrentAttackState = ESpiderBossAttackState::DefaultAttack;
				break;
			case EPathFollowingRequestResult::Failed:
				//GLog->Log(FString::Printf(TEXT("요청 실패")));
				break;
			case EPathFollowingRequestResult::RequestSuccessful:
				//GLog->Log(FString::Printf(TEXT("성공")));
				CurrentState = ESpiderBossState::Chase;
				break;
			}
		}
			break;
		case ESpiderBossState::Attack:
		{
			switch (CurrentAttackState)
			{
			case ESpiderBossAttackState::DefaultAttack:
				if (IsAttack)
				{
					IsCombo = true;
				}
				else
				{
					IsAttack = true;

					if (SpiderBossAnimInstance)
					{
						SpiderBossAnimInstance->PlayAttackMontage(0);
						CurrentCombo += 1;
						SpiderBossAnimInstance->JumpAttackMontageSection(0, CurrentCombo);
					}
				}
				break;
			case ESpiderBossAttackState::ChargeAttack:
				if (!IsAttack)
				{
					IsAttack = true;
					SpiderBossAnimInstance->PlayAttackMontage(1);
				}
				break;
			case ESpiderBossAttackState::Summon:
				break;
			}

			FRotator LooAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Target->GetActorLocation());
			SetActorRotation(LooAtRotation);

			if (Distance > TargetLimitDistance * 2.0f)
			{
				IsCombo = false;
				CurrentState = ESpiderBossState::Chase;
			}
		}
			break;
		case ESpiderBossState::Death:
			DeathInVisibleValue += 0.01;
			GetMesh()->SetScalarParameterValueOnMaterials(TEXT("Amount"), DeathInVisibleValue);

			//GLog->Log(FString::Printf(TEXT("몬스터 사망")));
			if (DeathInVisibleValue == 0)
			{
				GLog->Log(FString::Printf(TEXT("재배치 준비")));
				//We Not Use Destroy Function
				//Destroy();

				//bisActive  true -> false 재배치 준비를 위해.
				bisActive = false;

				//몬스터 상태는 Ready로 변경
				CurrentState = ESpiderBossState::Ready;
				DeathFlag = true;
			}
			break;
		}
	}
	else
	{
		GLog->Log(FString::Printf(TEXT("거미 보스 : 타겟이 존재하지 않음")));
	}
}

void ASpiderBoss::Init(MONSTER_CODE _MyMonsterCode, int _MyMonsterNum)
{
	Super::Init(_MyMonsterCode, _MyMonsterNum);
	CurrentState = ESpiderBossState::Idle;

	CurrentHP = MaxHP;
}

void ASpiderBoss::SetAIController(AMonsterAIController * NewAIController)
{
	SpiderBossAIController = Cast<ASpiderBossAIController>(NewAIController);
}

ESpiderBossState ASpiderBoss::GetCurrentState()
{
	return CurrentState;
}

void ASpiderBoss::AttackHit()
{
	AIManager->AttackMeleeHitCreate(this, AttackInfo, false);
}

void ASpiderBoss::OnComboSave()
{
	GLog->Log(FString::Printf(TEXT("거미 보스 콤보 공격 시작")));
	if (IsCombo)
	{
		IsCombo = false;

		if (SpiderBossAnimInstance)
		{
			SpiderBossAnimInstance->PlayAttackMontage(0);
			CurrentCombo += 1;
			SpiderBossAnimInstance->JumpAttackMontageSection(0, CurrentCombo);
		}
	}
}

void ASpiderBoss::OnMonsterAttackEnded()
{
	Super::OnMonsterAttackEnded();
}

void ASpiderBoss::Death()
{
	//GLog->Log(FString::Printf(TEXT("거미 보스 사망")));
	Super::Death();
	CurrentState = ESpiderBossState::Death;
}

float ASpiderBoss::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	CurrentHP -= DamageAmount;

	/*if (CurrentHP <= 0)
	{
		SetActorEnableCollision(false);
		CurrentHP = 0;
		CurrentState = ESpiderBossState::Death;
	}*/
	return DamageAmount;
}
