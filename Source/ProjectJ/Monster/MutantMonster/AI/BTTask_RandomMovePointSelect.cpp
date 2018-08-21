// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_RandomMovePointSelect.h"
#include "Monster/MutantMonster/MutantAIController.h"
#include "Monster/MutantMonster/MutantMonster.h"

#include "Monster/PatrolPoint.h"

#include "MyCharacter/Warrior/MyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

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
				MovePoints = Mycharacter->AttackPoints;

				int RandomAttackPointIndex = FMath::FRandRange(0, 7);

				AI->BBComponent->SetValueAsObject("MovePoint", MovePoints[RandomAttackPointIndex]);
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
