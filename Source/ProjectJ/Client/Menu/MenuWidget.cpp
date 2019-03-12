// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuWidget.h"
//클라 헤더
#include "Components/Button.h"
#include "Client/Menu/ChannelChange/Widget/ChannelChange.h"
//서버 헤더

void UMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ChannelChangeWidget = Cast<UChannelChange>(GetWidgetFromName(TEXT("ChannelChangeWidget")));
	ChannelChangeButton = Cast<UButton>(GetWidgetFromName(TEXT("ChannelChangeButton")));
	CharacterSelectButton = Cast<UButton>(GetWidgetFromName(TEXT("CharacterSelectButton")));
	LogOutButton = Cast<UButton>(GetWidgetFromName(TEXT("LogOutButton")));
	GameExitButton = Cast<UButton>(GetWidgetFromName(TEXT("GameExitButton")));

	if (ChannelChangeButton)
	{
		ChannelChangeButton->OnClicked.AddDynamic(this, &UMenuWidget::ChannelChange);
	}

	if (CharacterSelectButton)
	{
		CharacterSelectButton->OnClicked.AddDynamic(this, &UMenuWidget::CharacterSelect);
	}

	if (LogOutButton)
	{
		LogOutButton->OnClicked.AddDynamic(this, &UMenuWidget::LogOut);
	}

	if (GameExitButton)
	{
		GameExitButton->OnClicked.AddDynamic(this, &UMenuWidget::GameExit);
	}

	if (ChannelChangeWidget)
	{
		ChannelChangeWidget->CreateChannelChange();
		ChannelChangeWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UMenuWidget::ChannelChange()
{
	ChannelChangeWidgetVisible();
}

void UMenuWidget::CharacterSelect()
{
}

void UMenuWidget::LogOut()
{

}

void UMenuWidget::GameExit()
{

}

void UMenuWidget::ChannelChangeWidgetVisible()
{
	if (ChannelChangeWidget)
	{
		ChannelChangeWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void UMenuWidget::ChannelChangeWidgetHidden()
{
	if (ChannelChangeWidget)
	{
		ChannelChangeWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

UChannelChange * UMenuWidget::GetChannelChangeWidget()
{
	return ChannelChangeWidget;
}
