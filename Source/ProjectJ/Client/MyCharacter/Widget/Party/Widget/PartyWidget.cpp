// Fill out your copyright notice in the Description page of Project Settings.

#include "PartyWidget.h"
//클라 헤더
#include "Components/VerticalBox.h"

//서버 헤더

void UPartyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	VerticalPartySlots = Cast<UVerticalBox>(GetWidgetFromName(TEXT("PartySlots")));
}
