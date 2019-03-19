// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacterUI.h"
//클라 헤더
#include "Kismet/GameplayStatics.h"
#include "Client/MyCharacter/Widget/Inventory/Inventory.h"
#include "Client/MyCharacter/Widget/Party/Party.h"
#include "Client/MyCharacter/Widget/CharacterInteraction/ClickCharacterInteraction.h"
#include "Client/MyCharacter/Widget/Inventory/Widget/InventoryWidget.h"
#include "Client/MyCharacter/Widget/Party/Widget/PartyWidget.h"
#include "Client/MyCharacter/Widget/CharacterInteraction/Widget/MyCharacterWidget.h"
//서버 헤더

// Sets default values for this component's properties
UMyCharacterUI::UMyCharacterUI()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	InventoryComponent = CreateDefaultSubobject<UInventory>(TEXT("Inventory"));
	PartyComponent = CreateDefaultSubobject<UParty>(TEXT("Party"));
	MyCharacterInteraction = CreateDefaultSubobject<UClickCharacterInteraction>(TEXT("ClickCharacterIntreaciton"));
}


// Called when the game starts
void UMyCharacterUI::BeginPlay()
{
	Super::BeginPlay();

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

UClickCharacterInteraction * UMyCharacterUI::GetMyCharacterInteraction()
{
	return MyCharacterInteraction;
}

void UMyCharacterUI::AllUIWidgetHidden()
{
	MyCharacterInteraction->GetMyCharacterWidget()->RemoveFromParent(); 
	InventoryComponent->GetInventoryWidget()->RemoveFromParent();
	PartyComponent->GetPartyWidget()->RemoveFromParent();
}