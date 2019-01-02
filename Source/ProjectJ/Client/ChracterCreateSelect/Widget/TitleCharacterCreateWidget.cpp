// Fill out your copyright notice in the Description page of Project Settings.

#include "TitleCharacterCreateWidget.h"
//클라 헤더
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Kismet/GameplayStatics.h"
#include "Client/ChracterCreateSelect/ChracterCreateSelectPC.h"
#include "Client/ChracterCreateSelect/CharacterCreateSelectGameMode.h"
//서버 헤더
#include "NetWork/CharacterManager.h"
#include "NetWork/NetworkManager.h"

void UTitleCharacterCreateWidget::NativeConstruct()
{
	NickNameInputBox = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("NickNameInputBox")));

	ChracterCreateButton = Cast<UButton>(GetWidgetFromName(TEXT("ChracterCreateButton")));

	CancelButton = Cast<UButton>(GetWidgetFromName(TEXT("CancelButton")));

	if (ChracterCreateButton)
	{
		ChracterCreateButton->OnClicked.AddDynamic(this, &UTitleCharacterCreateWidget::ChracterCreate);
	}

	if (CancelButton)
	{
		CancelButton->OnClicked.AddDynamic(this, &UTitleCharacterCreateWidget::Cancel);
	}

	PC = Cast<AChracterCreateSelectPC>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	CCSGM = Cast<ACharacterCreateSelectGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

void UTitleCharacterCreateWidget::ChracterCreate()
{
	// 캐릭터가 선택 되었다면
	if (ChracterCreateButton && PC->JobCode != 0)
	{
		FString id = NickNameInputBox->Text.ToString();		
		CharacterManager::GetInstance()->Character_Req_Character(TCHAR_TO_ANSI(*id), PC->JobCode);
		NetworkClient_main::NetworkManager::GetInstance()->Send();
		NetworkClient_main::NetworkManager::GetInstance()->Wait();

		bool result;

		PacketData* Data;
		if (StorageManager::GetInstance()->GetFront(Data))
		{
			if (Data->protocol == PCHARACTERDATA_CREATE_RESULT)
			{
				StorageManager::GetInstance()->ChangeData(Data->data, result);
				StorageManager::GetInstance()->PopData();

				if (result)
				{
					CharacterManager::GetInstance()->Character_Req_Slot();
					NetworkClient_main::NetworkManager::GetInstance()->Send();
					NetworkClient_main::NetworkManager::GetInstance()->Wait();
				}
			}
		}

		CCSGM->CharacterSelectWidgetToggle();
		CCSGM->CharacterCreateWidgetToggle();
	}
	else   // 캐릭터가 선택 되지 않았다면
	{
		FText ft = NSLOCTEXT("Character", "RequestCharacterSelect", "캐릭터를 선택해주세요");
		EAppReturnType::Type Open(EAppMsgType::Type Ok, FText(ft));
	}
}


void UTitleCharacterCreateWidget::Cancel()
{
	if (PC)
	{
		CharacterManager::GetInstance()->Character_Exit();
		NetworkClient_main::NetworkManager::GetInstance()->Send();
		NetworkClient_main::NetworkManager::GetInstance()->Wait();

		CCSGM->CharacterCreateWidgetToggle();
		CCSGM->CharacterSelectWidgetToggle();
		PC->ToCharacterSelect();
	}
}