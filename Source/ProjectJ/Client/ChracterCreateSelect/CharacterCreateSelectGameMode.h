// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CharacterCreateSelectGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API ACharacterCreateSelectGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	TArray <AActor*> Cameras;
	ACharacterCreateSelectGameMode();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
