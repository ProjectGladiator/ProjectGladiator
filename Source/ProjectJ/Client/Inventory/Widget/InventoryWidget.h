// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
		class UInventory* Inventory;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UUniformGridPanel* InventoryGrid;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TArray<class UInventorySlotWidget*> InventorySlots;

	float RowColumnValue;

	virtual void NativeConstruct() override;

	void CreateInventorySlots(); //인벤토리 슬롯위젯을 생성해주는 함수
	
};
