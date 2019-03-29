// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Client/Monster/MonsterAIController.h"
#include "GrountAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API AGrountAIController : public AMonsterAIController
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
		virtual void Possess(APawn* InPawn) override;
	
	
};
