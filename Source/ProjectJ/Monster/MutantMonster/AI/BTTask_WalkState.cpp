// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_WalkState.h"
#include "Header/MutantAIHeader.h"



void UBTTask_WalkState::InitializeFromAsset(UBehaviorTree & Asset)
{
	Super::InitializeFromAsset(Asset);
	bNotifyTick = true;
	WalkStateEscapeFlag = false;
}

EBTNodeResult::Type UBTTask_WalkState::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	return EBTNodeResult::InProgress;	
}

void UBTTask_WalkState::TickTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AMutantAIController* AI = Cast<AMutantAIController>(OwnerComp.GetAIOwner());

	if (AI)
	{
		AMutantMonster* Mutant = Cast<AMutantMonster>(AI->GetPawn());

		if (Mutant)
		{
			AMyCharacter* Mycharacter = Cast<AMyCharacter>(AI->BBComponent->GetValueAsObject("Player"));

			if (Mycharacter)
			{
				AActor* GoalActor = Cast<AActor>(AI->BBComponent->GetValueAsObject("MovePoint"));

				if (GoalActor)
				{
					AI->MoveToActor(GoalActor);

					if (Mutant->GetActorLocation() == GoalActor->GetActorLocation())
					{
						UE_LOG(LogClass, Warning, TEXT("ChaseStateCheckExe"));
						FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
					}
				}
			}
		}
	}
}
