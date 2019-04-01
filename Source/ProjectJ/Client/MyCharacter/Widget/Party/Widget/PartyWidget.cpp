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
		GLog->Log(FString::Printf(TEXT("PartyInteraction 잇음")));
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

void UPartyWidget::SetPartyInteraction(FPartySlot& _PartySlotInfo)
{
	PartyInteraction->SetPartyInteractionWidget(_PartySlotInfo);
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
