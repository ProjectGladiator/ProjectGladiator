// Fill out your copyright notice in the Description page of Project Settings.

#include "TitleCharacterCreateWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Kismet/GameplayStatics.h"
#include "Title/TitlePlayerController.h"
#include "NetWork/CharacterManager.h"

void UTitleCharacterCreateWidget::NativeConstruct()
{
	NickNameInputBox = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("NickNameInputBox")));

	NickNameOverlapCheckButton = Cast<UButton>(GetWidgetFromName(TEXT("NickNameOverlapCheckButton")));

	ChracterCreateButton = Cast<UButton>(GetWidgetFromName(TEXT("ChracterCreateButton")));

	CancelButton = Cast<UButton>(GetWidgetFromName(TEXT("CancelButton")));

	if (ChracterCreateButton)
	{
		ChracterCreateButton->OnClicked.AddDynamic(this, &UTitleCharacterCreateWidget::ChracterCreate);
	}

	if (NickNameOverlapCheckButton)
	{
		NickNameOverlapCheckButton->OnClicked.AddDynamic(this, &UTitleCharacterCreateWidget::NickNameOverlap);
	}

	if (CancelButton)
	{
		CancelButton->OnClicked.AddDynamic(this, &UTitleCharacterCreateWidget::Cancel);
	}

	PC = Cast<ATitlePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

void UTitleCharacterCreateWidget::ChracterCreate()
{
	if (ChracterCreateButton)
	{
		PC->CharacterSelectWidgetToggle();
		PC->CharacterCreateWidgetToggle();
	}

	CharacterManager::GetInstance()->Character_Req_Slot();
}

void UTitleCharacterCreateWidget::NickNameOverlap()
{

}

void UTitleCharacterCreateWidget::Cancel()
{
	if (PC)
	{
		PC->CharacterCreateWidgetToggle();
		PC->CharacterSelectWidgetToggle();
	}
}