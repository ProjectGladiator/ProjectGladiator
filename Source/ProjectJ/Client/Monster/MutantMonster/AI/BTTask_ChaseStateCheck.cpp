// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_ChaseStateCheck.h"
#include "Client/Header/MutantAIHeader.h"

EBTNodeResult::Type UBTTask_ChaseStateCheck::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AMutantAIController* AI = Cast<AMutantAIController>(OwnerComp.GetAIOwner());

	if (AI)
	{
		AMutantMonster* Mutant = Cast<AMutantMonster>(AI->GetPawn());

		if (Mutant)
		{
			if (Mutant->CurrentAnimState == EMonsterAnimState::JumpAttack)
			{
				if (Mutant->CurrentJumpState == EMonsterJumpState::Idle)
				{
					Mutant->CurrentJumpState = EMonsterJumpState::JumpStart;
				}
			}
		}
	}	
	return EBTNodeResult::Succeeded;
}
