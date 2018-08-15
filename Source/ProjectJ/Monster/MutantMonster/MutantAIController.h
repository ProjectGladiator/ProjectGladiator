// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MutantAIController.generated.h"

/**
 * 
 */

UCLASS()
class PROJECTJ_API AMutantAIController : public AAIController
{
	GENERATED_BODY()
public:
	AMutantAIController();
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category = "AI")
		class UBehaviorTreeComponent* BTComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
		class UBlackboardComponent* BBComponent;

	UFUNCTION()
		virtual void Possess(APawn* InPawn) override;
};
