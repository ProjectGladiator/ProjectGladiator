// Fill out your copyright notice in the Description page of Project Settings.

#include "Inventory.h"
//클라 헤더
#include "Client/Item/MasterItem.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Client/MyCharacter/Widget/Inventory/Widget/InventoryWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

//서버 헤더


// Sets default values for this component's properties
UInventory::UInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	InventoryMaxCount = 20;

}


// Called when the game starts
void UInventory::BeginPlay()
{
	Super::BeginPlay();

	FStringClassReference InventoryWidgetClass(TEXT("WidgetBlueprint'/Game/Blueprints/Widget/Inventory/Widget/W_Inventory.W_Inventory_C'"));

	if (UClass* MyInventoryWidgetClass = InventoryWidgetClass.TryLoadClass<UUserWidget>())
	{
		InventoryWidget = Cast<UInventoryWidget>(CreateWidget<UUserWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), MyInventoryWidgetClass));
		
		InventoryWidget->AddToViewport(); //화면에 붙인다.
		InventoryWidget->SetVisibility(ESlateVisibility::Hidden); //숨긴다.
	}	
}


// Called every frame
void UInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UInventory::IsSlotEmpty(int Index)
{
	FInventorySlot InventorySlot = Slots[Index];
		
	if (UKismetSystemLibrary::IsValidClass(InventorySlot.ItemClass->StaticClass()))
	{
		return true; //있음
	}
	else
	{
		return false; //없음
	}
}

void UInventory::GetItemInfo(int Index, FItemDataTable& ItemInfo, bool& IsEmpty)
{
	FInventorySlot InventorySlot = Slots[Index];
	
	if (UKismetSystemLibrary::IsValidClass(InventorySlot.ItemClass->StaticClass()))
	{
		IsEmpty = false;
		ItemInfo = Slots[Index].ItemClass->ItemInfo;
	}
	else
	{
		IsEmpty = true;
	}	
}

void UInventory::SearchEmptySlot(bool& Success,int& EmptySlotIndex)
{
	for (int i = 0; i < InventoryMaxCount; i++)
	{
		if (!UKismetSystemLibrary::IsValidClass(Slots[i].ItemClass->StaticClass()))
		{
			EmptySlotIndex = i;
			Success = true;
		}
		else
		{
			EmptySlotIndex = -1;
			Success = false;
		}
	}
}

void UInventory::InventoryWidgetToggle()
{
	if (InventoryWidget)
	{
		if (InventoryWidget->GetVisibility() == ESlateVisibility::Hidden)
		{
			InventoryWidget->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			InventoryWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

int32 UInventory::GetInventoryMaxCount()
{
	return InventoryMaxCount;
}

void UInventory::InventoryCreate(int32 _NewInventoryMaxCount)
{
	InventoryMaxCount = _NewInventoryMaxCount;

	if (InventoryWidget)
	{
		InventoryWidget->CreateInventorySlots();
	}
}

