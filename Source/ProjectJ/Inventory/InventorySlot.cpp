// Fill out your copyright notice in the Description page of Project Settings.

#include "InventorySlot.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Item/MasterItem.h"
#include "Engine/StreamableManager.h"
#include "Engine/Texture2D.h"

void UInventorySlot::NativeConstruct()
{
	Super::NativeConstruct();

	InventorySlotButton = Cast<UButton>(GetWidgetFromName(TEXT("InventorySlotButton")));
	ItemImage = Cast<UImage>(GetWidgetFromName(TEXT("ItemImage")));
	ItemAmount = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemAmount")));
}

void UInventorySlot::UpdateInventorySlot(FSInventorySlot SlotInfo)
{
	
	if (UKismetSystemLibrary::IsValidClass(SlotInfo.ItemClass->StaticClass()))
	{
		InventorySlotButton->SetIsEnabled(true);
		InventorySlotInfo = SlotInfo;

		if (ItemImage)
		{
			FStreamableManager AssetLoader;

			ItemImage->SetBrushFromTexture(AssetLoader.LoadSynchronous<UTexture2D>(InventorySlotInfo.ItemClass->ItemInfo.ItemThumbnail)); 
			ItemAmount->SetText(FText::FromString(FString::FromInt(InventorySlotInfo.Amount)));
		}
	}
	else
	{
		InventorySlotButton->SetIsEnabled(false);
		ItemImage->SetVisibility(ESlateVisibility::Hidden);
	}
}
