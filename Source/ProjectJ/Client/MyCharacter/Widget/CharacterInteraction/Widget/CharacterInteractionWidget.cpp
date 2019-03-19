// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterInteractionWidget.h"
//클라 헤더
#include "Components/Button.h"
#include "Client/MainMap/MainMapPlayerController.h"
#include "Client/MyCharacter/PC/MyCharacter.h"
#include "Client/MyCharacter/Widget/MyCharacterUI.h"
#include "Client/MyCharacter/Widget/CharacterInteraction/ClickCharacterInteraction.h"
#include "Client/MyCharacter/Widget/CharacterInteraction/Structure/FClickCharacterInfo.h"
#include "Client/MyCharacter/Widget/Party/Party.h"
#include "Client/MyCharacter/Widget/Party/Widget/PartyAcceptRejectWidget.h"

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
}

void UCharacterInteractionWidget::Trade()
{
	GLog->Log(FString::Printf(TEXT("거래하기 버튼 시작")));
}

void UCharacterInteractionWidget::Party()
{
	GLog->Log(FString::Printf(TEXT("파티맺기 버튼 시작")));

	auto MainMapPlayerController = Cast<AMainMapPlayerController>(GetOwningPlayer());

	if (MainMapPlayerController)
	{
		GLog->Log(FString::Printf(TEXT("메인맵 플레이어 컨트롤러 존재")));

		auto MyCharacter = Cast<AMyCharacter>(MainMapPlayerController->GetPawn());

		if (MyCharacter)
		{
			/*if (MyCharacter->GetMyCharacterUI()->GetPartyComponent()->IsPartyJoin())
			{
				
			}
			else
			{
				GLog->Log(FString::Printf(TEXT("파티원이 꽉 참")));
			}*/
		}
		else
		{
			GLog->Log(FString::Printf(TEXT("플레이어 캐릭터 존재하지 않음")));
		}
	}
	else
	{
		GLog->Log(FString::Printf(TEXT("메인맵 플레이어 컨트롤러 존재 하지 않음")));
	}
}