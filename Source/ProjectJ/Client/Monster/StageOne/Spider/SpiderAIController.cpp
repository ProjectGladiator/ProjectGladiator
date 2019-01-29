// Fill out your copyright notice in the Description page of Project Settings.

#include "SpiderAIController.h"
//클라 헤더
#include "Spider.h"

//서버 헤더

void ASpiderAIController::Possess(APawn * InPawn)
{
	Super::Possess(InPawn);

	auto Spider = Cast<ASpider>(InPawn);

	if (Spider)
	{
		Spider->SetAIController(this);
		GLog->Log(FString::Printf(TEXT("Spider Posses Success")));
	}
	else
	{
		GLog->Log(FString::Printf(TEXT("Spider Posses Fail")));
	}
}
