// Fill out your copyright notice in the Description page of Project Settings.

#include "MainStageGameMode.h"
//클라 헤더
#include "MainStagePlayerController.h"
#include "Client/CharacterSpawnLocation.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Client/WinterGameInstance.h"
#include "Client/MyCharacter/Tanker/Tanker.h"
#include "MainStagePlayerController.h"
//서버 헤더
#include "NetWork/CharacterManager.h"
#include "NetWork/StorageManager.h"
#include "NetWork/JobInfo.h"

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

			memset(character_info, 0, sizeof(CharacterInfo));

			// 캐릭터 정보 서버에서 받은거 넣어줌
			StorageManager::GetInstance()->ChangeData(Data->data, 1, character_info);

			StorageManager::GetInstance()->PopData();

			FVector SpawnLocation(character_info->x, character_info->y, character_info->z);

			FActorSpawnParameters SpawnActorOption;
	
			SpawnActorOption.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			switch (character_info->character_code)
			{
			case CHARACTER_JOB::TANKER:
				{// 지역 변수이용하기 위함
					ATanker * Tanker = GetWorld()->SpawnActor<ATanker>(Tanker->StaticClass(), SpawnLocation, FRotator::ZeroRotator, SpawnActorOption);

					if (Tanker)
					{
						auto MainStagePlayerController = Cast<AMainStagePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

						if (MainStagePlayerController)
						{
							MainStagePlayerController->Possess(Tanker);
						}
						else
						{
							GLog->Log(FString::Printf(TEXT("메인 스테이지 월드에 메인스테이지 플레이어컨트롤러가 스폰 안됨")));
						}
					}
					else
					{
						GLog->Log(FString::Printf(TEXT("메인 스테이지 월드에 탱커가 스폰 안됨")));
					}
				}
				break;
			case CHARACTER_JOB::WARRIOR:
				break;
			case CHARACTER_JOB::MAGICIAN:
				break;
			case CHARACTER_JOB::GUNNER:
				break;
			}
			break;

			// 필요없어진 캐릭터정보 구조체 해제
			delete character_info;
		}
	}	
}
