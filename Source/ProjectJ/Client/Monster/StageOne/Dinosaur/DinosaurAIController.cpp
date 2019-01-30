// Fill out your copyright notice in the Description page of Project Settings.

#include "DinosaurAIController.h"
//클라 헤더
#include "Dinosaur.h"
//서버 헤더

void ADinosaurAIController::Possess(APawn * InPawn)
{
	Super::Possess(InPawn);

	auto Dinosaur = Cast<ADinosaur>(InPawn);

	if (Dinosaur)
	{
		Dinosaur->SetAIController(this);
		GLog->Log(FString::Printf(TEXT("Dinosaur Possess Success")));
	}
	else
	{
		GLog->Log(FString::Printf(TEXT("Dinosaur Possess Fail")));
	}
}
