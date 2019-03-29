// Fill out your copyright notice in the Description page of Project Settings.

#include "ChannelChangeSlot.h"
//클라 헤더
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Client/MainMap/MainMapGameMode.h"
#include "Client/MainMap/MainMapPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Client/MyCharacter/PC/MyCharacter.h"
#include "Client/MyCharacter/Widget/MyCharacterUI.h"
#include "Client/MyCharacter/Widget/MainWidget.h"

//서버 헤더

void UChannelChangeSlot::NativeConstruct()
{
	Super::NativeConstruct();

	ChannelChangeSlotButton = Cast<UButton>(GetWidgetFromName(TEXT("ChannelChangeSlotButton")));

	if (ChannelChangeSlotButton)
	{
		ChannelChangeSlotButton->OnClicked.AddDynamic(this, &UChannelChangeSlot::ChannelChange);
	}

	ChannelNameText = Cast<UTextBlock>(GetWidgetFromName(TEXT("ChannelNameText")));

	ChannelCongestionBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("ChannelCongestionBar")));
}

void UChannelChangeSlot::SetChannelInfo(AMainMapGameMode * _MainMapGameMode, AMyCharacter* _MyCharacter)
{
	ChannelInfo.MainMapGameMode = _MainMapGameMode;
	ChannelInfo.MyCharacter = _MyCharacter;
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

void UChannelChangeSlot::ChannelChange()
{
	if (ChannelInfo.MainMapGameMode)
	{
		int32 CurrentChannelNum = ChannelInfo.MainMapGameMode->GetChannelNum();
		int32 ChannelIndex = ChannelInfo.ChannelIndex;

		GLog->Log(FString::Printf(TEXT("게임모드 채널 번호 : %d"), CurrentChannelNum));
		GLog->Log(FString::Printf(TEXT("선택한 채널 번호 : %d"), ChannelIndex));

		if (CurrentChannelNum != ChannelIndex)
		{
			ChannelInfo.MainMapGameMode->LoadingWidgetViewScreen();
			ChannelInfo.MyCharacter->GetMyCharacterUI()->GetMainWidget()->MenuWidgetToggle();

			auto MainMapPlayerController = Cast<AMainMapPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

			if (MainMapPlayerController)
			{
				MainMapPlayerController->C2S_ReqChannelChange(ChannelIndex);
			}
		}
		else
		{
			ChannelInfo.MyCharacter->GetMyCharacterUI()->GetMainWidget()->MenuWidgetToggle();
			ChannelInfo.MainMapGameMode->OkWidgetToggle(FText::FromString(FString::Printf(TEXT("Same Channel\nChoose Other Channel"))));
		}
	}
}
