﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryWidget.h"
//클라 헤더
#include "Components/Button.h"
#include "Components/UniformGridPanel.h"
#include "Client/MyCharacter/PC/MyCharacter.h"
#include "Client/MyCharacter/Widget/Inventory/Inventory.h"
#include "Client/MyCharacter/Widget/Inventory/Widget/InventorySlotWidget.h"
#include "kismet/KismetMathLibrary.h"
#include "Components/UniformGridSlot.h"
#include "Client/MyCharacter/Widget/Inventory/Structure/FInventorySlot.h"
#include "Client/MyCharacter/Widget/MyCharacterUI.h"
//서버 헤더

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	AMyCharacter* MyCharacter = Cast<AMyCharacter>(GetOwningPlayerPawn());
	
	if (MyCharacter)
	{
		Inventory = MyCharacter->GetMyCharacterUI()->GetInventoryComponent();
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
		
		float Column;
		for (float i = 0; i < Inventory->GetInventoryMaxCount(); i=i+1.0f)
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
						InventorySlot->UpdateInventorySlot(InventorySlots[i]->InventorySlotInfo);
					}
				}
			}
		}
	}
}