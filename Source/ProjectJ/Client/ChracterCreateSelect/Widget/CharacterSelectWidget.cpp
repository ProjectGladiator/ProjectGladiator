﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterSelectWidget.h"
//클라 헤더
#include "Components/Button.h"
#include "Client/ChracterCreateSelect/Widget/CharacterSelectButton.h"
#include "Kismet/GameplayStatics.h"
#include "Client/MainMap/MainMapGameMode.h"
#include "Client/MainMap/MainMapPlayerController.h"
#include "Client/WinterGameInstance.h"

//서버 헤더
#include "NetWork/NetworkManager.h"
#include "NetWork/CharacterManager.h"
#include "NetWork/StorageManager.h"

void UCharacterSelectWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GameStartButton = Cast<UButton>(GetWidgetFromName(TEXT("GameStart")));
	CharacterDeleteButton = Cast<UButton>(GetWidgetFromName(TEXT("CharacterDelete")));
	CharacterCreateButton = Cast<UButton>(GetWidgetFromName(TEXT("CharacterCreate")));
	CharacterButtonOne = Cast<UCharacterSelectButton>(GetWidgetFromName(TEXT("CharacterSelectButtonOne")));
	CharacterButtonOne->SetVisibility(ESlateVisibility::Hidden);
	CharacterButtonTwo = Cast<UCharacterSelectButton>(GetWidgetFromName(TEXT("CharacterSelectButtonTwo")));
	CharacterButtonTwo->SetVisibility(ESlateVisibility::Hidden);
	CharacterButtonThree = Cast<UCharacterSelectButton>(GetWidgetFromName(TEXT("CharacterSelectButtonThree")));
	CharacterButtonThree->SetVisibility(ESlateVisibility::Hidden);

	if (GameStartButton)
	{
		GameStartButton->OnClicked.AddDynamic(this, &UCharacterSelectWidget::GameStart);
	}

	if (CharacterDeleteButton)
	{
		CharacterDeleteButton->OnClicked.AddDynamic(this, &UCharacterSelectWidget::MyCharacterDelete);
	}

	if (CharacterCreateButton)
	{
		CharacterCreateButton->OnClicked.AddDynamic(this, &UCharacterSelectWidget::MyCharacterCreate);
	}

	MainMapPlayerController = Cast<AMainMapPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	MainMapGameMode = Cast<AMainMapGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

void UCharacterSelectWidget::GameStart()
{
	GLog->Log(FString::Printf(TEXT("선택한 슬롯 : %d"), MainMapPlayerController->GetSelectIndex()));
	if (MainMapPlayerController)
	{
		if (MainMapPlayerController->GetSelectIndex() != -1)
		{
			//****
			//** 게임 시작, 캐릭터 생성 버튼 비활성화
			//****
			ButtonDisable();

			/*
			** 캐릭터 선택한 슬롯번호 서버에 보내면서 접속 요청하기
			*/
			CharacterManager::GetInstance()->Character_Req_Enter(MainMapPlayerController->GetSelectIndex());
			NetworkClient_main::NetworkManager::GetInstance()->Send();
			//MainMapPlayerController->SetSelectIndex(-1);
		}
		else
		{
			if (MainMapGameMode)
			{
				MainMapGameMode->CancelWidgetToggle(FText(FText::FromString("select chracter button")));
			}
		}
	}
}

void UCharacterSelectWidget::MyCharacterDelete()
{
	if (MainMapPlayerController)
	{
		if (MainMapPlayerController->GetSelectIndex() != -1)
		{
			CharacterManager::GetInstance()->Character_Req_Delete(MainMapPlayerController->GetSelectIndex());
			NetworkClient_main::NetworkManager::GetInstance()->Send();
		}
		else
		{
			if (MainMapGameMode)
			{
				MainMapGameMode->CancelWidgetToggle(FText(FText::FromString("Please select a character to delete")));
			}
		}
	}
}

void UCharacterSelectWidget::MyCharacterCreate()
{
	if (MainMapGameMode && MainMapPlayerController)
	{
		MainMapGameMode->CharacterCreateWidgetToggle();
		MainMapGameMode->CharacterSelectWidgetToggle();
		MainMapGameMode->SelectCharacterDestroy();
		MainMapPlayerController->SetSelectIndex(-1);
		MainMapPlayerController->ToCharacterCreate();
	}
}

void UCharacterSelectWidget::MyCharacterSlotUpdate(PacketData * _data)
{
	bool EmptySlot;
	int SlotCount;
	PacketData* Data = _data;

	CharacterSlot* characterslot = new CharacterSlot[3];

	memset(characterslot, 0, sizeof(CharacterSlot) * 3);

	StorageManager::GetInstance()->ChangeData(Data->data, EmptySlot, SlotCount, characterslot);

	if (!EmptySlot)
	{
		CharacterButtonOne->SetVisibility(ESlateVisibility::Hidden);
		CharacterButtonTwo->SetVisibility(ESlateVisibility::Hidden);
		CharacterButtonThree->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		for (int i = 0; i < SlotCount; i++)
		{
			FString name = characterslot[i].name;
			FString level = FString::FromInt(characterslot[i].level);
			WCHAR CharacterNick[20];
			memset(CharacterNick, 0, sizeof(CharacterNick));

			int nLen = MultiByteToWideChar(CP_ACP, 0, characterslot[i].nick, strlen(characterslot[i].nick), NULL, NULL);
			MultiByteToWideChar(CP_UTF8, 0, characterslot[i].nick, strlen(characterslot[i].nick), CharacterNick, nLen);
			
			if (i == 0)
			{
				CharacterButtonOne->CharacterInfoInput(FText::FromString((TEXT("%s"), CharacterNick)), FText::FromString(level), FText::FromString(name));
				CharacterButtonOne->SetVisibility(ESlateVisibility::Visible);
			}
			else if (i == 1)
			{
				CharacterButtonTwo->CharacterInfoInput(FText::FromString((TEXT("%s"), CharacterNick)), FText::FromString(level), FText::FromString(name));
				CharacterButtonTwo->SetVisibility(ESlateVisibility::Visible);
			}
			else if (i == 2)
			{
				CharacterButtonThree->CharacterInfoInput(FText::FromString((TEXT("%s"), CharacterNick)), FText::FromString(level), FText::FromString(name));
				CharacterButtonThree->SetVisibility(ESlateVisibility::Visible);
			}
			//delete[] con_nick;
		}
	}
	StorageManager::GetInstance()->PopData();

	delete[] characterslot;
}

void UCharacterSelectWidget::MyCharacterSlotHidden()
{
	MainMapPlayerController->ToCharacterSelect();
	CharacterButtonOne->SetVisibility(ESlateVisibility::Hidden);
	CharacterButtonTwo->SetVisibility(ESlateVisibility::Hidden);
	CharacterButtonThree->SetVisibility(ESlateVisibility::Hidden);
}

void UCharacterSelectWidget::ButtonEnable()
{
	GameStartButton->SetVisibility(ESlateVisibility::Visible);
	CharacterCreateButton->SetVisibility(ESlateVisibility::Visible);
	CharacterDeleteButton->SetVisibility(ESlateVisibility::Visible);
}

void UCharacterSelectWidget::ButtonDisable()
{
	GameStartButton->SetVisibility(ESlateVisibility::HitTestInvisible);
	CharacterCreateButton->SetVisibility(ESlateVisibility::HitTestInvisible);
	CharacterDeleteButton->SetVisibility(ESlateVisibility::HitTestInvisible);
}
