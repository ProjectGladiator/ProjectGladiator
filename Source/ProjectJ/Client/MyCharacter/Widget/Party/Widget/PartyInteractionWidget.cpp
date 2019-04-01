﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "PartyInteractionWidget.h"
//클라 헤더
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Client/MyCharacter/PC/MyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Client/MainMap/MainMapPlayerController.h"
//서버 헤더

void UPartyInteractionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	NickNameText = Cast<UTextBlock>(GetWidgetFromName(TEXT("NickNameText")));
	PartyLeaderDelegateButton = Cast<UButton>(GetWidgetFromName(TEXT("PartyLeaderDelegateButton")));

	if (PartyLeaderDelegateButton)
	{
		PartyLeaderDelegateButton->OnClicked.AddDynamic(this, &UPartyInteractionWidget::PartyLeaderDelegate);
	}

	PartyKickButton = Cast<UButton>(GetWidgetFromName(TEXT("PartyKickButton")));

	if (PartyKickButton)
	{
		PartyKickButton->OnClicked.AddDynamic(this, &UPartyInteractionWidget::PartyKick);
	}

	PartyExitButton = Cast<UButton>(GetWidgetFromName(TEXT("PartyExitButton")));

	if (PartyExitButton)
	{
		PartyExitButton->OnClicked.AddDynamic(this, &UPartyInteractionWidget::PartyLeave);
	}
}

void UPartyInteractionWidget::SetPartyInteractionWidget(bool _IsMyPartySlot, FPartySlot & _PartySlotInfo)
{
	PartySlotInfo = _PartySlotInfo;

	if (NickNameText)
	{
		NickNameText->SetText(FText::FromString(ANSI_TO_TCHAR(PartySlotInfo.NickName)));
	}

	auto MyCharacter = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (MyCharacter)
	{
		bool IsPartyLeader = MyCharacter->GetPartyLeader();

		if (IsPartyLeader)
		{
			if (PartyLeaderDelegateButton)
			{
				if (_IsMyPartySlot)
				{
					PartyLeaderDelegateButton->SetVisibility(ESlateVisibility::Collapsed);
				}
				else
				{
					PartyLeaderDelegateButton->SetVisibility(ESlateVisibility::Visible);
				}
			}

			if (PartyKickButton)
			{
				PartyKickButton->SetVisibility(ESlateVisibility::Visible);
			}
		}
		else
		{
			if (NickNameText)
			{
				if (_IsMyPartySlot)
				{
					NickNameText->SetVisibility(ESlateVisibility::Collapsed);
				}
				else
				{
					NickNameText->SetVisibility(ESlateVisibility::Visible);
				}
			}

			if (PartyLeaderDelegateButton)
			{
				PartyLeaderDelegateButton->SetVisibility(ESlateVisibility::Collapsed);
			}

			if (PartyKickButton)
			{
				PartyKickButton->SetVisibility(ESlateVisibility::Collapsed);
			}
		}
	}
}

void UPartyInteractionWidget::PartyLeaderDelegate()
{
	auto MainMapPlayerController = Cast<AMainMapPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (MainMapPlayerController)
	{
		MainMapPlayerController->C2S_ReqPartyLeaderDelegate(PartySlotInfo.CharacterCode);
		SetVisibility(ESlateVisibility::Hidden);
	}
}

void UPartyInteractionWidget::PartyKick()
{
	auto MainMapPlayerController = Cast<AMainMapPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (MainMapPlayerController)
	{
		MainMapPlayerController->C2S_ReqPartyKick(PartySlotInfo.CharacterCode);
		SetVisibility(ESlateVisibility::Hidden);
	}
}

void UPartyInteractionWidget::PartyLeave()
{
	auto MainMapPlayerController = Cast<AMainMapPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (MainMapPlayerController)
	{
		MainMapPlayerController->C2S_ReqPartyLeave();
		SetVisibility(ESlateVisibility::Hidden);
	}
}
