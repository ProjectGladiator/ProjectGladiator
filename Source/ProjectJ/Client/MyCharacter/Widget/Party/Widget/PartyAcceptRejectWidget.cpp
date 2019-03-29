// Fill out your copyright notice in the Description page of Project Settings.

#include "PartyAcceptRejectWidget.h"
//클라 헤더
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Client/MyCharacter/PC/MyCharacter.h"
#include "Client/MyCharacter/Widget/MyCharacterUI.h"
#include "Client/MyCharacter/Widget/Party/Party.h"
#include "Client/MainMap/MainMapPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Client/MainMap/MainMapGameMode.h"
#include "Client/MyCharacter/Widget/Party/Widget/PartyWidget.h"

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

void UPartyAcceptRejectWidget::SetPartyRequestCharacterSetInfo(char* _PartyReqCharacterNickName, char* _PartyReqCharacterCode, int32 _PartyRoomNum)
{
	PartyReqCharacterNickName = _PartyReqCharacterNickName;

	memset(PartyReqCharacterCode, 0, sizeof(PartyReqCharacterCode));
	memcpy(PartyReqCharacterCode, _PartyReqCharacterCode, strlen(_PartyReqCharacterCode));

	PartyRoomNum = _PartyRoomNum;

	if (PartyInvitedCharacterNick)
	{
		PartyInvitedCharacterNick->SetText(FText::FromString(ANSI_TO_TCHAR(PartyReqCharacterNickName)));
	}
}

void UPartyAcceptRejectWidget::PartyAccept()
{
	auto MainMapPlayerController = Cast<AMainMapPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (MainMapPlayerController)
	{
		MainMapPlayerController->C2S_ReqPartyAccept(true, PartyReqCharacterCode, PartyRoomNum);
	}

	GLog->Log(FString::Printf(TEXT("파티 수락 버튼 누름")));

	SetVisibility(ESlateVisibility::Hidden);
}

void UPartyAcceptRejectWidget::PartyReject()
{
	auto MainMapPlayerController = Cast<AMainMapPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (MainMapPlayerController)
	{
		MainMapPlayerController->C2S_ReqPartyAccept(false, PartyReqCharacterCode, PartyRoomNum);
	}
	GLog->Log(FString::Printf(TEXT("파티 거절 버튼 누름")));

	SetVisibility(ESlateVisibility::Hidden);
}
