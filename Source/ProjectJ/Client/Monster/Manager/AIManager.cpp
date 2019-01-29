// Fill out your copyright notice in the Description page of Project Settings.

#include "AIManager.h"
//클라헤더
#include "Client/Monster/Monster.h"
#include "Client/MyCharacter/MyCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Client/Monster/MonsterAIController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/World.h"
//서버헤더

// Sets default values for this component's properties
UAIManager::UAIManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UAIManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAIManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

float UAIManager::DistanceCalculate(AMonster * Monster, AMyCharacter * Target)
{
	if (Monster->IsValidLowLevel() && Target->IsValidLowLevel())
	{
		float Distance = FVector::Distance(Monster->GetActorLocation(), Target->GetActorLocation());

		return Distance;
	}
	else
	{
		return -1;
	}
}

EPathFollowingRequestResult::Type UAIManager::TargetChase(AMonsterAIController * MonsterAIController, AMyCharacter * Target, float & TargetLimitDistance)
{
	EPathFollowingRequestResult::Type GoalResult = EPathFollowingRequestResult::Type::Failed;

	if (MonsterAIController->IsValidLowLevel() && Target->IsValidLowLevel())
	{
		GoalResult = MonsterAIController->MoveToActor(Target, TargetLimitDistance, true, true, true, 0, true);
		return GoalResult;
	}
	else
	{
		return GoalResult;
	}
}

void UAIManager::AttackHitCreate(AMonster * Monster, FMonsterAttackInfo & AttackInfo)
{
	if (Monster->IsValidLowLevel())
	{
		GLog->Log(FString::Printf(TEXT("몬스터 공격중")));
		TArray<TEnumAsByte<EObjectTypeQuery>>ObjectTypes;
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_PhysicsBody));

		TArray<FHitResult> HitResults;

		TArray<AActor*>IgonreActors;
		IgonreActors.Add(Monster);

		FVector TraceStart = Monster->GetActorLocation() + Monster->GetActorForwardVector() * AttackInfo.AttackStartLocation;
		FVector TraceEnd = TraceStart + Monster->GetActorForwardVector() * AttackInfo.AttackEndLocation;

		UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(),
			TraceStart,
			TraceEnd,
			AttackInfo.AttackWidth,
			ObjectTypes,
			false,
			IgonreActors,
			EDrawDebugTrace::ForDuration,
			HitResults,
			true);
	}
}

