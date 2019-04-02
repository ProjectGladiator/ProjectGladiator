﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "InDunGeonMessageWidget.h"
//클라 헤더
#include "Components/Button.h"
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

}

void UInDunGeonMessageWidget::InDunGeonCancel()
{
	SetVisibility(ESlateVisibility::Hidden);
}