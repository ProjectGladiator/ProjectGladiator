// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_ParryingState.h"

#include "Monster/MutantMonster/MutantAIController.h"
#include "Monster/MutantMonster/MutantMonster.h"

#include "Components/CapsuleComponent.h"

EBTNodeResult::Type UBTTask_ParryingState::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AMutantAIController* AI = Cast<AMutantAIController>(OwnerComp.GetAIOwner());

	if (AI)
	{
		AMutantMonster* Mutant = Cast<AMutantMonster>(AI->GetPawn());

		if (Mutant)
		{
			Mutant->IsParrying = false;
			Mutant->CurrentAnimState = EMonsterAnimState::Run;
			Mutant->CurrentAttackState = EMonsterAttackState::Idle;
			Mutant->CurrentState = EMonsterState::Chase;			
		}
	}
	return EBTNodeResult::Succeeded;
}
