// Fill out your copyright notice in the Description page of Project Settings.

#include "MainStageGameMode.h"
//클라 헤더
#include "MainStagePlayerController.h"
#include "Client/CharacterSpawnLocation.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Client/WinterGameInstance.h"
#include "Client/MyCharacter/Tanker/Tanker.h"
//서버 헤더
#include "NetWork/CharacterManager.h"
#include "NetWork/StorageManager.h"

AMainStageGameMode::AMainStageGameMode()
{	
	PlayerControllerClass = AMainStagePlayerController::StaticClass();

	PrimaryActorTick.bCanEverTick = true;
}

AMainStageGameMode::~AMainStageGameMode()
{
}

void AMainStageGameMode::BeginPlay()
{
	Super::BeginPlay();

	UWinterGameInstance* MyGI = Cast<UWinterGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	// Chracter_Req_Enter << 해당 함수는 캐릭터 생성에서 게임시작 버튼 누를시 호출
	//if (MyGI)
	//{
	//	CharacterManager::GetInstance()->Character_Req_Enter(MyGI->GetSelectCharacterIndex());
	//}
}

void AMainStageGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PacketData* Data;
	CharacterInfo* character_info = nullptr;
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
			// 캐릭터 정보 받을 구조체 할당
			character_info = new CharacterInfo;
			// 캐릭터 정보 서버에서 받은거 넣어줌
			StorageManager::GetInstance()->ChangeData(Data, 1, character_info);

			FVector SpawnLocation(character_info->x, character_info->y, character_info->z);

			FActorSpawnParameters SpawnActorOption;
	
			SpawnActorOption.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			switch (character_info->character_code)
			{
			case 1000:
				{// 지역 변수이용하기 위함
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

			// 필요없어진 캐릭터정보 구조체 해제
			delete character_info;
		}
	}	
}
