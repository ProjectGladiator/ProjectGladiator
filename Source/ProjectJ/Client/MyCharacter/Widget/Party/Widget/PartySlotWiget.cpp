// Fill out your copyright notice in the Description page of Project Settings.

#include "PartySlotWiget.h"
//클라 헤더
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "Client/MyCharacter/PC/MyCharacter.h"
#include "Client/MyCharacter/Widget/Party/Widget/PartyWidget.h"
#include "Client/MyCharacter/Widget/Party/Widget/PartyInteractionWidget.h"

//서버 헤더
#include "NetWork/JobInfo.h"

void UPartySlotWiget::NativeConstruct()
{
	Super::NativeConstruct();

	PartyReader = false;

	PartyCharacterButton = Cast<UButton>(GetWidgetFromName(TEXT("PartyCharacterButton")));
	NickNameText = Cast<UTextBlock>(GetWidgetFromName(TEXT("CharacterNickName")));
	HPText = Cast<UTextBlock>(GetWidgetFromName(TEXT("CharacterHPText")));
	MPText = Cast<UTextBlock>(GetWidgetFromName(TEXT("CharacterMPText")));
	HPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PartyCharacterHPBar")));
	MPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PartyCharacterMPBar")));
	LeaderImage = Cast<UImage>(GetWidgetFromName(TEXT("LeaderImage")));

	if (LeaderImage)
	{
		LeaderImage->SetVisibility(ESlateVisibility::Hidden);
	}
}

FReply UPartySlotWiget::NativeOnMouseButtonDown(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))
	{
		if (PartyWidget)
		{
			PartyWidget->SetPartyInteraction(PartySlotInfo);
			auto PartyInteractionWidget = PartyWidget->GetPartyInteraction();

			if (PartyInteractionWidget)
			{
				PartyInteractionWidget->SetRenderTranslation(FVector2D(InGeometry.Position.X, InGeometry.Position.Y));
				PartyWidget->PartyInteractionWidgetVisible();
			}
		}
	}
	else
	{
		if (PartyWidget)
		{
			PartyWidget->PartyInteractionWidgetHidden();
		}
	}

	return FReply::Handled();
}

void UPartySlotWiget::PartySlotUpdate(FPartySlot& _PartySlot, int32 _Index)
{
	if (NickNameText)
	{
		PartySlotInfo = _PartySlot;
		PartySlotIndex = _Index;


		NickNameText->SetText(FText::FromString(ANSI_TO_TCHAR(PartySlotInfo.NickName)));

		float HP = PartySlotInfo.HP;
		float MP = PartySlotInfo.MP;

		if (HPText)
		{
			HPText->SetText(FText::FromString(FString::FromInt((int32)(HP))));

			if (MPText)
			{
				MPText->SetText(FText::FromString(FString::FromInt((int32)(MP))));

				if (HPBar)
				{
					float HPPercent = HP / HP;

					HPBar->SetPercent(HPPercent);

					if (MPBar)
					{
						float MPPercent = 0;

						if (PartySlotInfo.JobCode == CHARACTER_JOB::Gunner)
						{
							MPPercent = MP / MP;
						}

						MPBar->SetPercent(MPPercent);

						if (PartySlotInfo.Leader)
						{
							if (LeaderImage)
							{
								LeaderImage->SetVisibility(ESlateVisibility::Visible);
							}
						}
					}
				}
			}
		}
	}
}

void UPartySlotWiget::SetPartyWidget(UPartyWidget * _PartyWidget)
{
	PartyWidget = _PartyWidget;
}
