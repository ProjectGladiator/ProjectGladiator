﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "PartyWidget.h"
//클라 헤더
#include "Components/VerticalBox.h"
#include "PartySlotWiget.h"

//서버 헤더

void UPartyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	VerticalPartySlots = Cast<UVerticalBox>(GetWidgetFromName(TEXT("PartySlots")));
}

UPartySlotWiget* UPartyWidget::PartySlotCreate(AMyCharacter* _MyCharacter)
{
	FStringClassReference PartySlotWidgetClass(TEXT("WidgetBlueprint'/Game/Blueprints/Widget/Party/W_PartySlot.W_PartySlot_C'"));

	if (UClass* MyPartySlotWidgetClass = PartySlotWidgetClass.TryLoadClass<UUserWidget>())
	{
		UPartySlotWiget* PartySlot = Cast<UPartySlotWiget>(CreateWidget<UUserWidget>(GetOwningPlayer(), MyPartySlotWidgetClass));

		if (PartySlot)
		{
			int32 Index = PartySlotWigets.Num();
			FPartySlot SlotInfo;
			SlotInfo.MyCharacter = _MyCharacter;
			PartySlot->SetPartySlotIndex(Index);
			PartySlot->SetPartySlotInfo(SlotInfo);
			PartySlotWigets.Add(PartySlot);
			VerticalPartySlots->AddChild(PartySlot);

			return PartySlot;
		}
		else
		{
			return nullptr;
		}
	}
	else
	{
		return nullptr;
	}
}
