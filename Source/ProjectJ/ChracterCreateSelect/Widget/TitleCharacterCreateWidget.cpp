// Fill out your copyright notice in the Description page of Project Settings.

#include "TitleCharacterCreateWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Kismet/GameplayStatics.h"
#include "ChracterCreateSelect/ChracterCreateSelectPC.h"
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
}

void UTitleCharacterCreateWidget::ChracterCreate()
{
	if (ChracterCreateButton)
	{
		FString id = NickNameInputBox->Text.ToString();		
		CharacterManager::GetInstance()->Character_Req_Character(TCHAR_TO_ANSI(*id), PC->JobCode);
		NetworkClient_main::NetworkManager::GetInstance()->Send();
		NetworkClient_main::NetworkManager::GetInstance()->Wait();

		PC->CharacterSelectWidgetToggle();
		PC->CharacterCreateWidgetToggle();
	}
}


void UTitleCharacterCreateWidget::Cancel()
{
	if (PC)
	{
		CharacterManager::GetInstance()->Character_Exit();
		NetworkClient_main::NetworkManager::GetInstance()->Send();
		NetworkClient_main::NetworkManager::GetInstance()->Wait();

		PC->CharacterCreateWidgetToggle();
		PC->CharacterSelectWidgetToggle();
		PC->ToCharacterSelect();
	}
}