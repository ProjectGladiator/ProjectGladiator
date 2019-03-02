// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacterUI.h"
//클라 헤더
#include "Client/MyCharacter/Widget/Inventory/Inventory.h"
//서버 헤더

// Sets default values for this component's properties
UMyCharacterUI::UMyCharacterUI()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	Inventory = CreateDefaultSubobject<UInventory>(TEXT("Inventory"));
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

