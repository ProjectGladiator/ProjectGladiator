// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ArcherAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API AArcherAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AArcherAIController();

	// AI
	UFUNCTION()
		virtual void Possess(APawn* InPawn) override;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
		class UBlackboardComponent* BBComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
		class UBehaviorTreeComponent* BTComponent;
};
