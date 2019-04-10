// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacterUI.h"
//클라 헤더
#include "Kismet/GameplayStatics.h"
#include "Client/MyCharacter/Widget/Inventory/Inventory.h"
#include "Client/MyCharacter/Widget/Party/Party.h"
#include "Client/MyCharacter/Widget/CharacterInteraction/ClickCharacterInteraction.h"
#include "Client/MyCharacter/Widget/Inventory/Widget/InventoryWidget.h"
#include "Client/MyCharacter/Widget/Party/Widget/PartyWidget.h"
#include "Client/MyCharacter/Widget/Info/MyCharacterWidget.h"
#include "Client/Menu/MenuWidget.h"
#include "Client/MyCharacter/Widget/MainWidget.h"
#include "Client/MyCharacter/PC/MyCharacter.h"
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

	//에디터 상에 있는 블루프린트를 읽어서 TitleLoginWidgetClass에 저장한다.
	FStringClassReference MainWidgetClass(TEXT("WidgetBlueprint'/Game/Blueprints/Widget/W_MainWidget.W_MainWidget_C'"));

	//앞에서 읽어 들인 TitleLoginWidgetClass를 UserWidget클래스 형태로 읽어서 MyWidgetClass에 저장한다.
	if (UClass* MyWidgetClass = MainWidgetClass.TryLoadClass<UUserWidget>())
	{
		//MyWidgetClass를 토대로 MainWidget을 생성한다.
		MainWidget = Cast<UMainWidget>(CreateWidget<UUserWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), MyWidgetClass));

		MainWidget->AddToViewport(); //화면에 붙인다.
		MainWidget->SetVisibility(ESlateVisibility::Hidden); //보여준다.
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

void UMyCharacterUI::AllUIHidden()
{
	MainWidgetHidden();

	MyCharacterInteraction->MyCharacterWidgetHidden();

	auto MyCharacter = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (MyCharacter)
	{
		if (MyCharacter->GetClickCharacter())
		{
			MyCharacter->GetClickCharacter()->GetMyCharacterUI()->GetMyCharacterInteraction()->MyCharacterWidgetHidden();
		}
	}
}

void UMyCharacterUI::AllUIVisible()
{
	MainWidgetVisible();

	MyCharacterInteraction->MyCharacterWidgetVisible();

	auto MyCharacter = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (MyCharacter)
	{
		if (MyCharacter->GetClickCharacter())
		{
			MyCharacter->GetClickCharacter()->GetMyCharacterUI()->GetMyCharacterInteraction()->MyCharacterWidgetVisible();
		}
	}
}

void UMyCharacterUI::AllUIDestroy()
{
	if (MyCharacterInteraction->GetMyCharacterWidget())
	{
		MyCharacterInteraction->GetMyCharacterWidget()->RemoveFromParent();
	}

	if (MainWidget)
	{
		MainWidget->RemoveFromParent();
	}
}

UMainWidget* UMyCharacterUI::GetMainWidget()
{
	return MainWidget;
}

void UMyCharacterUI::MainWidgetVisible()
{
	if (MainWidget)
	{
		MainWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void UMyCharacterUI::MainWidgetHidden()
{
	if (MainWidget)
	{
		MainWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}
