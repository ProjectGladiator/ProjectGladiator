// Fill out your copyright notice in the Description page of Project Settings.

#include "StoreInventory.h"
//클라 헤더
#include "Kismet/KismetSystemLibrary.h"
#include "Client/MyCharacter/NPC/Widget/StoreInventory/StoreInventoryWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

//서버 헤더


// Sets default values for this component's properties
UStoreInventory::UStoreInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	InventoryMaxCount = 20;
}


// Called when the game starts
void UStoreInventory::BeginPlay()
{
	Super::BeginPlay();
	//FStringClassReference InventoryWidgetClass(TEXT("WidgetBlueprint'/Game/Blueprints/Widget/Inventory/Widget/W_Inventory.W_Inventory_C'"));

	//if (UClass* MyInventoryWidgetClass = InventoryWidgetClass.TryLoadClass<UUserWidget>())
	//{
	//	InventoryWidget = Cast<UInventoryWidget>(CreateWidget<UUserWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), MyInventoryWidgetClass));
	//	
	//	InventoryWidget->AddToViewport(); //화면에 붙인다.
	//	InventoryWidget->SetVisibility(ESlateVisibility::Hidden); //숨긴다.
	//}	
}


// Called every frame
void UStoreInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

//bool UStoreInventory::IsSlotEmpty(int Index)
//{
//	FInventorySlot InventorySlot = Slots[Index];
//		
//	if (UKismetSystemLibrary::IsValidClass(InventorySlot.ItemClass->StaticClass()))
//	{
//		return true; //있음
//	}
//	else
//	{
//		return false; //없음
//	}
//}

//void UStoreInventory::GetItemInfo(int Index, FItemDataTable& ItemInfo, bool& IsEmpty)
//{
//	FInventorySlot InventorySlot = Slots[Index];
//	
//	if (UKismetSystemLibrary::IsValidClass(InventorySlot.ItemClass->StaticClass()))
//	{
//		IsEmpty = false;
//		ItemInfo = Slots[Index].ItemClass->ItemInfo;
//	}
//	else
//	{
//		IsEmpty = true;
//	}	
//}

//void UStoreInventory::SearchEmptySlot(bool& Success,int& EmptySlotIndex)
//{
//	for (int i = 0; i < InventoryMaxCount; i++)
//	{
//		if (!UKismetSystemLibrary::IsValidClass(Slots[i].ItemClass->StaticClass()))
//		{
//			EmptySlotIndex = i;
//			Success = true;
//		}
//		else
//		{
//			EmptySlotIndex = -1;
//			Success = false;
//		}
//	}
//}

void UStoreInventory::InventoryWidgetToggle()
{
	if (InventoryWidget)
	{
		
	}
}

UInventoryWidget * UStoreInventory::GetInventoryWidget()
{
	return InventoryWidget;
}

int32 UStoreInventory::GetInventoryMaxCount()
{
	return InventoryMaxCount;
}

void UStoreInventory::InventoryCreate(int32 _NewInventoryMaxCount)
{
	InventoryMaxCount = _NewInventoryMaxCount;

	if (InventoryWidget)
	{
		//InventoryWidget->CreateInventorySlots(InventoryMaxCount);
	}
}

