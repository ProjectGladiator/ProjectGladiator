// Fill out your copyright notice in the Description page of Project Settings.

#include "MainStageGameMode.h"
#include "MainStagePlayerController.h"
#include "Client/CharacterSpawnLocation.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

AMainStageGameMode::AMainStageGameMode()
{	
	PlayerControllerClass = AMainStagePlayerController::StaticClass();
}

void AMainStageGameMode::BeginPlay()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACharacterSpawnLocation::StaticClass(), CharacterSpawnLocations);

	if (CharacterSpawnLocations.Num() > 0)
	{
		for (auto CharacterSpawnLocation : CharacterSpawnLocations)
		{
			SpawnLocation.Add(CharacterSpawnLocation->GetActorLocation());
		}		
	}
	else
	{
		GLog->Log(FString::Printf(TEXT("월드에 캐릭터 스폰 위치가 존재하지 않음")));
	}
}
