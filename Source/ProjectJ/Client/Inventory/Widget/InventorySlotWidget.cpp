// Fill out your copyright notice in the Description page of Project Settings.

#include "InventorySlotWidget.h"
//클라 헤더
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Client/Item/MasterItem.h"
#include "Engine/StreamableManager.h"
#include "Engine/Texture2D.h"
//서버 헤더

void UInventorySlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InventorySlotButton = Cast<UButton>(GetWidgetFromName(TEXT("InventorySlotButton")));
	ItemImage = Cast<UImage>(GetWidgetFromName(TEXT("ItemImage")));
	ItemAmount = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemAmount")));
}

void UInventorySlotWidget::UpdateInventorySlot(FSInventorySlot SlotInfo)
{

	if (UKismetSystemLibrary::IsValidClass(SlotInfo.ItemClass->StaticClass()))
	{
		InventorySlotButton->SetIsEnabled(true);
		InventorySlotInfo = SlotInfo;

		if (ItemImage)
		{
			FStreamableManager AssetLoader;

			ItemImage->SetBrushFromTexture(Cast<UTexture2D>(InventorySlotInfo.ItemClass->ItemInfo.ItemThumbnail));
			ItemAmount->SetText(FText::FromString(FString::FromInt(InventorySlotInfo.Amount)));
		}
	}
	else
	{
		InventorySlotButton->SetIsEnabled(false);
		ItemImage->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UInventorySlotWidget::SlotIndexInit(int Index)
{
	SlotIndex = Index;
}




