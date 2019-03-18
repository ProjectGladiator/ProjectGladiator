// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacterWidget.h"
//클라 헤더
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Client/MyCharacter/PC/MyCharacter.h"
//서버 헤더

void UMyCharacterWidget::NativeConstruct()
{
	Super::NativeConstruct();

	MyCharacterButton = Cast<UButton>(GetWidgetFromName(TEXT("MyCharacterButton")));
	MyCharacterHPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("MyCharacterHPBar")));
	MyCharacterMPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("MyCharacterMPBar")));
	MyCharacterHPText = Cast<UTextBlock>(GetWidgetFromName(TEXT("MyCharacterHPText")));
	MyCharacterMPText = Cast<UTextBlock>(GetWidgetFromName(TEXT("MyCharacterMPText")));
	MyCharacterNickName = Cast<UTextBlock>(GetWidgetFromName(TEXT("MyCharacterNickName")));
}

void UMyCharacterWidget::SetInit(AMyCharacter* _MyCharacter)
{
	if (_MyCharacter)
	{
		ClickCharacterSlotInfo.ClickCharacter = _MyCharacter;

		if (MyCharacterNickName)
		{
			char* NickName = ClickCharacterSlotInfo.ClickCharacter->GetCharacterNickName();

			MyCharacterNickName->SetText(FText::FromString(ANSI_TO_TCHAR(NickName)));
			HPUpdate();
			MPUpdate();
		}
		SetVisibility(ESlateVisibility::Visible);
	}
}

void UMyCharacterWidget::HPUpdate()
{
	float CurrentHP = ClickCharacterSlotInfo.ClickCharacter->GetCurrentHP();
	float MaxHP = ClickCharacterSlotInfo.ClickCharacter->GetMaxHP();

	if (MyCharacterHPText)
	{
		MyCharacterHPText->SetText(FText::FromString(FString::FromInt((int32)(CurrentHP))));

		if (MyCharacterHPBar)
		{
			float HPPercent = CurrentHP / MaxHP;

			MyCharacterHPBar->SetPercent(HPPercent);
		}
	}

}

void UMyCharacterWidget::MPUpdate()
{

}

FClickCharacterInfo UMyCharacterWidget::GetClickCharacterSlotInfo()
{
	return ClickCharacterSlotInfo;
}

void UMyCharacterWidget::SetPosition(FVector2D _Position)
{
	SetRenderTranslation(_Position);
}

