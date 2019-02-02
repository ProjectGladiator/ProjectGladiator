// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterCreateWidget.h"
//클라 헤더
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Kismet/GameplayStatics.h"
#include "Client/ChracterCreateSelect/ChracterCreateSelectPC.h"
#include "Client/ChracterCreateSelect/CharacterCreateSelectGameMode.h"
#include "Client/MainMap/MainMapGameMode.h"
#include "Client/MainMap/MainMapPlayerController.h"
#include "Client/ErrorWidget/WidgetOk.h"
#include "Client/ErrorWidget/WidgetCancel.h"

//서버 헤더
#include "NetWork/CharacterManager.h"
#include "NetWork/NetworkManager.h"

void UCharacterCreateWidget::NativeConstruct()
{
	Super::NativeConstruct();

	NickNameInputBox = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("NickNameInputBox")));

	ChracterCreateButton = Cast<UButton>(GetWidgetFromName(TEXT("ChracterCreateButton")));

	CancelButton = Cast<UButton>(GetWidgetFromName(TEXT("CancelButton")));

	if (ChracterCreateButton)
	{
		ChracterCreateButton->OnClicked.AddDynamic(this, &UCharacterCreateWidget::ChracterCreate);
	}

	if (CancelButton)
	{
		CancelButton->OnClicked.AddDynamic(this, &UCharacterCreateWidget::Cancel);
	}

	MainMapPlayerController = Cast<AMainMapPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	MainMapGameMode = Cast<AMainMapGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

void UCharacterCreateWidget::ChracterCreate()
{
	// 캐릭터가 선택 되었다면
	if (ChracterCreateButton && MainMapPlayerController->GetJobCode() != 0)
	{
		FString id = NickNameInputBox->Text.ToString();
		if (!id.IsEmpty())
		{
			CharacterManager::GetInstance()->Character_Req_Character(TCHAR_TO_ANSI(*id), MainMapPlayerController->GetJobCode());
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
						//NetworkClient_main::NetworkManager::GetInstance()->Wait();
					}
				}
			}
			NickNameInputBox->SetText(FText::FromString(TEXT("")));
			MainMapGameMode->CharacterSelectWidgetToggle();
			MainMapGameMode->CharacterCreateWidgetToggle();
			MainMapPlayerController->ToCharacterSelect();
		}
		else
		{
			MainMapGameMode->OkWidgetToggle(FText(FText::FromString("아이디를 입력해주세요")));
		}
	}
	else   // 캐릭터가 선택 되지 않았다면
	{
		FText ft = NSLOCTEXT("Character", "RequestCharacterSelect", "캐릭터를 선택해주세요");
		EAppReturnType::Type Open(EAppMsgType::Type Ok, FText(ft));
	}
}

void UCharacterCreateWidget::Cancel()
{
	if (MainMapPlayerController)
	{
		CharacterManager::GetInstance()->Character_Exit();
		NetworkClient_main::NetworkManager::GetInstance()->Send();
		NetworkClient_main::NetworkManager::GetInstance()->Wait();

		MainMapGameMode->CharacterCreateWidgetToggle();
		MainMapGameMode->CharacterSelectWidgetToggle();
		MainMapPlayerController->ToCharacterSelect();
	}
}

UButton * UCharacterCreateWidget::GetChracterCreateButton()
{
	return ChracterCreateButton;
}
