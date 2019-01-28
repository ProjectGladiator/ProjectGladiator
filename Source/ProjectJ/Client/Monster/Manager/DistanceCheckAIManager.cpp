// Fill out your copyright notice in the Description page of Project Settings.

#include "DistanceCheckAIManager.h"
//클라헤더
#include "Client/Monster/Monster.h"
#include "Client/MyCharacter/MyCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Client/Monster/MonsterAIController.h"
//서버헤더

// Sets default values for this component's properties
UDistanceCheckAIManager::UDistanceCheckAIManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UDistanceCheckAIManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UDistanceCheckAIManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

float UDistanceCheckAIManager::DistanceCalculate(AMonster * Monster, AMyCharacter* Target)
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

EPathFollowingRequestResult::Type UDistanceCheckAIManager::TargetChase(AMonsterAIController* MonsterAIController, AMyCharacter * Target, float& TargetLimitDistance)
{
	EPathFollowingRequestResult::Type GoalResult= EPathFollowingRequestResult::Type::Failed;

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

