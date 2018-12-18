// Fill out your copyright notice in the Description page of Project Settings.

#include "ArcherAIController.h"
#include "Client/Monster/ArcherMonster/ArcherMonster.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

AArcherAIController::AArcherAIController()
{
	/*BBComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));
	BTComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTree"));*/
}

void AArcherAIController::Possess(APawn * InPawn)
{
	Super::Possess(InPawn);

	/*AArcherMonster* Archer = Cast<AArcherMonster>(InPawn);

	if (Archer)
	{
		if (Archer->BehaviorTree)
		{
			if (Archer->BehaviorTree->BlackboardAsset)
			{
				BBComponent->InitializeBlackboard(*(Archer->BehaviorTree->BlackboardAsset));
				BTComponent->StartTree(*(Archer->BehaviorTree));
			}
		}
	}*/
}
