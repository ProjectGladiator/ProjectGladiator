// Fill out your copyright notice in the Description page of Project Settings.

#include "StoreInventoryWidget.h"
//클라 헤더
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"

//서버 헤더
void UStoreInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	StoreNameText = Cast<UTextBlock>(GetWidgetFromName(TEXT("StoreNameText")));
	StoreCloseButton = Cast<UButton>(GetWidgetFromName(TEXT("StoreCloseButton")));
	StoreInventoryScrollBox = Cast<UScrollBox>(GetWidgetFromName(TEXT("StoreInventoryScrollBox")));
}

void UStoreInventoryWidget::CreateStoreInventorySlots()
{

}

void UStoreInventoryWidget::CloseStoreInventory()
{
	SetVisibility(ESlateVisibility::Hidden);
}
