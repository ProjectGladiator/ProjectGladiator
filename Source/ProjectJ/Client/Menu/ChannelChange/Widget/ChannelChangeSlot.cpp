// Fill out your copyright notice in the Description page of Project Settings.

#include "ChannelChangeSlot.h"
//클라 헤더
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

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