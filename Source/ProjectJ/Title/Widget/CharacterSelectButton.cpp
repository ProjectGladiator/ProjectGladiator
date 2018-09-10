// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterSelectButton.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Title/TitlePlayerController.h"

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

	PC = Cast<ATitlePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

void UCharacterSelectButton::CharacterSelect()
{
	if (CharacterSelectButton)
	{
		PC->CharacterSelectWidgetToggle();
		PC->CharacterCreateWidgetToggle();		
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

