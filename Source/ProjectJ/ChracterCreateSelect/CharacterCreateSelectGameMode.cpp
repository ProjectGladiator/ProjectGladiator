// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterCreateSelectGameMode.h"
#include "ChracterCreateSelectPC.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "ChracterCreateSelect/CameraActor/ChracterCreateCamera.h"
#include "NetWork/CharacterManager.h"

ACharacterCreateSelectGameMode::ACharacterCreateSelectGameMode()
{
	PlayerControllerClass = AChracterCreateSelectPC::StaticClass();
}

void ACharacterCreateSelectGameMode::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AChracterCreateCamera::StaticClass(), Cameras);

	CharacterManager::GetInstance()->Character_Req_Slot();

}
