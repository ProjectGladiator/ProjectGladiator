// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Client/MyCharacter/Widget/Inventory/Structure/FInventorySlot.h"
#include "InventorySlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API UInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
		int SlotIndex;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
		class UButton* InventorySlotButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
		class UImage* ItemImage;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
		class UTextBlock* ItemAmount;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ItemInfo")
		FInventorySlot InventorySlotInfo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
		class UInventory* Inventory;

	virtual void NativeConstruct() override;

	void UpdateInventorySlot(FInventorySlot SlotInfo);
	
	void SlotIndexInit(int Index);
	
	UFUNCTION()
		void SlotClick();
};
