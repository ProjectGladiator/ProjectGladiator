// Fill out your copyright notice in the Description page of Project Settings.

#include "MainStageGameMode.h"
//클라 헤더
#include "MainStagePlayerController.h"
#include "Client/CharacterSpawnLocation.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "NetWork/CharacterManager.h"
#include "Client/WinterGameInstance.h"
#include "Client/MyCharacter/Tanker/Tanker.h"
//서버 헤더
#include "NetWork/StorageManager.h"

AMainStageGameMode::AMainStageGameMode()
{	
	PlayerControllerClass = AMainStagePlayerController::StaticClass();

	PrimaryActorTick.bCanEverTick = true;
}

void AMainStageGameMode::BeginPlay()
{
	Super::BeginPlay();

	UWinterGameInstance* MyGI = Cast<UWinterGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (MyGI)
	{
		CharacterManager::GetInstance()->Character_Req_Enter(MyGI->GetSelectCharacterIndex());
	}	
}

void AMainStageGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PacketData* Data;
	//bool ResultFlag;
	if (StorageManager::GetInstance()->GetFront(Data))
	{
		switch (Data->protocol)
		{
		case PCHARACTERDATA_ENTER_RESULT:
			/*StorageManager::GetInstance()->ChangeData(Data, ResultFlag);

			if (ResultFlag)
			{
				StorageManager::GetInstance()->PopData();
			}*/
			break;
		case PCHARACTERDATA_ENTER_INFO:
			StorageManager::GetInstance()->ChangeData(Data, 1, CharacterInfos);

			FVector SpawnLocation(CharacterInfos.x, CharacterInfos.y, CharacterInfos.z);

			FActorSpawnParameters SpawnActorOption;
	
			SpawnActorOption.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			switch (CharacterInfos.character_code)
			{
			case 1000:
			{
				ATanker * Tanker = GetWorld()->SpawnActor<ATanker>(Tanker->StaticClass(), SpawnLocation, FRotator::ZeroRotator, SpawnActorOption);
			}
				break;
			case 2000:
				break;
			case 3000:
				break;
			case 4000:
				break;
			}
			break;
		}
	}	
}
