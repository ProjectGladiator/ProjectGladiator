// Fill out your copyright notice in the Description page of Project Settings.

#include "ChannelChange.h"
//클라 헤더
#include "Components/UniformGridPanel.h"
#include "Components/Button.h"
#include "ChannelChangeSlot.h"
#include "Client/MainMap/MainMapGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Components/UniformGridSlot.h"
#include "kismet/KismetMathLibrary.h"

//서버 헤더

void UChannelChange::NativeConstruct()
{
	ChannelChangeGrid = Cast<UUniformGridPanel>(GetWidgetFromName(TEXT("ChannelChangeGrid")));

	ChannelChangeBackButton = Cast<UButton>(GetWidgetFromName(TEXT("ChannelChangeBackButton")));
	RowColumnValue = 3.0f;

	if (ChannelChangeBackButton)
	{
		ChannelChangeBackButton->OnClicked.AddDynamic(this, &UChannelChange::ChannChangeWidgetHidden);
	}
}

void UChannelChange::CreateChannelChange()
{
	float Column;

	for (int32 i = 0; i < 6; i++)
	{
		FStringClassReference ChannelSlotWidgetClass(TEXT("WidgetBlueprint'/Game/Blueprints/Widget/Menu/ChannelChange/W_ChannelChangeSlot.W_ChannelChangeSlot_C'"));

		if (UClass* MyChannelSlotWidgetClass = ChannelSlotWidgetClass.TryLoadClass<UUserWidget>())
		{
			UChannelChangeSlot* ChannelChangeSlot = Cast<UChannelChangeSlot>(CreateWidget<UUserWidget>(GetOwningPlayer(), MyChannelSlotWidgetClass));

			if (ChannelChangeSlot)
			{
				auto MainMapGameMode = Cast<AMainMapGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

				if (MainMapGameMode)
				{
					ChannelChangeSlot->SetChannelInfo(MainMapGameMode);
					ChannelChangeSlot->InitChannelSlot(i);
					ChannelChangeSlots.Add(ChannelChangeSlot);

					UUniformGridSlot* ChannelChangeGridSlot = ChannelChangeGrid->AddChildToUniformGrid(ChannelChangeSlot);

					if (ChannelChangeGridSlot)
					{
						ChannelChangeGridSlot->SetRow(UKismetMathLibrary::FTrunc(i / RowColumnValue));
						UKismetMathLibrary::FMod(i, RowColumnValue, Column);
						ChannelChangeGridSlot->SetColumn(UKismetMathLibrary::FTrunc(Column));
					}
				}
			}
		}
	}
}

void UChannelChange::ChannelUpdate(int32 _ChannelNum, int32 _CurrentChannelUserCount)
{
	auto ChannelSlot = ChannelChangeSlots[_ChannelNum];

	if (ChannelSlot)
	{
		ChannelSlot->ChannelSlotUpdate(_CurrentChannelUserCount);
	}
}

void UChannelChange::ChannChangeWidgetHidden()
{
	SetVisibility(ESlateVisibility::Hidden);
}
