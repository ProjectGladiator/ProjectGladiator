// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Client/Item/Struct/FItemInfo.h"
#include "StoreInventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API UStoreInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, Meta = (AllowPrivateAccess = true))
		class UTextBlock* StoreNameText;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, Meta = (AllowPrivateAccess = true))
		class UButton* StoreCloseButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, Meta = (AllowPrivateAccess = true))
		class UScrollBox* StoreInventoryScrollBox;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, Meta = (AllowPrivateAccess = true))
		TArray<class UStoreInventorySlotWidget*> StoreInventorySlots;
public:
	virtual void NativeConstruct() override;

	void CreateStoreInventorySlots(FItemInfo& ItemInfo);

	UFUNCTION()
		void CloseStoreInventory();
};
