// Fill out your copyright notice in the Description page of Project Settings.

#include "PartySlotWiget.h"
//클라 헤더
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "Client/MyCharacter/PC/MyCharacter.h"

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
