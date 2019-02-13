// Fill out your copyright notice in the Description page of Project Settings.

#include "SpiderBossAIController.h"
//클라 헤더
#include "SpiderBoss.h"

//서버 헤더

void ASpiderBossAIController::Possess(APawn * InPawn)
{
	Super::Possess(InPawn);

	auto SpiderBoss = Cast<ASpiderBoss>(InPawn);

	if (SpiderBoss)
	{
		SpiderBoss->SetAIController(this);
		GLog->Log(FString::Printf(TEXT("Spider Boss Posses Success")));
	}
	else
	{
		GLog->Log(FString::Printf(TEXT("Spider Boss Posses Fail")));
	}
}



