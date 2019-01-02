// Fill out your copyright notice in the Description page of Project Settings.

#include "MainStageGameMode.h"
#include "MainStagePlayerController.h"
#include "Client/CharacterSpawnLocation.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "NetWork/CharacterManager.h"
#include "Client/WinterGameInstance.h"
#include "NetWork/StorageManager.h"

AMainStageGameMode::AMainStageGameMode()
{	
	PlayerControllerClass = AMainStagePlayerController::StaticClass();

	PrimaryActorTick.bCanEverTick = true;
}

void AMainStageGameMode::BeginPlay()
{
	Super::BeginPlay();

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

	UWinterGameInstance* MyGI = Cast<UWinterGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (MyGI)
	{
		CharacterManager::GetInstance()->Character_Req_Enter(MyGI->GetSelectCharacterIndex());
	}	
}

void AMainStageGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//PacketData* Data;
	//bool ResultFlag;
	//if (StorageManager::GetInstance()->GetFront(Data))
	//{
	//	switch (Data->protocol)
	//	{
	//	case PCHARACTERDATA_ENTER_RESULT:
	//		StorageManager::GetInstance()->ChangeData(Data, ResultFlag);

	//		if (ResultFlag)
	//		{
	//			StorageManager::GetInstance()->PopData();
	//		}
	//		break;
	//	case PCHARACTERDATA_ENTER_INFO:
	//		//StorageManager::GetInstance()->ChangeData(Data,)
	//		break;
	//	}
	//}	
}
