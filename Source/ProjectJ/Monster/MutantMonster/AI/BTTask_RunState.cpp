// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_RunState.h"
#include "Monster/MutantMonster/MutantAIController.h"
#include "Monster/MutantMonster/MutantMonster.h"

#include "BehaviorTree/BlackboardComponent.h"



EBTNodeResult::Type UBTTask_RunState::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AMutantAIController* AI = Cast<AMutantAIController>(OwnerComp.GetAIOwner());

	if (AI)
	{
		AMutantMonster* Mutant = Cast<AMutantMonster>(AI->GetPawn());

		if (Mutant)
		{
			float Distance = AI->BBComponent->GetValueAsFloat("Distance");

			if (Distance > 1500.0f)
			{
				UE_LOG(LogClass, Warning, TEXT("Distacne 1500.0f"));
				Mutant->CurrentAnimState = EMonsterAnimState::JumpAttackReady;			
			}
		}
	}

	return EBTNodeResult::Succeeded;
}
