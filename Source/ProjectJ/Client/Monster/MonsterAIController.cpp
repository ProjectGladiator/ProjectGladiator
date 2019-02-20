// Fill out your copyright notice in the Description page of Project Settings.

#include "MonsterAIController.h"
//클라 헤더
#include "Navigation/CrowdFollowingComponent.h"

//서버 헤더
AMonsterAIController::AMonsterAIController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{

}

void AMonsterAIController::Possess(APawn * InPawn)
{
	Super::Possess(InPawn);
}