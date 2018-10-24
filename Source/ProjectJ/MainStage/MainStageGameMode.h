// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainStageGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API AMainStageGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	TArray<class AActor*> CharacterSpawnLocations;
	TArray <FVector> SpawnLocation;
	AMainStageGameMode();
	virtual void BeginPlay() override;	
};
