// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacterUI.h"
//클라 헤더
#include "Kismet/GameplayStatics.h"
#include "Client/MyCharacter/Widget/Inventory/Inventory.h"
#include "Client/MyCharacter/Widget/Party/Party.h"
//서버 헤더

// Sets default values for this component's properties
UMyCharacterUI::UMyCharacterUI()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	InventoryComponent = CreateDefaultSubobject<UInventory>(TEXT("Inventory"));
	PartyComponent = CreateDefaultSubobject<UParty>(TEXT("Party"));
}


// Called when the game starts
void UMyCharacterUI::BeginPlay()
{
	Super::BeginPlay();

	// ...	
}


// Called every frame
void UMyCharacterUI::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMyCharacterUI::SetMyCharacterUI()
{
	if (InventoryComponent)
	{
		InventoryComponent->InventoryCreate(20);
	}
}

UInventory* UMyCharacterUI::GetInventoryComponent()
{
	return InventoryComponent;
}

UParty * UMyCharacterUI::GetPartyComponent()
{
	return PartyComponent;
}