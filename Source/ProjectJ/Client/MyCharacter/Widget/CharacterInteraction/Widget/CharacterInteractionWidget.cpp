// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterInteractionWidget.h"
//클라 헤더
#include "Components/Button.h"
#include "Client/MainMap/MainMapPlayerController.h"
#include "Client/MainMap/MainMapOtherPlayerController.h"
#include "Client/MyCharacter/PC/MyCharacter.h"
#include "Client/MyCharacter/Widget/MyCharacterUI.h"
#include "Client/MyCharacter/Widget/CharacterInteraction/ClickCharacterInteraction.h"
#include "Client/MyCharacter/Widget/Info/MyCharacterWidget.h"
#include "Client/MyCharacter/Widget/Party/Party.h"
#include "Client/MyCharacter/Widget/Party/Widget/PartyWidget.h"
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

	if (MainMapPlayerController)
	{
		auto MyCharacter = Cast<AMyCharacter>(MainMapPlayerController->GetPawn());

		if (MyCharacter)
		{
			auto MainMapGameMode = Cast<AMainMapGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

			if (MainMapGameMode)
			{
				if (MyCharacter->GetMyCharacterUI()->GetPartyComponent()->GetPartyWidget()->GetVisibility() == ESlateVisibility::Visible)
				{
					if (MyCharacter->GetPartyLeader())
					{
						PartyInVite(MyCharacter, MainMapGameMode);
					}
					else
					{
						MainMapGameMode->OkWidgetToggle(FText::FromString(FString::Printf(TEXT("You're Not Leader"))));
					}
				}
				else
				{
					PartyInVite(MyCharacter, MainMapGameMode);
				}
			}
		}
	}
	else
	{
		GLog->Log(FString::Printf(TEXT("MainMapPlayerController이 없음")));
	}
}

void UCharacterInteractionWidget::Init(APlayerController* _MainMapPlayerController)
{
	MainMapPlayerController = Cast<AMainMapPlayerController>(_MainMapPlayerController);	
}

void UCharacterInteractionWidget::PartyInVite(AMyCharacter* _MyCharacter,AMainMapGameMode* _MainMapGameMode)
{
	auto ClickCharacter = _MyCharacter->GetClickCharacter();

	if (ClickCharacter)
	{
		bool IsOtherCharacterPartyJoin = ClickCharacter->GetMyCharacterUI()->GetPartyComponent()->IsPartyJoin();
		bool IsMyCharacterPartyJoin = _MyCharacter->GetMyCharacterUI()->GetPartyComponent()->IsPartyJoin();

		if (IsOtherCharacterPartyJoin)
		{
			if (IsMyCharacterPartyJoin)
			{
				MainMapPlayerController->C2S_ReqPartyJoin(ClickCharacter->GetCharacterCode());
				SetVisibility(ESlateVisibility::Hidden);
			}
			else
			{
				_MainMapGameMode->OkWidgetToggle(FText::FromString(FString::Printf(TEXT("MyCharacter Party Full"))));
			}
		}
		else
		{
			_MainMapGameMode->OkWidgetToggle(FText::FromString(FString::Printf(TEXT("OtherCharacter Party Full"))));
		}
	}
}
