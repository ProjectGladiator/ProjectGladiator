// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryWidget.h"
#include "Components/Button.h"
#include "Components/UniformGridPanel.h"

#include "MyCharacter/MyCharacter.h"
#include "Inventory/Inventory.h"
#include "Inventory/Widget/InventorySlotWidget.h"
#include "kismet/KismetMathLibrary.h"
#include "Components/UniformGridSlot.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	AMyCharacter* MyCharacter = Cast<AMyCharacter>(GetOwningPlayerPawn());

	if (MyCharacter)
	{
		Inventory = MyCharacter->Inventory;
	}

	InventoryGrid = Cast<UUniformGridPanel>(GetWidgetFromName(TEXT("SlotGridPanel")));

	RowColumnValue = 5.0f;
}

void UInventoryWidget::CreateInventorySlots()
{
	if (Inventory)
	{
		InventoryGrid->ClearChildren();
		InventorySlots.Empty();
		
		for (int i = 0; i < Inventory->InventoryMaxCount; i++)
		{
			FStringClassReference InventorySlotWidgetClass(TEXT("WidgetBlueprint'/Game/Blueprints/Widget/Inventory/Widget/W_InventorySlot.W_InventorySlot_C'"));

			if (UClass* MyWidgetClass = InventorySlotWidgetClass.TryLoadClass<UUserWidget>())
			{				
				UInventorySlotWidget* InventorySlot = Cast<UInventorySlotWidget>(CreateWidget<UUserWidget>(GetOwningPlayer(), MyWidgetClass));

				if (InventorySlot)
				{
					InventorySlot->SlotIndexInit(i);
					InventorySlots.Add(InventorySlot);
					UUniformGridSlot* InputGridSlot =InventoryGrid->AddChildToUniformGrid(InventorySlot);

					if (InputGridSlot)
					{
					/*	UKismetMathLibrary::Trun
						i/RowColumnValue*/
					}
				}
			}
		}
	}
}