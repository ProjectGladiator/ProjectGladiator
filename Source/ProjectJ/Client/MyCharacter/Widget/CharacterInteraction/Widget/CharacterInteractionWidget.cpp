// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterInteractionWidget.h"
//클라 헤더
#include "Components/Button.h"
#include "Client/MainMap/MainMapOtherPlayerController.h"
#include "Client/MyCharacter/PC/MyCharacter.h"
//서버 헤더

void UCharacterInteractionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	TradeButton = Cast<UButton>(GetWidgetFromName(TEXT("TradeButton")));
	PartyButton = Cast<UButton>(GetWidgetFromName(TEXT("PartyButton")));

	if (TradeButton)
	{
		TradeButton->OnClicked.AddDynamic(this, &UCharacterInteractionWidget::Trade);
	}

	if (PartyButton)
	{
		PartyButton->OnClicked.AddDynamic(this, &UCharacterInteractionWidget::Party);
	}
}

void UCharacterInteractionWidget::Trade()
{
	GLog->Log(FString::Printf(TEXT("거래하기 버튼 시작")));
}

void UCharacterInteractionWidget::Party()
{
	GLog->Log(FString::Printf(TEXT("파티맺기 버튼 시작")));
}