// Fill out your copyright notice in the Description page of Project Settings.

#include "Party.h"
//클라 헤더
#include "Kismet/GameplayStatics.h"
#include "Client/MyCharacter/Widget/Party/Widget/PartyWidget.h"
#include "Client/MyCharacter/Widget/Party/Widget/PartySlotWiget.h"
//서버 헤더

// Sets default values for this component's properties
UParty::UParty()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UParty::BeginPlay()
{
	Super::BeginPlay();

	FStringClassReference PartyWidgetClass(TEXT("WidgetBlueprint'/Game/Blueprints/Widget/Party/W_Party.W_Party_C'"));

	if (UClass* MyPartyWidgetClass = PartyWidgetClass.TryLoadClass<UUserWidget>())
	{
		PartyWidget = Cast<UPartyWidget>(CreateWidget<UUserWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), MyPartyWidgetClass));

		PartyWidget->AddToViewport(); //화면에 붙인다.
		PartyWidget->SetVisibility(ESlateVisibility::Hidden); //숨긴다.
	}	
}


// Called every frame
void UParty::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UParty::PartyWidgetToggle()
{
	if (PartyWidget)
	{
		if (PartyWidget->GetVisibility() == ESlateVisibility::Hidden)
		{
			PartyWidget->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			PartyWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

UPartyWidget * UParty::GetPartyWidget()
{
	return PartyWidget;
}

void UParty::PartyJoin(AMyCharacter* _MyCharacter)
{
	if (PartyWidget)
	{
		UPartySlotWiget* PartySlotWidget = PartyWidget->PartySlotCreate(_MyCharacter);

		if (PartySlotWidget)
		{
			PartySlotWidget->PartySlotUpdate();
		}
	}
}