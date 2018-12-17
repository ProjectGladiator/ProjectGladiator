// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterSelectButton.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "ChracterCreateSelect/ChracterCreateSelectPC.h"

void UCharacterSelectButton::NativeConstruct()
{
	Super::NativeConstruct();

	CharacterSelectButton = Cast<UButton>(GetWidgetFromName(TEXT("CharacterSelectButton")));

	CharacterNickName = Cast<UTextBlock>(GetWidgetFromName(TEXT("CharacterNickName")));

	CharacterLevel = Cast<UTextBlock>(GetWidgetFromName(TEXT("CharacterLevel")));

	ClassName = Cast<UTextBlock>(GetWidgetFromName(TEXT("ClassName")));

	if (CharacterSelectButton)
	{
		CharacterSelectButton->OnClicked.AddDynamic(this, &UCharacterSelectButton::CharacterSelect);
	}

	PC = Cast<AChracterCreateSelectPC>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

void UCharacterSelectButton::CharacterSelect()
{
	if (CharacterSelectButton)
	{
	/*	PC->CharacterSelectWidgetToggle();
		PC->CharacterCreateWidgetToggle();	*/	

		FString str = this->GetName();

		if (str.Compare("CharacterSelectButtonOne"))
		{
			PC->select_index = 1;
		}
		else if (str.Compare("CharacterSelectButtonTwo"))
		{
			PC->select_index = 2;
		}
		else if (str.Compare("CharacterSelectButtonThree"))
		{
			PC->select_index = 3;
		}
	}
}

void UCharacterSelectButton::CharacterInfoInput(const FText & NickName, const FText & Level, const FText & JobName)
{
	if (CharacterNickName && CharacterLevel && ClassName)
	{
		CharacterNickName->SetText(NickName);
		CharacterLevel->SetText(Level);
		ClassName->SetText(JobName);
	}
}

