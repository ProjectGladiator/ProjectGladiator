// Fill out your copyright notice in the Description page of Project Settings.

#include "BearAIController.h"
//클라 헤더
#include "Bear.h"
//서버 헤더

void ABearAIController::Possess(APawn * InPawn)
{
	Super::Possess(InPawn);

	auto Bear = Cast<ABear>(InPawn);

	if (Bear)
	{
		Bear->SetAIController(this);
		GLog->Log(FString::Printf(TEXT("Bear Posses Success")));
	}
	else
	{
		GLog->Log(FString::Printf(TEXT("Bear Posses Fail")));
	}
}
