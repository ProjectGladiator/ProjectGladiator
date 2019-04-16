// Fill out your copyright notice in the Description page of Project Settings.

#include "InDunGeonMessageWidget.h"
//클라 헤더
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Client/MainMap/MainMapPlayerController.h"
//서버 헤더

void UInDunGeonMessageWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InDunGeonAcceptButton = Cast<UButton>(GetWidgetFromName(TEXT("InDunGeonAcceptButton")));

	if (InDunGeonAcceptButton)
	{
		InDunGeonAcceptButton->OnClicked.AddDynamic(this, &UInDunGeonMessageWidget::InDunGeonAccept);
	}

	InDunGeonCancelButton = Cast<UButton>(GetWidgetFromName(TEXT("InDunGeonCancelButton")));

	if (InDunGeonCancelButton)
	{
		InDunGeonAcceptButton->OnClicked.AddDynamic(this, &UInDunGeonMessageWidget::InDunGeonCancel);
	}
}

void UInDunGeonMessageWidget::InDunGeonAccept()
{
	SetVisibility(ESlateVisibility::Hidden);

	auto MainMapPlayerController = Cast<AMainMapPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (MainMapPlayerController)
	{
		MainMapPlayerController->C2S_ReqInGameDungeon();
	}
}

void UInDunGeonMessageWidget::InDunGeonCancel()
{
	SetVisibility(ESlateVisibility::Hidden);
}
