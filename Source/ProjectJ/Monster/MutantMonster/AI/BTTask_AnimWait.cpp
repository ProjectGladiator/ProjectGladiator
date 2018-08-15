// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_AnimWait.h"
#include "Monster/MutantMonster/MutantAIController.h"
#include "Monster/MutantMonster/MutantMonster.h"

EBTNodeResult::Type UBTTask_AnimWait::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AMutantAIController* AI = Cast<AMutantAIController>(OwnerComp.GetAIOwner());

	if (AI)
	{
		AMutantMonster* Mutant = Cast<AMutantMonster>(AI->GetPawn());

		if (Mutant)
		{
			Mutant->CurrentAnimState = EMonsterAnimState::Wait;
		}
	}
	return EBTNodeResult::Succeeded;
}
