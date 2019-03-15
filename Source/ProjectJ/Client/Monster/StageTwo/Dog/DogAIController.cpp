// Fill out your copyright notice in the Description page of Project Settings.

#include "DogAIController.h"

#include "Dog.h"


void ADogAIController::Possess(APawn * InPawn)
{
	Super::Possess(InPawn);

	auto Dog = Cast<ADog>(InPawn);

	if (Dog)
	{
		Dog->SetAIController(this);
		//Dog->SetAIController(this);
		GLog->Log(FString::Printf(TEXT("Dog Posses Success")));
	}
	else
	{
		GLog->Log(FString::Printf(TEXT("Dog Posses Fail")));
	}
}