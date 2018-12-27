// Fill out your copyright notice in the Description page of Project Settings.

#include "TitleCharacterSelectWidget.h"
#include "Components/Button.h"
#include "Client/Title/Widget/CharacterSelectButton.h"
#include "Kismet/GameplayStatics.h"
#include "Client/ChracterCreateSelect/ChracterCreateSelectPC.h"
#include "NetWork/NetworkManager.h"
#include "NetWork/CharacterManager.h"
#include "NetWork/StorageManager.h"
#include "Client/WinterGameInstance.h"

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
}	

void UTitleCharacterSelectWidget::GameStart()
{

	if (PC)
	{	
		UWinterGameInstance* MyGI = Cast<UWinterGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));		
		
		if (MyGI)
		{

			PacketData* Data;
			bool ResultFlag;

			if (StorageManager::GetInstance()->GetFront(Data))
			{
				switch (Data->protocol)
				{
				case PCHARACTERDATA_ENTER_RESULT:
					StorageManager::GetInstance()->ChangeData(Data, ResultFlag);

					if (ResultFlag)
					{
						StorageManager::GetInstance()->PopData();

						switch (PC->select_index)
						{
						case 1:
							MyGI->SetSelectCharacterIndex(PC->select_index);
							UE_LOG(LogClass, Warning, TEXT("1번 선택함"));
							break;
						case 2:
							MyGI->SetSelectCharacterIndex(PC->select_index);
							UE_LOG(LogClass, Warning, TEXT("2번 선택함"));
							break;
						case 3:
							MyGI->SetSelectCharacterIndex(PC->select_index);
							UE_LOG(LogClass, Warning, TEXT("3번 선택함"));
							break;
						}
					}
					else
					{

					}
					break;
				}
			}			
		}		
		
		//PC->SetInputMode(FInputModeGameOnly());
		//UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainStage")); //타이틀 맵으로 이동			
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

	if (StorageManager::GetInstance()->GetFront(Data))
	{
		if (Data->protocol == PCHARACTERDATA_SLOT_INFO)
		{
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
	}
}
