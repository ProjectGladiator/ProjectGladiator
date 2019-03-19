// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainMapOtherPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API AMainMapOtherPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMainMapOtherPlayerController();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		virtual void Possess(APawn* InPawn) override;
};
