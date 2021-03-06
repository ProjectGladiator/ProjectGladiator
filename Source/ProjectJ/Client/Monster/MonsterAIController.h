// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MonsterAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API AMonsterAIController : public AAIController
{
	GENERATED_BODY()
public:
	AMonsterAIController(const FObjectInitializer& ObjectInitializer);
	
	UFUNCTION()
		virtual void Possess(APawn* InPawn) override;
};
