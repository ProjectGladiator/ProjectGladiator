// Fill out your copyright notice in the Description page of Project Settings.

#include "TitleCharacterSelectWidget.h"
#include "Components/Button.h"
#include "Title/Widget/CharacterSelectButton.h"
#include "Kismet/GameplayStatics.h"
#include "Title/TitlePlayerController.h"
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
	
	PC = Cast<ATitlePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
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

}

void UTitleCharacterSelectWidget::MyCharacterSlotUpdate()
{
	bool EmptySlot;
	int SlotCount;
	PacketData* Data;
	CharacterSlot* CharacterSlotInfo;

	if (StorageManager::GetInstance()->GetFront(Data))
	{
		if (Data->protoocl == SERVER_CHARACTER_SLOT_RESULT)
		{
			StorageManager::GetInstance()->ChangeData(Data->data, EmptySlot, SlotCount,CharacterSlotInfo);

			if (EmptySlot)
			{
				CharacterButtonOne->SetVisibility(ESlateVisibility::Hidden);
				CharacterButtonTwo->SetVisibility(ESlateVisibility::Hidden);
				CharacterButtonThree->SetVisibility(ESlateVisibility::Hidden);
			}
			else
			{

			}
		}
	}
}
