// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_JumpReadyState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API UBTTask_JumpReadyState : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	class AMutantMonster* Mutant;
	FTimerHandle RunTimer;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void JumpRunCheck();
};
