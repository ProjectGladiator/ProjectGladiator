// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_JumpAttackState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API UBTTask_JumpAttackState : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	class AMutantMonster* Mutant;
	bool CurrentFalling;
	bool PreviousFalling;
	 //몬스터와 바닥간의 거리를 담을 구조체 변수
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
