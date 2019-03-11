// Fill out your copyright notice in the Description page of Project Settings.

#include "ChannelChange.h"
//클라 헤더
#include "Components/UniformGridPanel.h"
#include "ChannelChangeSlot.h"
#include "Client/MainMap/MainMapGameMode.h"

//서버 헤더

void UChannelChange::NativeConstruct()
{
	ChannelChangeGrid = Cast<UUniformGridPanel>(GetWidgetFromName(TEXT("ChannelChangeGrid")));
}



void UChannelChange::CreateChannelChange()
{
	for (int i = 0; i < 5; i++)
	{
		FStringClassReference ChannelSlotWidgetClass(TEXT("WidgetBlueprint'/Game/Blueprints/Widget/Menu/ChannelChange/W_ChannelChangeSlot.W_ChannelChangeSlot_C'"));

		if (UClass* MyChannelSlotWidgetClass = ChannelSlotWidgetClass.TryLoadClass<UUserWidget>())
		{
			UChannelChangeSlot* ChannelChangeSlot = Cast<UChannelChangeSlot>(CreateWidget<UUserWidget>(GetOwningPlayer(), MyChannelSlotWidgetClass));

			if (ChannelChangeSlot)
			{
				
			}
		}
	}
}
