// Fill out your copyright notice in the Description page of Project Settings.

#include "Worm.h"
//클라 헤더
#include "UObject/ConstructorHelpers.h" // 경로 탐색
#include "Components/SkeletalMeshComponent.h" //스켈레탈 메쉬 헤더
#include "Animation/AnimBlueprint.h" // 애님 블루프린트
#include "WormAnimInstance.h" //벌레 애님인스턴스 헤더
#include "WormAIController.h" //벌레 AI 컨트롤러 헤더
#include "Client/MyCharacter/MyCharacter.h" //캐릭터들 부모 헤더
#include "Client/Monster/Manager/AIManager.h" //AI담당 컴포넌트 헤더
#include "Kismet/GameplayStatics.h" //각종 유틸 헤더
#include "Navigation/PathFollowingComponent.h" //AI관련 헤더
#include "Runtime/AIModule/Classes/Blueprint/AIBlueprintHelperLibrary.h"
#include "GameFrameWork/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

//서버 헤더

AWorm::AWorm()
{
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AWormAIController::StaticClass();

	//에디터 상에서 벌레 스켈레탈메쉬를 찾아서 SK_Worm에 넣는다.
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>SK_Worm(TEXT("SkeletalMesh'/Game/Assets/Monster/InfinityBladeAdversaries/Enemy/Enemy_Clot_Worm/SK_Enemy_Clot_Worm.SK_Enemy_Clot_Worm'"));

	//찾는것에 성공하면
	if (SK_Worm.Succeeded())
	{
		//찾은 스켈레탈 메쉬를 적용한다.
		GetMesh()->SetSkeletalMesh(SK_Worm.Object);
	}

	// 애님블루프린트 찾아 메쉬에 세팅
	static ConstructorHelpers::FObjectFinder<UClass>ABP_Worm(TEXT("AnimBlueprint'/Game/Blueprints/Monster/StageOne/Worm/Blueprints/ABP_Worm.ABP_Worm_C'"));

	if (ABP_Worm.Succeeded())  //찾는것에 성공햇으면
	{
		UClass* WormAnimBlueprint = ABP_Worm.Object; //오브젝트를 구하고

		if (WormAnimBlueprint)
		{
			//메쉬에 사용할 애니메이션을 블루프린트로 정한다.
			GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
			GetMesh()->SetAnimInstanceClass(WormAnimBlueprint);  //찾은 애니메이션블루프린트를 넣어준다.
		}
	}

	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));

	GetCharacterMovement()->MaxWalkSpeed = 320.0f;

	DeathFlag = false;

	CurrentState = EWormState::Idle;
}

void AWorm::BeginPlay()
{
	Super::BeginPlay();

	MaxHP = 100.0f;
	CurrentHP = MaxHP;

	TargetLimitDistance = 100.0f;
	AttackInfo.SetAttackInfo(0, 0, 300.0f);
	Target = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	WormAnimInstance = Cast<UWormAnimInstance>(GetMesh()->GetAnimInstance());

	if (WormAnimInstance)
	{
		GLog->Log(FString::Printf(TEXT("죽음 델리게이트 함수 연결")));
		WormAnimInstance->OnDeath.AddDynamic(this, &AWorm::Death);
	}
}

void AWorm::Tick(float DeltaTime)
{
	float Distance = AIManager->DistanceCalculate(this, Target);

	if (WormAIController)
	{
		switch (CurrentState)
		{
		case EWormState::Idle:
			if (Target)
			{
				CurrentState = EWormState::Chase;
			}
			break;
		case EWormState::Chase:
		{
			EPathFollowingRequestResult::Type GoalResult = AIManager->TargetChase(WormAIController, Target, TargetLimitDistance);

			switch (GoalResult)
			{
			case EPathFollowingRequestResult::AlreadyAtGoal:
				CurrentState = EWormState::Attack;
				break;
			case EPathFollowingRequestResult::Failed:
				GLog->Log(FString::Printf(TEXT("요청 실패")));
				break;
			case EPathFollowingRequestResult::RequestSuccessful:
				break;
			}
		}
		break;
		case EWormState::Attack:
		{
			FHitResult HitResult=AIManager->AttackMeleeHitCreate(this, AttackInfo,true);
			WormAnimInstance->PlayAttackMontage(0);

			CurrentState = EWormState::Death;
		}
		break;
		case EWormState::Death:
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
		GLog->Log(FString::Printf(TEXT("AI 컨트롤러가 없음")));
	}
}

void AWorm::SetAIController(AMonsterAIController * NewAIController)
{
	WormAIController = Cast<AWormAIController>(NewAIController);
}

void AWorm::Death()
{
	DeathFlag = true;
}

float AWorm::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	CurrentHP -= DamageAmount;

	if (CurrentHP <= 0)
	{
		SetActorEnableCollision(false);
		CurrentHP = 0;
		CurrentState = EWormState::Death;
		WormAnimInstance->PlayAttackMontage(0);
	}
	return DamageAmount;
}
