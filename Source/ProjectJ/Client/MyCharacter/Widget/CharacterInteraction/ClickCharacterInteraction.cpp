// Fill out your copyright notice in the Description page of Project Settings.

#include "ClickCharacterInteraction.h"
//클라 헤더
#include "Client/MyCharacter/Widget/CharacterInteraction/Widget/ClickCharacterWidget.h"
#include "Kismet/GameplayStatics.h"

//서버 헤더

// Sets default values for this component's properties
UClickCharacterInteraction::UClickCharacterInteraction()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UClickCharacterInteraction::BeginPlay()
{
	Super::BeginPlay();

	FStringClassReference ClickCharacterWidgetClass(TEXT("WidgetBlueprint'/Game/Blueprints/Widget/CharacterInteraction/W_ClickCharacter.W_ClickCharacter_C'"));

	if (UClass* MyClickCharacterWidgetClass = ClickCharacterWidgetClass.TryLoadClass<UUserWidget>())
	{
		ClickCharacterWidget = Cast<UClickCharacterWidget>(CreateWidget<UUserWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), MyClickCharacterWidgetClass));

		ClickCharacterWidget->AddToViewport(); //화면에 붙인다.
		ClickCharacterWidget->SetRenderTranslation(FVector2D(1250.0f, 740.0f));
		ClickCharacterWidget->SetVisibility(ESlateVisibility::Hidden); //숨긴다.
	}
}


// Called every frame
void UClickCharacterInteraction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UClickCharacterInteraction::ClickCharacterWidgetVisible()
{
	if (ClickCharacterWidget)
	{
		ClickCharacterWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void UClickCharacterInteraction::ClickCharacterWidgetHidden()
{
	if (ClickCharacterWidget)
	{
		ClickCharacterWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

UClickCharacterWidget * UClickCharacterInteraction::GetClickCharacterWidget()
{
	return ClickCharacterWidget;
}

void UClickCharacterInteraction::ClickCharacterSetInfo(AMyCharacter * _ClickCharacter)
{
	if (ClickCharacterWidget)
	{
		if (_ClickCharacter)
		{
			FClickCharacterInfo ClickInfo;
			ClickInfo.ClickCharacter = _ClickCharacter;
			ClickCharacterWidget->SetClickCharacterInfo(ClickInfo);
		}
	}
}
