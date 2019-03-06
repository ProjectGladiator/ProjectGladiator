// Fill out your copyright notice in the Description page of Project Settings.

#include "PartyAcceptRejectWidget.h"
//클라 헤더
#include "Components/Button.h"
#include "Components/TextBlock.h"

//서버 헤더

void UPartyAcceptRejectWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PartyInvitedCharacterNick = Cast<UTextBlock>(GetWidgetFromName(TEXT("PartyInvitedCharacterNick")));
	PartyAcceptButton = Cast<UButton>(GetWidgetFromName(TEXT("PartyAcceptButton")));
	PartyRejectButton = Cast<UButton>(GetWidgetFromName(TEXT("PartyRejectButton")));
}
