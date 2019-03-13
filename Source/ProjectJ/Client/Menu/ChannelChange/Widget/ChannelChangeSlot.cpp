// Fill out your copyright notice in the Description page of Project Settings.

#include "ChannelChangeSlot.h"
//클라 헤더
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Client/MainMap/MainMapGameMode.h"

//서버 헤더

void UChannelChangeSlot::NativeConstruct()
{
	Super::NativeConstruct();

	ChannelChangeSlotButton = Cast<UButton>(GetWidgetFromName(TEXT("ChannelChangeSlotButton")));
	
	ChannelNameText = Cast<UTextBlock>(GetWidgetFromName(TEXT("ChannelNameText")));

	ChannelCongestionBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("ChannelCongestionBar")));
}

void UChannelChangeSlot::SetChannelInfo(AMainMapGameMode * _MainMapGameMode)
{
	ChannelInfo.MainMapGameMode = _MainMapGameMode;
}

void UChannelChangeSlot::InitChannelSlot(int32 _ChannelIndex)
{
	ChannelInfo.ChannelIndex = _ChannelIndex;
	ChannelInfo.CurrentChannelUserCount = 0;
	
	if (ChannelNameText)
	{
		ChannelNameText->SetText(FText::FromString(FString::Printf(TEXT("채널 %d"), _ChannelIndex)));

		if (ChannelInfo.MainMapGameMode)
		{
			ChannelSlotUpdate(0);
		}
	}
}

void UChannelChangeSlot::ChannelSlotUpdate(int32 _CurrentChannelUserCount)
{
	ChannelInfo.CurrentChannelUserCount = _CurrentChannelUserCount;
	float MaxChannelUserCount = ChannelInfo.MainMapGameMode->GetMaxChannelUserCount();

	float ChannelCongestion = ChannelInfo.CurrentChannelUserCount / MaxChannelUserCount;
	ChannelCongestionBar->SetPercent(ChannelCongestion);
}
