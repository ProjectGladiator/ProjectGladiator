// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_DeadState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API UBTTask_DeadState : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	int a;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	
};