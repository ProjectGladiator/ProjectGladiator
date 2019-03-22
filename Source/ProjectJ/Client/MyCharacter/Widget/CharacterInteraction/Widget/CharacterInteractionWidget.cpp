﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterInteractionWidget.h"
//클라 헤더
#include "Components/Button.h"
#include "Client/MainMap/MainMapPlayerController.h"
#include "Client/MainMap/MainMapOtherPlayerController.h"
#include "Client/MyCharacter/PC/MyCharacter.h"
#include "Client/MyCharacter/Widget/MyCharacterUI.h"
#include "Client/MyCharacter/Widget/CharacterInteraction/ClickCharacterInteraction.h"
#include "Client/MyCharacter/Widget/CharacterInteraction/Widget/MyCharacterWidget.h"
#include "Client/MyCharacter/Widget/Party/Party.h"
#include "Kismet/GameplayStatics.h"
#include "Client/MainMap/MainMapGameMode.h"
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

	auto MyPlayerController = Cast<AMainMapPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (MyPlayerController)
	{
		auto MyCharacter = Cast<AMyCharacter>(MyPlayerController->GetPawn());

		if (MyCharacter)
		{
			auto ClickCharacter = MyCharacter->GetClickCharacter();

			if (ClickCharacter)
			{
				auto MainMapPlayerController = Cast<AMainMapPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

				if (MainMapPlayerController)
				{
					auto MyCharacter = Cast<AMyCharacter>(MainMapPlayerController->GetPawn());

					if (MyCharacter)
					{
						bool IsOtherCharacterPartyJoin = ClickCharacter->GetMyCharacterUI()->GetPartyComponent()->IsPartyJoin();
						bool IsMyCharacterPartyJoin = MyCharacter->GetMyCharacterUI()->GetPartyComponent()->IsPartyJoin();

						auto MainMapGameMode = Cast<AMainMapGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

						if (MainMapGameMode)
						{
							if (IsOtherCharacterPartyJoin)
							{
								if (IsMyCharacterPartyJoin)
								{
									MainMapPlayerController->C2S_ReqPartyJoin(ClickCharacter->GetCharacterCode());
									SetVisibility(ESlateVisibility::Hidden);
								}
								else
								{
									MainMapGameMode->OkWidgetToggle(FText::FromString(FString::Printf(TEXT("MyCharacter Party Full"))));
								}
							}
							else
							{
								MainMapGameMode->OkWidgetToggle(FText::FromString(FString::Printf(TEXT("OtherCharacter Party Full"))));
							}
						}
						else
						{
							GLog->Log(FString::Printf(TEXT("UCharacterInteractionWidget Party MainMapGameMode 없음")));
						}
					}
				}
			}
		}
	}
}