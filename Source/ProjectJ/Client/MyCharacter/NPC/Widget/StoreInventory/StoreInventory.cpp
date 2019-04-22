// Fill out your copyright notice in the Description page of Project Settings.

#include "StoreInventory.h"
//클라 헤더
#include "Kismet/KismetSystemLibrary.h"
#include "Client/MyCharacter/NPC/Widget/StoreInventory/StoreInventoryWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/Texture2D.h"

//서버 헤더


// Sets default values for this component's properties
UStoreInventory::UStoreInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	InventoryMaxCount = 0;

	static ConstructorHelpers::FObjectFinder<UTexture2D>T_HPPotion(TEXT("TTexture2D'/Game/Assets/Item/Potion/Texture/RedPotion.RedPotion'"));

	if (T_HPPotion.Succeeded())
	{
		HPPotionTexture = T_HPPotion.Object;
	}
}


// Called when the game starts
void UStoreInventory::BeginPlay()
{
	Super::BeginPlay();
	FStringClassReference StoreInventoryWidgetClass(TEXT("WidgetBlueprint'/Game/Blueprints/Widget/Store/W_StoreInventory.W_StoreInventory_C'"));

	if (UClass* MyStoreInventoryWidgetClass = StoreInventoryWidgetClass.TryLoadClass<UUserWidget>())
	{
		StoreInventoryWidget = Cast<UStoreInventoryWidget>(CreateWidget<UUserWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), MyStoreInventoryWidgetClass));
		
		StoreInventoryWidget->AddToViewport(); //화면에 붙인다.
		StoreInventoryWidget->SetVisibility(ESlateVisibility::Hidden); //숨긴다.
	}	
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
	if (StoreInventoryWidget)
	{
		if (StoreInventoryWidget->GetVisibility() == ESlateVisibility::Visible)
		{
			StoreInventoryWidget->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			StoreInventoryWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

int32 UStoreInventory::GetInventoryMaxCount()
{
	return InventoryMaxCount;
}

void UStoreInventory::PotionStoreInventoryCreate()
{
	InventoryMaxCount++;

	FItemInfo NewStoreItem(10,FText::FromString(TEXT("체력 물약")), EItemType::Consumable, 20, 0, 20, HPPotionTexture);

	if (StoreInventoryWidget)
	{
		StoreInventoryWidget->CreateStoreInventorySlots(NewStoreItem);
	}
}

void UStoreInventory::StoreWidgetToggle()
{
	if (StoreInventoryWidget)
	{
		if (StoreInventoryWidget->GetVisibility() == ESlateVisibility::Visible)
		{
			StoreInventoryWidget->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			StoreInventoryWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}
}
