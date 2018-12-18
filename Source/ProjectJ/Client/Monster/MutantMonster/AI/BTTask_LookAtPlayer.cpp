// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_LookAtPlayer.h"
#include "Client/Header/MutantAIHeader.h"

EBTNodeResult::Type UBTTask_LookAtPlayer::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AMutantAIController* AI = Cast<AMutantAIController>(OwnerComp.GetAIOwner());

	if (AI)
	{
		AActor* Player = Cast<AActor>(AI->BBComponent->GetValueAsObject(TEXT("Player")));

		if (Player)
		{
			AMyCharacter* MyCharacter = Cast<AMyCharacter>(Player);

			if (MyCharacter)
			{
				AMutantMonster* Mutant = Cast<AMutantMonster>(AI->GetPawn());

				//FRotator LookAt = UKismetMathLibrary::FindLookAtRotation(Mutant->GetActorLocation(), MyCharacter->GetActorLocation());
			//	AI->BBComponent->SetValueAsRotator("LookAtRotator", LookAt);

				if (Mutant)
				{
					Mutant->CurrentAnimState = EMonsterAnimState::Wait;
					//Mutant->SetActorRotation(LookAt);
					Mutant->CurrentState = EMonsterState::Rotate;
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
	else
	{
		return EBTNodeResult::Failed;
	}
}
