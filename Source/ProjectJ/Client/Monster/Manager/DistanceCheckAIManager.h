// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Runtime/AIModule/Classes/Navigation/PathFollowingComponent.h"
#include "DistanceCheckAIManager.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTJ_API UDistanceCheckAIManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDistanceCheckAIManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	float DistanceCalculate(class AMonster* Monster,class AMyCharacter* Target);

	EPathFollowingRequestResult::Type TargetChase(class AMonsterAIController* MonsterAIController, class AMyCharacter* Target, float& TargetLimitDistance);
};
