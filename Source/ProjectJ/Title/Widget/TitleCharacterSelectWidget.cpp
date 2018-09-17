// Fill out your copyright notice in the Description page of Project Settings.

#include "TitleCharacterSelectWidget.h"
#include "Components/Button.h"
#include "Title/Widget/CharacterSelectButton.h"
#include "Kismet/GameplayStatics.h"
#include "ChracterCreateSelect/ChracterCreateSelectPC.h"
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
	CharacterButtonTwo = Cast<UCharacterSelectButton>(GetWidgetFromName(TEXT("CharacterSelectButtonTwo")));
	CharacterButtonThree = Cast<UCharacterSelectButton>(GetWidgetFromName(TEXT("CharacterSelectButtonThree")));
	
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

}	

void UTitleCharacterSelectWidget::GameStart()
{
	if (PC)
	{
		PC->SetInputMode(FInputModeGameOnly());
		UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainStage")); //타이틀 맵으로 이동			
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

	PC->CharacterCreateWidgetToggle();
	PC->CharacterSelectWidgetToggle();
	PC->ToCharacterCreate();
}

void UTitleCharacterSelectWidget::MyCharacterSlotUpdate()
{
	bool EmptySlot;
	int SlotCount;
	PacketData* Data;
	CharacterSlot* CharacterSlotInfo = nullptr;

	if (StorageManager::GetInstance()->GetFront(Data))
	{
		if (Data->protocol == PCHARACTERDATA_SLOT_INFO)
		{
			StorageManager::GetInstance()->ChangeData(Data->data, EmptySlot, SlotCount,CharacterSlotInfo);

			if (!EmptySlot)
			{
				CharacterButtonOne->SetVisibility(ESlateVisibility::Hidden);
				CharacterButtonTwo->SetVisibility(ESlateVisibility::Hidden);
				CharacterButtonThree->SetVisibility(ESlateVisibility::Hidden);
			}
			else
			{
				CharacterSlot* characterslot = new CharacterSlot[SlotCount];

				for (int i = 0; i < SlotCount; i++)
				{
					FString name = CharacterSlotInfo[i].name;
					FString level = FString::FromInt(*CharacterSlotInfo[i].level);
					FString nick = CharacterSlotInfo[i].nick;
					
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
		}
	}
}
