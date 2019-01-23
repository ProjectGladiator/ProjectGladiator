// Fill out your copyright notice in the Description page of Project Settings.

#include "Worm.h"
//클라 헤더
#include "UObject/ConstructorHelpers.h" // 경로 탐색
#include "Components/SkeletalMeshComponent.h" //스켈레탈 메쉬 헤더
#include "Animation/AnimBlueprint.h" // 애님 블루프린트
#include "WormAnimInstance.h"
#include "WormAIController.h"
#include "Client/MyCharacter/MyCharacter.h"
#include "Client/Monster/Manager/DistanceCheckAIManager.h"
#include "Kismet/GameplayStatics.h"
#include "Navigation/PathFollowingComponent.h"
#include "Runtime/AIModule/Classes/Blueprint/AIBlueprintHelperLibrary.h"
#include "GameFrameWork/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

//서버 헤더

AWorm::AWorm()
{
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AWormAIController::StaticClass();

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>SK_Worm(TEXT("SkeletalMesh'/Game/Assets/Monster/InfinityBladeAdversaries/Enemy/Enemy_Clot_Worm/SK_Enemy_Clot_Worm.SK_Enemy_Clot_Worm'"));

	if (SK_Worm.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_Worm.Object);
	}

	// 애님블루프린트 찾아 메쉬에 세팅
	static ConstructorHelpers::FObjectFinder<UClass>ABP_Worm(TEXT("AnimBlueprint'/Game/Blueprints/Monster/Worm/Blueprints/ABP_Worm.ABP_Worm_C'"));

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

	GetCharacterMovement()->MaxWalkSpeed = 300.0f;

	TargetLimitDistance = 100.0f;

	DeathFlag = false;

	CurrentState = EWormState::Idle;
	MaxHP = 100.0f;
}

void AWorm::BeginPlay()
{
	Super::BeginPlay();

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
	float Distance = DistanceCheckAIManager->DistanceCalculate(this, Target);

	TArray<AActor*>IgonreActors;
	IgonreActors.Add(this);
	FHitResult HitResult;
	FVector TraceStart;
	FVector TraceEnd;
	TArray<TEnumAsByte<EObjectTypeQuery>>ObjectTypes;

	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_PhysicsBody));

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
			EPathFollowingRequestResult::Type GoalResult = DistanceCheckAIManager->TargetChase(WormAIController, Target, TargetLimitDistance);

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
			TraceStart = GetActorLocation();
			TraceEnd = TraceStart + (GetActorForwardVector()*9000.0f);
			bool Result = UKismetSystemLibrary::LineTraceSingleForObjects(
				GetWorld(),
				TraceStart,
				TraceEnd,
				ObjectTypes,
				true,
				IgonreActors,
				EDrawDebugTrace::ForDuration,
				HitResult,
				true,
				FLinearColor::Red);

			WormAnimInstance->PlayAttackMontage();

			UGameplayStatics::ApplyRadialDamage(GetWorld(),
				10.0f,
				HitResult.ImpactPoint,
				300.0f,
				nullptr,
				IgonreActors,
				this,
				UGameplayStatics::GetPlayerController(GetWorld(), 0),
				false,
				ECollisionChannel::ECC_WorldStatic
			);

			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
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
	GLog->Log(FString::Printf(TEXT("죽음")));
	DeathFlag = true;
}
