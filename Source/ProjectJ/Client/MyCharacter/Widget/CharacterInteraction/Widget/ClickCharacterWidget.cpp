// Fill out your copyright notice in the Description page of Project Settings.

#include "ClickCharacterWidget.h"
//클라 헤더
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Client/MyCharacter/PC/MyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Client/MyCharacter/Widget/CharacterInteraction/Widget/CharacterInteractionWidget.h"

//서버 헤더

void UClickCharacterWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ClickCharacterButton = Cast<UButton>(GetWidgetFromName(TEXT("ClickCharacterButton")));
	ClickCharacterNickNameText = Cast<UTextBlock>(GetWidgetFromName(TEXT("NickNameText")));
	ClickCharacterHPText = Cast<UTextBlock>(GetWidgetFromName(TEXT("HPText")));
	ClickCharacterMPText = Cast<UTextBlock>(GetWidgetFromName(TEXT("MPText")));
	ClickCharacterHPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPBar")));
	ClickCharacterMPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("MPBar")));

	CharacterInteractionWidget = Cast<UCharacterInteractionWidget>(GetWidgetFromName(TEXT("CharacterInteration")));

	if (CharacterInteractionWidget)
	{
		CharacterInteractionWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UClickCharacterWidget::SetClickCharacterInfo(FClickCharacterInfo & _ClickCharacterInfo)
{
	ClickCharacterSlotInfo = _ClickCharacterInfo;
}

void UClickCharacterWidget::ClickCharacterUpdate()
{
	if (ClickCharacterNickNameText)
	{
		float ClickCharacterCurrentHP;
		float ClickCharacterMaxHP;
		float HPPerCent;

		ClickCharacterNickNameText->SetText(FText::FromString(TEXT("내가 클릭된 캐릭터다")));
		ClickCharacterHPText->SetText(FText::FromString(FString::FromInt(ClickCharacterSlotInfo.ClickCharacter->GetCurrentHP())));
		
		ClickCharacterCurrentHP = ClickCharacterSlotInfo.ClickCharacter->GetCurrentHP();
		ClickCharacterMaxHP = ClickCharacterSlotInfo.ClickCharacter->GetMaxHP();

		HPPerCent = ClickCharacterCurrentHP / ClickCharacterMaxHP;

		ClickCharacterHPBar->SetPercent(HPPerCent);

	}
}

FClickCharacterInfo UClickCharacterWidget::GetClickCharacterSlotInfo()
{
	return ClickCharacterSlotInfo;
}

FReply UClickCharacterWidget::NativeOnMouseButtonDown(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		GLog->Log(FString::Printf(TEXT("마우스 왼쪽 클릭")));
	}
	else if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))
	{
		GLog->Log(FString::Printf(TEXT("마우스 오른쪽 클릭")));
	}

	if (CharacterInteractionWidget)
	{
		if (CharacterInteractionWidget->GetVisibility() == ESlateVisibility::Hidden)
		{
			CharacterInteractionWidget->SetRenderTranslation(FVector2D(150.0f, 50.0f));
			CharacterInteractionWidget->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			CharacterInteractionWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	GLog->Log(FString::Printf(TEXT("다른애 이름표에서 마우스 클릭")));

	return FReply::Handled();
}

void UClickCharacterWidget::CharacterInteractionWidgetVisible()
{
	if (CharacterInteractionWidget)
	{
		CharacterInteractionWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void UClickCharacterWidget::CharacterInteractionWidgetHidden()
{
	if (CharacterInteractionWidget)
	{
		CharacterInteractionWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}