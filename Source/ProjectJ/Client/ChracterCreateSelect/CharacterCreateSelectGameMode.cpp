﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterCreateSelectGameMode.h"
#include "ChracterCreateSelectPC.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Client/ChracterCreateSelect/CameraActor/ChracterCreateCamera.h"
#include "Widget/TitleCharacterSelectWidget.h"		// 새로 추가
#include "NetWork/CharacterManager.h"
#include "NetWork/NetworkManager.h"
#include "NetWork/StorageManager.h"

ACharacterCreateSelectGameMode::ACharacterCreateSelectGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
	PlayerControllerClass = AChracterCreateSelectPC::StaticClass();
}

void ACharacterCreateSelectGameMode::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AChracterCreateCamera::StaticClass(), Cameras);

	CharacterManager::GetInstance()->Character_Req_Slot();
	NetworkClient_main::NetworkManager::GetInstance()->Send();

	AChracterCreateSelectPC* CCSPC = Cast<AChracterCreateSelectPC>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	
	if (CCSPC)
	{
		CharacterSelectWidget = CCSPC->CharacterSelectWidget;
	}
}

void ACharacterCreateSelectGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PacketData* Data;
	//bool ResultFlag;

	if (StorageManager::GetInstance()->GetFront(Data))
	{
		switch (Data->protocol)
		{
		case PCHARACTERDATA_SLOT_INFO:
			CharacterSelectWidget->MyCharacterSlotUpdate(Data);
			break;
		}
	}
}
