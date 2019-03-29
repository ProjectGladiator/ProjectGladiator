// Fill out your copyright notice in the Description page of Project Settings.

#include "GrountAIController.h"

#include "Grount.h"
void AGrountAIController::Possess(APawn * InPawn)
{
	Super::Possess(InPawn);

	auto Grount = Cast<AGrount>(InPawn);

	if (Grount)
	{
		//Grount->SetAIController(this);
		GLog->Log(FString::Printf(TEXT("Grount Posses Success")));
	}
	else
	{
		GLog->Log(FString::Printf(TEXT("Grount Posses Fail")));
	}
}

