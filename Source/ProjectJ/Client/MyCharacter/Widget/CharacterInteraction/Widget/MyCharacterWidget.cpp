﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacterWidget.h"
//클라 헤더
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Client/MyCharacter/PC/MyCharacter.h"
#include "kismet/GameplayStatics.h"
#include "Client/MyCharacter/Widget/CharacterInteraction/Widget/CharacterInteractionWidget.h"
#include "Client/MainMap/MainMapOtherPlayerController.h"


//서버 헤더

void UMyCharacterWidget::NativeConstruct()
{
	Super::NativeConstruct();

	MyCharacterButton = Cast<UButton>(GetWidgetFromName(TEXT("MyCharacterButton")));
	MyCharacterHPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("MyCharacterHPBar")));
	MyCharacterMPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("MyCharacterMPBar")));
	MyCharacterHPText = Cast<UTextBlock>(GetWidgetFromName(TEXT("MyCharacterHPText")));
	MyCharacterMPText = Cast<UTextBlock>(GetWidgetFromName(TEXT("MyCharacterMPText")));
	MyCharacterNickName = Cast<UTextBlock>(GetWidgetFromName(TEXT("MyCharacterNickName")));

	CharacterInteraction = Cast<UCharacterInteractionWidget>(GetWidgetFromName(TEXT("CharacterInterationWidget")));

	if (CharacterInteraction)
	{
		CharacterInteraction->SetVisibility(ESlateVisibility::Hidden);
	}
}

FReply UMyCharacterWidget::NativeOnMouseButtonDown(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	
	if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))
	{
		auto OtherCharacterController = Cast<AMainMapOtherPlayerController>(ClickCharacterSlotInfo.ClickCharacterPlayerController);

		if (OtherCharacterController)
		{
			if (CharacterInteraction)
			{
				if (CharacterInteraction->GetVisibility() == ESlateVisibility::Hidden)
				{
					CharacterInteraction->SetVisibility(ESlateVisibility::Visible);
				}
				else
				{
					CharacterInteraction->SetVisibility(ESlateVisibility::Hidden);
				}
			}
			else
			{
				GLog->Log(FString::Printf(TEXT("UMyCharacterWidget 캐릭터 상호작용 위젯이 없음")));
			}
			GLog->Log(FString::Printf(TEXT("마우스 오른쪽 클릭")));
		}
	}
	return FReply::Handled();
}

void UMyCharacterWidget::SetInit(AMyCharacter* _MyCharacter, APlayerController* _PlayerController)
{
	GLog->Log(FString::Printf(TEXT("내 캐릭터 위젯 초기화")));	 
	if (_MyCharacter)
	{
		ClickCharacterSlotInfo.ClickCharacter = _MyCharacter;
		ClickCharacterSlotInfo.ClickCharacterPlayerController = _PlayerController;

		if (MyCharacterNickName)
		{
			char* NickName = ClickCharacterSlotInfo.ClickCharacter->GetCharacterNickName();

			MyCharacterNickName->SetText(FText::FromString(ANSI_TO_TCHAR(NickName)));
			HPUpdate();
			MPUpdate();
		}
	}
}

void UMyCharacterWidget::HPUpdate()
{
	float CurrentHP = ClickCharacterSlotInfo.ClickCharacter->GetCurrentHP();
	float MaxHP = ClickCharacterSlotInfo.ClickCharacter->GetMaxHP();

	if (MyCharacterHPText)
	{
		MyCharacterHPText->SetText(FText::FromString(FString::FromInt((int32)(CurrentHP))));

		if (MyCharacterHPBar)
		{
			float HPPercent = CurrentHP / MaxHP;

			MyCharacterHPBar->SetPercent(HPPercent);
		}
	}

}

void UMyCharacterWidget::MPUpdate()
{

}

FClickCharacterInfo UMyCharacterWidget::GetClickCharacterSlotInfo()
{
	return ClickCharacterSlotInfo;
}

void UMyCharacterWidget::CharacterInteractionWidgetVisible()
{
	if (CharacterInteraction)
	{
		CharacterInteraction->SetVisibility(ESlateVisibility::Visible);
	}
}

void UMyCharacterWidget::CharacterInteractionWidgetHidden()
{
	if (CharacterInteraction)
	{
		CharacterInteraction->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UMyCharacterWidget::SetPosition(FVector2D _Position)
{
	SetRenderTranslation(_Position);
}

