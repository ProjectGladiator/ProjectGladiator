// Fill out your copyright notice in the Description page of Project Settings.

#include "ChattingMessageWidget.h"
//클라 헤더
#include "Components/TextBlock.h"
//서버 헤더

void UChattingMessageWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ChattingMessageText = Cast<UTextBlock>(GetWidgetFromName(TEXT("ChattingMessageText")));
}

void UChattingMessageWidget::ChattingMessageSet(const FText & _ChattingMessage)
{
	if (ChattingMessageText)
	{
		ChattingMessageText->SetText(_ChattingMessage);
	}
}
