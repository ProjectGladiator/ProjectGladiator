// Fill out your copyright notice in the Description page of Project Settings.

#include "BruteAIController.h"
#include "Brute.h"


void ABruteAIController::Possess(APawn * InPawn)
{
	Super::Possess(InPawn);

	auto Dog = Cast<ABrute>(InPawn);

	if (Dog)
	{
		Dog->SetAIController(this);
		//Dog->SetAIController(this);
		GLog->Log(FString::Printf(TEXT("Brute Posses Success")));
	}
	else
	{
		GLog->Log(FString::Printf(TEXT("Brute Posses Fail")));
	}
}
