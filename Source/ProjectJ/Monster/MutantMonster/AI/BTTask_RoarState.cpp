// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_RoarState.h"
#include "Monster/MutantMonster/MutantAIController.h"
#include "Monster/MutantMonster/MutantMonster.h"

EBTNodeResult::Type UBTTask_RoarState::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	AI = Cast<AMutantAIController>(OwnerComp.GetAIOwner());

	if (AI)
	{		
		AMutantMonster* Mutant = Cast<AMutantMonster>(AI->GetPawn());

		if (Mutant)
		{
			Mutant->CurrentState = EMonsterState::Chase;
			Mutant->CurrentAnimState = EMonsterAnimState::Run;
			return EBTNodeResult::Succeeded;
		}	
		else
		{
			return EBTNodeResult::Failed;
		}
	}
	else
	{
		return EBTNodeResult::Failed;
	}
}
