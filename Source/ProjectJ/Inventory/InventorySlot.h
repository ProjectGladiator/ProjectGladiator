// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inventory/Structure/SInventorySlot.h"
#include "InventorySlot.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API UInventorySlot : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
		class UButton* InventorySlotButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
		class UImage* ItemImage;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
		class UTextBlock* ItemAmount;	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ItemInfo")
		FSInventorySlot InventorySlotInfo;
	 
	virtual void NativeConstruct() override;

	void UpdateInventorySlot(FSInventorySlot SlotInfo);
};
