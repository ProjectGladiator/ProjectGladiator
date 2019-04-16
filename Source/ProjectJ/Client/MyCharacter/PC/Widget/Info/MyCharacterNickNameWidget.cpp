// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacterNickNameWidget.h"
//클라 헤더
#include "Components/TextBlock.h"
//서버 헤더

void UMyCharacterNickNameWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CharacterNickNameText = Cast<UTextBlock>(GetWidgetFromName(TEXT("CharacterNickNameText")));
}

void UMyCharacterNickNameWidget::SetCharacterNickNameToWidget(char * _MyCharacterNick)
{
	if (CharacterNickNameText)
	{
		CharacterNickNameText->SetText(FText::FromString(ANSI_TO_TCHAR(_MyCharacterNick)));
	}
}
