// Fill out your copyright notice in the Description page of Project Settings.

#include "WormAIController.h"
//클라 헤더
#include "Worm.h"
//서버 헤더

void AWormAIController::Possess(APawn * InPawn)
{
	Super::Possess(InPawn);

	auto Worm = Cast<AWorm>(InPawn);

	if (Worm)
	{
		Worm->SetAIController(this);
		GLog->Log(FString::Printf(TEXT("Posses Success")));
	}
	else
	{
		GLog->Log(FString::Printf(TEXT("Posses Fail")));
	}
}
