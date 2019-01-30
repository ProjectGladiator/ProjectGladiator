﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "AIManager.h"
//클라헤더
#include "Client/Monster/Monster.h" //몬스터 관련 헤더
#include "Client/MyCharacter/MyCharacter.h" //캐릭터 부모 관련 헤더
#include "Kismet/KismetMathLibrary.h" //수학 관련 헤더
#include "Client/Monster/MonsterAIController.h" //몬스터 AI 컨트롤러 관련 헤더
#include "Kismet/KismetSystemLibrary.h" //라인 트레이스 관련 헤더
#include "Engine/World.h" //월드 관련 헤더 
#include "Components/SkeletalMeshComponent.h" //스켈레탈 메쉬 컴포넌트 헤더

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

void UAIManager::AttackMeleeHitCreate(AMonster * Monster, FMonsterAttackInfo & AttackInfo)
{
	if (Monster->IsValidLowLevel())
	{
		GLog->Log(FString::Printf(TEXT("몬스터 공격중")));
		TArray<TEnumAsByte<EObjectTypeQuery>>ObjectTypes;
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_PhysicsBody));

		TArray<FHitResult> HitResults;

		TArray<AActor*>IgnoreActors;
		IgnoreActors.Add(Monster);

		FVector TraceStart = Monster->GetActorLocation() + Monster->GetActorForwardVector() * AttackInfo.AttackStartLocation;
		FVector TraceEnd = TraceStart + Monster->GetActorForwardVector() * AttackInfo.AttackEndLocation;

		UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(),
			TraceStart,
			TraceEnd,
			AttackInfo.AttackWidth,
			ObjectTypes,
			false,
			IgnoreActors,
			EDrawDebugTrace::ForDuration,
			HitResults,
			true);
	}
}

FHitResult UAIManager::AttackRangeHitCreate(AMonster * Monster, float RangeDistance, const FName& SocketName)
{
	FHitResult HitResult;

	if (Monster->IsValidLowLevel())
	{
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_PhysicsBody));
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));

		TArray<AActor*>IgnoreActors;
		IgnoreActors.Add(Monster);

		FVector TraceStart = Monster->GetMesh()->GetSocketLocation(SocketName);
		FVector TraceEnd = TraceStart + Monster->GetActorForwardVector()*RangeDistance;

		UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(),
			TraceStart,
			TraceEnd,
			ObjectTypes,
			false,
			IgnoreActors,
			EDrawDebugTrace::ForDuration,
			HitResult,
			true);
	}

	return HitResult;
}
