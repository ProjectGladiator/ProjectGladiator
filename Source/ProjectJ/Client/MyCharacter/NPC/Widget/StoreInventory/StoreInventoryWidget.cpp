// Fill out your copyright notice in the Description page of Project Settings.

#include "StoreInventoryWidget.h"
//클라 헤더
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "Kismet/GameplayStatics.h"
#include "StoreInventorySlotWidget.h"

//서버 헤더
void UStoreInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	StoreNameText = Cast<UTextBlock>(GetWidgetFromName(TEXT("StoreNameText")));

	if (StoreNameText)
	{
		StoreNameText->SetText(FText::FromString(TEXT("물약 상점")));
	}

	StoreCloseButton = Cast<UButton>(GetWidgetFromName(TEXT("StoreCloseButton")));

	if (StoreCloseButton)
	{
		StoreCloseButton->OnClicked.AddDynamic(this, &UStoreInventoryWidget::CloseStoreInventory);
	}
	StoreInventoryScrollBox = Cast<UScrollBox>(GetWidgetFromName(TEXT("StoreInventoryScrollBox")));
}

void UStoreInventoryWidget::CreateStoreInventorySlots(FItemInfo & ItemInfo)
{
	FStringClassReference StoreInventorySlotWidgetClass(TEXT("WidgetBlueprint'/Game/Blueprints/Widget/Store/W_StoreInventorySlot.W_StoreInventorySlot_C'"));
	
	if (UClass* MyStoreInventorySlotWidgetClass = StoreInventorySlotWidgetClass.TryLoadClass<UUserWidget>())
	{
		auto StoreInventorySlotWidget = Cast<UStoreInventorySlotWidget>(CreateWidget<UUserWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), MyStoreInventorySlotWidgetClass));

		if (StoreInventorySlotWidget)
		{
			StoreInventorySlotWidget->Init(ItemInfo);
			
			if (StoreInventoryScrollBox)
			{
				StoreInventorySlots.Add(StoreInventorySlotWidget);
				StoreInventoryScrollBox->AddChild(StoreInventorySlotWidget);
			}
		}
	}
}

void UStoreInventoryWidget::CloseStoreInventory()
{
	SetVisibility(ESlateVisibility::Hidden);
}
