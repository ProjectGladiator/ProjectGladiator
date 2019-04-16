// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Client/MyCharacter/PC/Widget/Inventory/Structure/FInventorySlot.h"
#include "InventorySlotWidget.generated.h"

UCLASS()
class PROJECTJ_API UInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, Meta = (AllowPrivateAccess = true))
		int SlotIndex;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, Meta = (AllowPrivateAccess = true))
		class UButton* InventorySlotButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, Meta = (AllowPrivateAccess = true))
		class UImage* ItemImage;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, Meta = (AllowPrivateAccess = true))
		class UTextBlock* ItemAmount;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ItemInfo, Meta = (AllowPrivateAccess = true))
		FInventorySlot InventorySlotInfo;
public:
	virtual void NativeConstruct() override;

	void UpdateInventorySlot(FInventorySlot SlotInfo);
	
	void SlotIndexInit(int Index);
	
	UFUNCTION()
		void SlotClick();

	FInventorySlot GetInventorySlotInfo();
};
