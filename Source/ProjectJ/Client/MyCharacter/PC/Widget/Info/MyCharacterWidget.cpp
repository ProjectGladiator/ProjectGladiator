// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacterWidget.h"
//클라 헤더
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Client/MyCharacter/PC/MyCharacter.h"
#include "kismet/GameplayStatics.h"
#include "Client/MyCharacter/PC/Widget/CharacterInteraction/Widget/CharacterInteractionWidget.h"
#include "Client/MainMap/MainMapOtherPlayerController.h"
#include "Client/MainMap/MainMapPlayerController.h"


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
		auto OtherCharacterController = Cast<AMainMapOtherPlayerController>(MyCharacterSlotInfo.ClickCharacterPlayerController);

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
		if (_PlayerController)
		{
			MyCharacterSlotInfo.ClickCharacter = _MyCharacter;
			MyCharacterSlotInfo.ClickCharacterPlayerController = _PlayerController;

			if (MyCharacterNickName)
			{
				char* NickName = MyCharacterSlotInfo.ClickCharacter->GetCharacterNickName();

				MyCharacterNickName->SetText(FText::FromString(ANSI_TO_TCHAR(NickName)));
				HPUpdate();
				MPUpdate();
			}

			auto MyCharacterPlayerController = Cast<AMainMapPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
			 
			if (MyCharacterPlayerController)
			{
				CharacterInteraction->Init(MyCharacterPlayerController);
			}
		}
	}
}

void UMyCharacterWidget::HPUpdate()
{
	float CurrentHP = MyCharacterSlotInfo.ClickCharacter->GetCurrentHP();
	float MaxHP = MyCharacterSlotInfo.ClickCharacter->GetMaxHP();

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
	float CurrentMP = MyCharacterSlotInfo.ClickCharacter->GetCurrentMP();
	float MaxMP = MyCharacterSlotInfo.ClickCharacter->GetMaxMP();

	if (MyCharacterMPText)
	{
		MyCharacterMPText->SetText(FText::FromString(FString::FromInt((int32)(CurrentMP))));

		if (MyCharacterMPBar)
		{
			float MPPercent = CurrentMP / MaxMP;

			MyCharacterMPBar->SetPercent(MPPercent);
		}
	}
}

FClickCharacterInfo UMyCharacterWidget::GetMyCharacterSlotInfo()
{
	return MyCharacterSlotInfo;
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

