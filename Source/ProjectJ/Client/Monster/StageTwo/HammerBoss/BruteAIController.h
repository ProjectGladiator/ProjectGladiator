// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Client/Monster/MonsterAIController.h"
#include "BruteAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API ABruteAIController : public AMonsterAIController
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
		virtual void Possess(APawn* InPawn) override;
	
	
};
