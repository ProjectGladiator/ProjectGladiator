// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_DeadState.h"
#include "Monster/MutantMonster/MutantAIController.h"

EBTNodeResult::Type UBTTask_DeadState::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	
	AMutantAIController* AI = Cast<AMutantAIController>(OwnerComp.GetAIOwner());

	if (AI)
	{
		AI->GetPawn()->Destroy();
		return EBTNodeResult::Succeeded;
	}
	else
	{
		return EBTNodeResult::Failed;
	}
	
}
