// Fill out your copyright notice in the Description page of Project Settings.

#include "DataTableComponent.h"
#include "UObject/ConstructorHelpers.h"


// Sets default values for this component's properties
UDataTableComponent::UDataTableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	//けいしかいしぉけいしけいし
	static ConstructorHelpers::FObjectFinder<UDataTable>DT_Item(TEXT("DataTable'/Game/Assets/Item/ItemDataTable.ItemDataTable'"));

	if (DT_Item.Succeeded())
	{
		DataTable = DT_Item.Object;
	}
}


// Called when the game starts
void UDataTableComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	

}


// Called every frame
void UDataTableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

FItemDataTable & UDataTableComponent::GetItemData(int ItemIndex)
{
	return *DataTable->FindRow<FItemDataTable>(*FString::FromInt(ItemIndex), TEXT("ItemIndex"));
}

