// Fill out your copyright notice in the Description page of Project Settings.

#include "PartyWidget.h"
//클라 헤더
#include "Components/VerticalBox.h"
#include "PartySlotWiget.h"
#include "Kismet/GameplayStatics.h"
#include "Client/MyCharacter/Widget/Party/Widget/PartyInteractionWidget.h"
//서버 헤더

void UPartyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	VerticalPartySlots = Cast<UVerticalBox>(GetWidgetFromName(TEXT("PartySlots")));

	PartyInteraction = Cast<UPartyInteractionWidget>(GetWidgetFromName(TEXT("PartyInteraction")));

	if (PartyInteraction)
	{
		PartyInteraction->SetVisibility(ESlateVisibility::Hidden);
	}
}

UPartySlotWiget* UPartyWidget::PartySlotCreate()
{
	FStringClassReference PartySlotWidgetClass(TEXT("WidgetBlueprint'/Game/Blueprints/Widget/Party/W_PartySlot.W_PartySlot_C'"));

	if (UClass* MyPartySlotWidgetClass = PartySlotWidgetClass.TryLoadClass<UUserWidget>())
	{
		UPartySlotWiget* PartySlot = Cast<UPartySlotWiget>(CreateWidget<UUserWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), MyPartySlotWidgetClass));
		
		if (PartySlot)
		{
			PartySlot->SetPartyWidget(this);
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

void UPartyWidget::SetPartyInteraction(bool _IsMyPartySlot, FPartySlot& _PartySlotInfo)
{
	PartyInteraction->SetPartyInteractionWidget(_IsMyPartySlot,_PartySlotInfo);
}

UPartyInteractionWidget * UPartyWidget::GetPartyInteraction()
{
	return PartyInteraction;
}

void UPartyWidget::PartyInteractionWidgetVisible()
{
	PartyInteraction->SetVisibility(ESlateVisibility::Visible);
}

void UPartyWidget::PartyInteractionWidgetHidden()
{
	PartyInteraction->SetVisibility(ESlateVisibility::Hidden);
}

void UPartyWidget::PartyLeave()
{
	for (int i = 0; i < PartySlotWigets.Num(); i++)
	{
		PartySlotWigets[i]->RemoveFromParent();
	}
	
	PartySlotWigets.Empty();

	SetVisibility(ESlateVisibility::Hidden);
}

void UPartyWidget::PartyLeave(char * _CharacterCode)
{
	for (int i = 0; i < PartySlotWigets.Num(); i++)
	{
		FPartySlot SlotInfo = PartySlotWigets[i]->GetPartySlotInfo();

		if (strcmp(SlotInfo.CharacterCode, _CharacterCode) == 0)
		{
			PartySlotWigets[i]->RemoveFromParent();
			PartySlotWigets.RemoveAt(i);
		}
	}
}

void UPartyWidget::PartyLeaderUpdate()
{
	for (int i = 0; i < PartySlotWigets.Num(); i++)
	{
		PartySlotWigets[i]->PartySlotLeaderUpdate();
	}
}
