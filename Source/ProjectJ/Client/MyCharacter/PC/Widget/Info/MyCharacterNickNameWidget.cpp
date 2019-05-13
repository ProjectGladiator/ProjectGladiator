// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacterNickNameWidget.h"
//클라 헤더
#include "Components/TextBlock.h"
#include <Windows.h>

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
		WCHAR CharacterNick[20];
		memset(CharacterNick, 0, sizeof(CharacterNick));

		int nLen = MultiByteToWideChar(CP_ACP, 0, _MyCharacterNick, strlen(_MyCharacterNick), NULL, NULL);
		MultiByteToWideChar(CP_UTF8, 0, _MyCharacterNick, strlen(_MyCharacterNick), CharacterNick, nLen);

		CharacterNickNameText->SetText(FText::FromString((TEXT("%s"), CharacterNick)));
	}
}
