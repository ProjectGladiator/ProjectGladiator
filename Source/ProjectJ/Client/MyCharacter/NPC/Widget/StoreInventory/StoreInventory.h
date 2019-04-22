// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Client/MyCharacter/PC/Widget/Inventory/Structure/FInventorySlot.h"
#include "StoreInventory.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJECTJ_API UStoreInventory : public UActorComponent
{
	GENERATED_BODY()
public:
	// Sets default values for this component's properties
	UStoreInventory();
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = InventoryWidget, Meta = (AllowPrivateAccess = true))
		class UStoreInventoryWidget* StoreInventoryWidget;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Info, Meta = (AllowPrivateAccess = true))
		int32 InventoryMaxCount;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = InventoryWidget, Meta = (AllowPrivateAccess = true))
		TArray<FInventorySlot> Slots;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = InventoryWidget, Meta = (AllowPrivateAccess = true))
		class UTexture2D* HPPotionTexture;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//bool IsSlotEmpty(int Index);

	//void GetItemInfo(int Index, FItemDataTable& ItemInfo, bool& IsEmpty);

	//void SearchEmptySlot(bool& Success, int& EmptySlotIndex);

	void InventoryWidgetToggle();

	int32 GetInventoryMaxCount();

	void PotionStoreInventoryCreate();

	void StoreWidgetToggle();
};
