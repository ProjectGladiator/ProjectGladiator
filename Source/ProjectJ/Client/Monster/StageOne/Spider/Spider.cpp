// Fill out your copyright notice in the Description page of Project Settings.

#include "Spider.h"
//클라 헤더
#include "UObject/ConstructorHelpers.h" //경로 탐색 헤더
#include "Components/SkeletalMeshComponent.h" //스켈레탈 메쉬 헤더
#include "GameFrameWork/CharacterMovementComponent.h" //캐릭터 속도 관련 헤더
#include "SpiderAIController.h" //거미 AI 컨트롤러 헤더
#include "Client/MyCharacter/MyCharacter.h" //캐릭터들 부모
#include "Kismet/GameplayStatics.h" //각종 유틸 헤더
#include "Client/Monster/Manager/AIManager.h" //AI담당 컴포넌트 헤더
#include "Kismet/KismetMathLibrary.h" //수학 관련 헤더
#include "Components/CapsuleComponent.h" //캡슐 컴포넌트 헤더
#include "SpiderAnimInstance.h" //거미 애님 인스턴스 헤더
#include <time.h>

//서버 헤더

ASpider::ASpider()
{
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = ASpiderAIController::StaticClass();

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>SK_Spider(TEXT("SkeletalMesh'/Game/Assets/Monster/InfinityBladeAdversaries/Enemy/Enemy_Great_Spider/SK_Greater_Spider.SK_Greater_Spider'"));

	if (SK_Spider.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_Spider.Object);
	}

	// 애님블루프린트 찾아 메쉬에 세팅
	static ConstructorHelpers::FObjectFinder<UClass>ABP_Spider(TEXT("AnimBlueprint'/Game/Blueprints/Monster/StageOne/Spider/Blueprins/ABP_Spider.ABP_Spider_C'"));

	if (ABP_Spider.Succeeded())  //찾는것에 성공햇으면
	{
		UClass* SpiderAnimBlueprint = ABP_Spider.Object; //오브젝트를 구하고

		if (SpiderAnimBlueprint)
		{
			//메쉬에 사용할 애니메이션을 블루프린트로 정한다.
			GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
			GetMesh()->SetAnimInstanceClass(SpiderAnimBlueprint);  //찾은 애니메이션블루프린트를 넣어준다.
		}
	}

	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	GetCharacterMovement()->MaxWalkSpeed = 250.0f;
}

void ASpider::BeginPlay()
{
	Super::BeginPlay();

	MaxHP = 100.0f;
	CurrentHP = MaxHP;

	TargetLimitDistance = 150.0f;
	AttackInfo.SetAttackInfo(150.0f, 80.0f, 100.0f);

	CurrentState = ESpiderState::Idle;

	Target = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	SpiderAnimInstance = Cast<USpiderAnimInstance>(GetMesh()->GetAnimInstance());

	if (SpiderAnimInstance)
	{
		SpiderAnimInstance->OnMonsterAttackHit.AddDynamic(this, &ASpider::AttackHit);
		SpiderAnimInstance->OnMonsterAttackEnded.AddDynamic(this, &ASpider::AttackEnded);
		SpiderAnimInstance->OnDeath.AddDynamic(this, &ASpider::Death);
	}
}

void ASpider::Tick(float DeltaTime)
{
	if (Target)
	{
		float Distance = AIManager->DistanceCalculate(this, Target);

		switch (CurrentState)
		{
		case ESpiderState::Idle:
			CurrentState = ESpiderState::Chase;
			break;
		case ESpiderState::Chase:
		{
			EPathFollowingRequestResult::Type GoalResult = AIManager->TargetChase(SpiderAIController, Target, TargetLimitDistance);

			switch (GoalResult)
			{
			case EPathFollowingRequestResult::AlreadyAtGoal:
				RandomAttack();
				break;
			case EPathFollowingRequestResult::Failed:
				//GLog->Log(FString::Printf(TEXT("요청 실패")));
				break;
			case EPathFollowingRequestResult::RequestSuccessful:
				//GLog->Log(FString::Printf(TEXT("성공")));
				CurrentState = ESpiderState::Chase;
				break;
			}
		}
		break;
		case ESpiderState::Attack:
		{
			FRotator LooAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Target->GetActorLocation());
			//GLog->Log(FString::Printf(TEXT("Pitch : %f Yaw : %f"), LooAtRotation.Pitch, LooAtRotation.Yaw));
			SetActorRotation(LooAtRotation);

			if (Distance > TargetLimitDistance * 2.0f)
			{
				CurrentState = ESpiderState::Chase;
			}
			else
			{

			}
		}
		break;
		case ESpiderState::Death:
			DeathInVisibleValue += 0.01;
			GetMesh()->SetScalarParameterValueOnMaterials(TEXT("Amount"), DeathInVisibleValue);

			if (DeathFlag)
			{
				Destroy();
			}
			break;
		}
	}
	else
	{
		GLog->Log(FString::Printf(TEXT("거미 : 타겟이 존재하지 않음")));
	}
}

void ASpider::SetAIController(AMonsterAIController * NewAIController)
{
	SpiderAIController = Cast<ASpiderAIController>(NewAIController);
}

ESpiderState ASpider::GetCurrentState()
{
	return CurrentState;
}

ESpiderAttackState ASpider::GetCurrentAttackState()
{
	return CurrentAttackState;
}

void ASpider::AttackHit()
{
	AIManager->AttackHitCreate(this, AttackInfo);
}

void ASpider::AttackEnded()
{
	RandomAttack();
}

void ASpider::Death()
{
	DeathFlag = true;
}

void ASpider::RandomAttack()
{
	RandomAttackValue = rand() % 10000 / 100.0f;

	GLog->Log(FString::Printf(TEXT("%f"), RandomAttackValue));

	if ( RandomAttackValue >= 60.0f)
	{
		CurrentAttackState = ESpiderAttackState::DefaultAttack;
	}
	else
	{
		CurrentAttackState = ESpiderAttackState::ChargeAttack;
	}
	CurrentState = ESpiderState::Attack;
}

float ASpider::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	CurrentHP -= DamageAmount;

	if (CurrentHP <= 0)
	{
		GetCapsuleComponent()->SetCollisionProfileName("OverlapOnlyPawn");
		CurrentHP = 0;
		CurrentState = ESpiderState::Death;
	}

	return DamageAmount;
}
