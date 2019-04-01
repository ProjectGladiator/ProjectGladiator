// Fill out your copyright notice in the Description page of Project Settings.

#include "PartyInteractionWidget.h"
//클라 헤더
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Client/MyCharacter/PC/MyCharacter.h"
#include "Kismet/GameplayStatics.h"
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
		PartyExitButton->OnClicked.AddDynamic(this, &UPartyInteractionWidget::PartyExit);
	}
}

void UPartyInteractionWidget::SetPartyInteractionWidget(FPartySlot & _PartySlotInfo)
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
				PartyLeaderDelegateButton->SetVisibility(ESlateVisibility::Visible);
			}

			if (PartyKickButton)
			{
				PartyKickButton->SetVisibility(ESlateVisibility::Visible);
			}
		}
		else
		{
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
	SetVisibility(ESlateVisibility::Hidden);
}

void UPartyInteractionWidget::PartyKick()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UPartyInteractionWidget::PartyExit()
{
	SetVisibility(ESlateVisibility::Hidden);
}
