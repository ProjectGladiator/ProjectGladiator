// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Client/Monster/MonsterAIController.h"
#include "SpiderAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API ASpiderAIController : public AMonsterAIController
{
	GENERATED_BODY()
public:
	UFUNCTION()
		virtual void Possess(APawn* InPawn) override;
};
