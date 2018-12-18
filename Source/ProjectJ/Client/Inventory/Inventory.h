// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Client/Inventory/Structure/SInventorySlot.h"
#include "Client/Item/DataTable/ItemDataTable.h"
#include "Inventory.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTJ_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventory();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Slots")
		TArray<FSInventorySlot> Slots;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Slots")
		int InventoryMaxCount;

	bool IsSlotEmpty(int Index);
	void GetItemInfo(int Index, FItemDataTable& ItemInfo, bool& IsEmpty);
	void SearchEmptySlot(bool& Success, int& EmptySlotIndex);

};
