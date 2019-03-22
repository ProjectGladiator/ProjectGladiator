// Fill out your copyright notice in the Description page of Project Settings.

#include "PartyAcceptRejectWidget.h"
//클라 헤더
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Client/MyCharacter/PC/MyCharacter.h"
#include "Client/MyCharacter/Widget/MyCharacterUI.h"
#include "Client/MyCharacter/Widget/Party/Party.h"

//서버 헤더

void UPartyAcceptRejectWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PartyInvitedCharacterNick = Cast<UTextBlock>(GetWidgetFromName(TEXT("PartyInvitedCharacterNick")));
	PartyAcceptButton = Cast<UButton>(GetWidgetFromName(TEXT("PartyAcceptButton")));
	PartyRejectButton = Cast<UButton>(GetWidgetFromName(TEXT("PartyRejectButton")));

	if (PartyAcceptButton)
	{
		PartyAcceptButton->OnClicked.AddDynamic(this, &UPartyAcceptRejectWidget::PartyAccept);
	}

	if (PartyRejectButton)
	{
		PartyRejectButton->OnClicked.AddDynamic(this, &UPartyAcceptRejectWidget::PartyReject);
	}
}

void UPartyAcceptRejectWidget::SetPartyRequestCharacterSetInfo(char* _PartyReqCharacterNickName, char* _PartyReqCharacterCode)
{
	PartyReqCharacterNickName = _PartyReqCharacterNickName;
	PartyReqCharacterCode = _PartyReqCharacterCode;

	if (PartyInvitedCharacterNick)
	{
		PartyInvitedCharacterNick->SetText(FText::FromString(ANSI_TO_TCHAR(PartyReqCharacterNickName)));
	}
}

void UPartyAcceptRejectWidget::PartyAccept()
{
	GLog->Log(FString::Printf(TEXT("파티 수락 버튼 누름")));
}

void UPartyAcceptRejectWidget::PartyReject()
{
	GLog->Log(FString::Printf(TEXT("파티 거절 버튼 누름")));
}
