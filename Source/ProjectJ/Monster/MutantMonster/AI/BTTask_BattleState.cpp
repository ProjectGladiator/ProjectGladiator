// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_BattleState.h"
#include "Header/MutantAIHeader.h"

EBTNodeResult::Type UBTTask_BattleState::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AMutantAIController* AI = Cast<AMutantAIController>(OwnerComp.GetAIOwner());

	if (AI)
	{
		AMutantMonster* Mutant = Cast<AMutantMonster>(AI->GetPawn());

		if (Mutant)
		{
			switch (Mutant->CurrentAttackState)
			{
			case EMonsterAttackState::Idle:
				break;
			case EMonsterAttackState::DefaultAttack:
				Mutant->CurrentAnimState = EMonsterAnimState::Attack;
				break;
			case EMonsterAttackState::ParryingAttack:
				Mutant->CurrentState = EMonsterState::Battle;
				Mutant->CurrentAnimState = EMonsterAnimState::Attack;
				break;
			}
			
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
