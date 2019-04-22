// Fill out your copyright notice in the Description page of Project Settings.

#include "StoreInventorySlotWidget.h"
//클라 헤더
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
//서버 헤더

void UStoreInventorySlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	StoreInventorySlotButton = Cast<UButton>(GetWidgetFromName(TEXT("StoreInventorySlotButton")));
	ItemImage = Cast<UImage>(GetWidgetFromName(TEXT("ItemImage")));
	ItemNameText = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemNameText")));
	ItemPriceText = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemPriceText")));
}

FReply UStoreInventorySlotWidget::NativeOnMouseButtonDown(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))
	{
		GLog->Log(FString::Printf(TEXT("상점 아이템 오른쪽 클릭")));
	}

	return FReply::Handled();
}

void UStoreInventorySlotWidget::Init(FItemInfo& _SlotInfo)
{
	StoreInventorySlotInfo = _SlotInfo;

	if (ItemImage)
	{
		ItemImage->SetBrushFromTexture(StoreInventorySlotInfo.ItemThumbnail);
	}

	if (ItemNameText)
	{
		ItemNameText->SetText(StoreInventorySlotInfo.ItemNameText);
	}

	if (ItemPriceText)
	{
		ItemPriceText->SetText(FText::FromString(FString::FromInt(StoreInventorySlotInfo.ItemPrice)));
	}
}
