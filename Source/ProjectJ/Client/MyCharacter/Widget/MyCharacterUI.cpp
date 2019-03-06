﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacterUI.h"
//클라 헤더
#include "Kismet/GameplayStatics.h"
#include "Client/MyCharacter/Widget/Inventory/Inventory.h"
#include "Client/MyCharacter/Widget/Party/Party.h"
#include "Client/MyCharacter/Widget/CharacterInteraction/ClickCharacterInteraction.h"
#include "Client/MyCharacter/Widget/MyCharacterWidget.h"
//서버 헤더

// Sets default values for this component's properties
UMyCharacterUI::UMyCharacterUI()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	InventoryComponent = CreateDefaultSubobject<UInventory>(TEXT("Inventory"));
	PartyComponent = CreateDefaultSubobject<UParty>(TEXT("Party"));
	ClickCharacterIntreaciton = CreateDefaultSubobject<UClickCharacterInteraction>(TEXT("ClickCharacterIntreaciton"));
}


// Called when the game starts
void UMyCharacterUI::BeginPlay()
{
	Super::BeginPlay();

	FStringClassReference MyCharacterInfoWidgetClass(TEXT("WidgetBlueprint'/Game/Blueprints/Widget/W_MyCharacter.W_MyCharacter_C'"));

	if (UClass* MyWidgetClass = MyCharacterInfoWidgetClass.TryLoadClass<UUserWidget>())
	{
		MyCharacterWidget = Cast<UMyCharacterWidget>(CreateWidget<UUserWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), MyWidgetClass));

		MyCharacterWidget->AddToViewport(); //화면에 붙인다.
		MyCharacterWidget->SetRenderTranslation(FVector2D(340.0f, 740.0f));
		MyCharacterWidget->SetVisibility(ESlateVisibility::Hidden); //숨긴다.
	}
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
		MyCharacterWidgetVisible();
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

UClickCharacterInteraction * UMyCharacterUI::GetClickCharacterInteractionComponent()
{
	return ClickCharacterIntreaciton;
}

void UMyCharacterUI::MyCharacterWidgetVisible()
{
	if (MyCharacterWidget)
	{
		MyCharacterWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void UMyCharacterUI::MyCharacterWidgetHidden()
{
	if (MyCharacterWidget)
	{
		MyCharacterWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}
