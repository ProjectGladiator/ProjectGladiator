// Fill out your copyright notice in the Description page of Project Settings.

#include "TitleCharacterSelectWidget.h"
//클라 헤더
#include "Components/Button.h"
#include "Client/ChracterCreateSelect/Widget/CharacterSelectButton.h"
#include "Kismet/GameplayStatics.h"
#include "Client/ChracterCreateSelect/ChracterCreateSelectPC.h"
#include "Client/ChracterCreateSelect/CharacterCreateSelectGameMode.h"
#include "Client/WinterGameInstance.h"
//서버 헤더
#include "NetWork/NetworkManager.h"
#include "NetWork/CharacterManager.h"
#include "NetWork/StorageManager.h"

void UTitleCharacterSelectWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GameStartButton = Cast<UButton>(GetWidgetFromName(TEXT("GameStart")));
	CharacterDelete = Cast<UButton>(GetWidgetFromName(TEXT("CharacterDelete")));
	CharacterCreate = Cast<UButton>(GetWidgetFromName(TEXT("CharacterCreate")));
	CharacterButtonOne = Cast<UCharacterSelectButton>(GetWidgetFromName(TEXT("CharacterSelectButtonOne")));
	CharacterButtonOne->SetVisibility(ESlateVisibility::Hidden);
	CharacterButtonTwo = Cast<UCharacterSelectButton>(GetWidgetFromName(TEXT("CharacterSelectButtonTwo")));
	CharacterButtonTwo->SetVisibility(ESlateVisibility::Hidden);
	CharacterButtonThree = Cast<UCharacterSelectButton>(GetWidgetFromName(TEXT("CharacterSelectButtonThree")));
	CharacterButtonThree->SetVisibility(ESlateVisibility::Hidden);
	
	if (GameStartButton)
	{
		GameStartButton->OnClicked.AddDynamic(this, &UTitleCharacterSelectWidget::GameStart);
	}

	if (CharacterDelete)
	{
		CharacterDelete->OnClicked.AddDynamic(this, &UTitleCharacterSelectWidget::MyCharacterDelete);
	}	

	if (CharacterCreate)
	{
		CharacterCreate->OnClicked.AddDynamic(this, &UTitleCharacterSelectWidget::MyCharacterCreate);
	}

	PC = Cast<AChracterCreateSelectPC>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	CCSGM = Cast<ACharacterCreateSelectGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}	

void UTitleCharacterSelectWidget::GameStart()
{

	if (PC)
	{	
		UWinterGameInstance* MyGI = Cast<UWinterGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));		
		
		if (MyGI)
		{
			//****
			//** 게임 시작, 캐릭터 생성 버튼 비활성화
			//****

			/*
			** 캐릭터 선택한 슬롯번호 서버에 보내면서 접속 요청하기
			*/
			CharacterManager::GetInstance()->Character_Req_Enter(PC->select_index);
			NetworkClient_main::NetworkManager::GetInstance()->Send();
		}		
	}	
}

void UTitleCharacterSelectWidget::MyCharacterDelete()
{

}

void UTitleCharacterSelectWidget::MyCharacterCreate()
{
	CharacterManager::GetInstance()->Character_Req_New_Character();
	NetworkClient_main::NetworkManager::GetInstance()->Send();
	NetworkClient_main::NetworkManager::GetInstance()->Wait();

	CCSGM->CharacterCreateWidgetToggle();
	CCSGM->CharacterSelectWidgetToggle();
	PC->ToCharacterCreate();
}

void UTitleCharacterSelectWidget::MyCharacterSlotUpdate(PacketData* _data)
{
	bool EmptySlot;
	int SlotCount;
	PacketData* Data = _data;

	CharacterSlot* characterslot = new CharacterSlot[3];

	memset(characterslot, 0, sizeof(CharacterSlot[3]));

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
			FString nick = characterslot[i].nick;

			if (i == 0)
			{
				CharacterButtonOne->CharacterInfoInput(FText::FromString(nick), FText::FromString(level), FText::FromString(name));
				CharacterButtonOne->SetVisibility(ESlateVisibility::Visible);
			}
			else if (i == 1)
			{
				CharacterButtonTwo->CharacterInfoInput(FText::FromString(nick), FText::FromString(level), FText::FromString(name));
				CharacterButtonTwo->SetVisibility(ESlateVisibility::Visible);
			}
			else if (i == 2)
			{
				CharacterButtonThree->CharacterInfoInput(FText::FromString(nick), FText::FromString(level), FText::FromString(name));
				CharacterButtonThree->SetVisibility(ESlateVisibility::Visible);
			}
		}
	}
	StorageManager::GetInstance()->PopData();
}
