// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_RandomMovePointSelect.h"
#include "Client/Header/MutantAIHeader.h"

EBTNodeResult::Type UBTTask_RandomMovePointSelect::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AMutantAIController* AI = Cast<AMutantAIController>(OwnerComp.GetAIOwner());

	TArray<APatrolPoint*>MovePoints;

	if (AI)
	{
		AMutantMonster* Mutant = Cast<AMutantMonster>(AI->GetPawn());

		if (Mutant)
		{
			AMyCharacter* Mycharacter = Cast<AMyCharacter>(AI->BBComponent->GetValueAsObject("Player"));
			
			if (Mycharacter)
			{
				//Mutant->JumpRunCheckFlag = true;
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
	else
	{
		return EBTNodeResult::Failed;
	}	
}
