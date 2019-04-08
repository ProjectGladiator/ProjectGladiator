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
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, Meta = (AllowPrivateAccess = true))
		class UUniformGridPanel* InventoryGrid;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, Meta = (AllowPrivateAccess = true))
		class UButton* CloseButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, Meta = (AllowPrivateAccess = true))
		class UTextBlock* MoneyText;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, Meta = (AllowPrivateAccess = true))
		TArray<class UInventorySlotWidget*> InventorySlots;
	float RowColumnValue;

public:
	virtual void NativeConstruct() override;

	void CreateInventorySlots(int32 _InventoryNum); //인벤토리 슬롯위젯을 생성해주는 함수
	void MoneyUpdate(int32 _NewMoney);

	UFUNCTION()
		void CloseInventory();
};