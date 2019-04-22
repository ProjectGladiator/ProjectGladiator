// Fill out your copyright notice in the Description page of Project Settings.

#include "ClickCharacterInteraction.h"
//클라 헤더
#include "Client/MyCharacter/PC/Widget/Info/MyCharacterWidget.h"
#include "Client/MyCharacter/PC/Widget/Info/MyCharacterNickNameWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/WidgetComponent.h"
#include "Client/MyCharacter/PC/Widget/Info/MyCharacterNickNameWidget.h"

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

	FStringClassReference BlueprintMyCharacterWidgetClass(TEXT("WidgetBlueprint'/Game/Blueprints/Widget/CharacterInteraction/W_MyCharacter.W_MyCharacter_C'"));

	if (UClass* MyCharacterWidgetClass = BlueprintMyCharacterWidgetClass.TryLoadClass<UUserWidget>())
	{
		MyCharacterWidget = Cast<UMyCharacterWidget>(CreateWidget<UUserWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), MyCharacterWidgetClass));

		MyCharacterWidget->AddToViewport(); //화면에 붙인다.
		MyCharacterWidget->SetRenderTranslation(FVector2D(340.0f, 640.0f));
		MyCharacterWidget->SetVisibility(ESlateVisibility::Hidden); //숨긴다.
	}
}


// Called every frame
void UClickCharacterInteraction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UClickCharacterInteraction::MyCharacterWidgetVisible()
{
	if (MyCharacterWidget)
	{
		MyCharacterWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void UClickCharacterInteraction::MyCharacterWidgetHidden()
{
	if (MyCharacterWidget)
	{
		MyCharacterWidget->SetVisibility(ESlateVisibility::Hidden);
		MyCharacterWidget->CharacterInteractionWidgetHidden();
	}
}

UMyCharacterWidget * UClickCharacterInteraction::GetMyCharacterWidget()
{
	return MyCharacterWidget;
}

UMyCharacterNickNameWidget * UClickCharacterInteraction::GetMyCharacterNickNameWidget()
{
	return MyCharacterNickNameWidget;
}

void UClickCharacterInteraction::SetMyCharacterNickNameWidget(UWidgetComponent * _MyCharacterWidgetComponent, char* _Nick)
{
	if (_MyCharacterWidgetComponent)
	{
		FStringClassReference BlueprintMyCharacterNickNameWidget(TEXT("WidgetBlueprint'/Game/Blueprints/Widget/CharacterInteraction/W_MyCharacterName.W_MyCharacterName_C'"));

		if (UClass* MyCharacterNickNameWidgetClass = BlueprintMyCharacterNickNameWidget.TryLoadClass<UUserWidget>())
		{
			_MyCharacterWidgetComponent->SetWidgetClass(MyCharacterNickNameWidgetClass);

			auto MyCharacterNickNameWidget = Cast<UMyCharacterNickNameWidget>(_MyCharacterWidgetComponent->GetUserWidgetObject());

			if (MyCharacterNickNameWidget)
			{
				MyCharacterNickNameWidget->SetCharacterNickNameToWidget(_Nick);
			}
		}
	}
}
