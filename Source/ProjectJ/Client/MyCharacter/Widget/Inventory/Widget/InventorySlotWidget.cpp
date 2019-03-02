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

	if (InventorySlotButton)
	{
		InventorySlotButton->OnClicked.AddDynamic(this, &UInventorySlotWidget::SlotClick);
	}	
}

void UInventorySlotWidget::UpdateInventorySlot(FInventorySlot SlotInfo)
{
	if (SlotInfo.ItemClass)
	{
		GLog->Log(FString::Printf(TEXT("슬롯 정보 있음")));
	}
	else
	{
		InventorySlotButton->SetIsEnabled(false);
		ItemAmount->SetVisibility(ESlateVisibility::Hidden);
		ItemImage->SetVisibility(ESlateVisibility::Hidden);
	}

	//if (UKismetSystemLibrary::IsValidClass(SlotInfo.ItemClass->StaticClass()))
	//{
	//	
	//	InventorySlotButton->SetIsEnabled(false);
	//	ItemImage->SetVisibility(ESlateVisibility::Hidden);

	//	//InventorySlotButton->SetIsEnabled(true);
	//	//InventorySlotInfo = SlotInfo;

	//	if (ItemImage)
	//	{
	//	/*	FStreamableManager AssetLoader;

	//		ItemImage->SetBrushFromTexture(Cast<UTexture2D>(InventorySlotInfo.ItemClass->ItemInfo.ItemThumbnail));
	//		ItemAmount->SetText(FText::FromString(FString::FromInt(InventorySlotInfo.Amount)));*/
	//	}
	//}
	//else
	//{
	//	InventorySlotButton->SetIsEnabled(false);
	//	ItemImage->SetVisibility(ESlateVisibility::Hidden);
	//}
}

void UInventorySlotWidget::SlotIndexInit(int Index)
{
	SlotIndex = Index;
}

void UInventorySlotWidget::SlotClick()
{
	GLog->Log(FString::Printf(TEXT("Slot Index : %d"), SlotIndex));
}




