// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryWidget.h"
//클라 헤더
#include "Components/Button.h"
#include "Components/UniformGridPanel.h"
#include "Components/TextBlock.h"
#include "Client/MyCharacter/PC/Widget/Inventory/Widget/InventorySlotWidget.h"
#include "kismet/KismetMathLibrary.h"
#include "Components/UniformGridSlot.h"
#include "Client/MainMap/MainMapPlayerController.h"
#include "Kismet/GameplayStatics.h"
//서버 헤더

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InventoryGrid = Cast<UUniformGridPanel>(GetWidgetFromName(TEXT("SlotGridPanel")));
	CloseButton = Cast<UButton>(GetWidgetFromName(TEXT("CloseButton")));
	MoneyText = Cast<UTextBlock>(GetWidgetFromName(TEXT("MoneyText")));
	RowColumnValue = 5.0f;
}

void UInventoryWidget::CreateInventorySlots(int32 _InventoryNum)
{
	InventoryGrid->ClearChildren();
	InventorySlots.Empty();

	float Column;
	for (float i = 0; i < _InventoryNum; i = i + 1.0f)
	{
		FStringClassReference InventorySlotWidgetClass(TEXT("WidgetBlueprint'/Game/Blueprints/Widget/Inventory/Widget/W_InventorySlot.W_InventorySlot_C'"));

		if (UClass* MyInventorySlotWidgetClass = InventorySlotWidgetClass.TryLoadClass<UUserWidget>())
		{
			UInventorySlotWidget* InventorySlot = Cast<UInventorySlotWidget>(CreateWidget<UUserWidget>(GetOwningPlayer(), MyInventorySlotWidgetClass));

			if (InventorySlot)
			{
				InventorySlot->SlotIndexInit(i);
				InventorySlots.Add(InventorySlot);
				UUniformGridSlot* InputGridSlot = InventoryGrid->AddChildToUniformGrid(InventorySlot);

				if (InputGridSlot)
				{
					InputGridSlot->SetRow(UKismetMathLibrary::FTrunc(i / RowColumnValue));
					UKismetMathLibrary::FMod(i, RowColumnValue, Column);
					InputGridSlot->SetColumn(UKismetMathLibrary::FTrunc(Column));
					InventorySlot->UpdateInventorySlot();
				}
			}
		}
	}
}

void UInventoryWidget::MoneyUpdate(int32 _NewMoney)
{
	if (MoneyText)
	{
		MoneyText->SetText(FText::FromString(FString::FromInt(_NewMoney)));
	}
}

void UInventoryWidget::CloseInventory()
{
	if (CloseButton)
	{
		SetVisibility(ESlateVisibility::Hidden);
	}
}
