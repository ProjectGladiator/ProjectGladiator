// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_AnimWait.h"
#include "Client/Header/MutantAIHeader.h"

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
