// Fill out your copyright notice in the Description page of Project Settings.

#include "MyNonPlayerCharacter.h"
//클라 헤더
#include "UObject/ConstructorHelpers.h"
#include "Client/MyCharacter/NPC/Widget/StoreInventory/StoreInventory.h"
//서버 헤더

// Sets default values
AMyNonPlayerCharacter::AMyNonPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;	

	StoreInventoryComponent = CreateDefaultSubobject<UStoreInventory>(TEXT("InventoryComponent"));
}

// Called when the game starts or when spawned
void AMyNonPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AMyNonPlayerCharacter::StoreWidgetToggle()
{
	if (StoreInventoryComponent)
	{
		StoreInventoryComponent->StoreWidgetToggle();
	}
}

// Called every frame
void AMyNonPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyNonPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

