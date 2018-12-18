// Fill out your copyright notice in the Description page of Project Settings.

#include "MutantAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MutantMonster.h"
#include "BehaviorTree/BehaviorTree.h"

AMutantAIController::AMutantAIController()
{
	BTComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTree"));
	BBComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));
}

void AMutantAIController::Possess(APawn * InPawn)
{
	Super::Possess(InPawn);

	AMutantMonster* Mutant = Cast<AMutantMonster>(InPawn);

	if (Mutant)
	{
		if (Mutant->BehaviorTree)
		{
			if (Mutant->BehaviorTree->BlackboardAsset)
			{
				BBComponent->InitializeBlackboard(*(Mutant->BehaviorTree->BlackboardAsset));
				BTComponent->StartTree(*(Mutant->BehaviorTree));
			}
		}
	}
}
