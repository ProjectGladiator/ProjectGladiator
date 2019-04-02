﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "MainWidget.h"
//클라 헤더
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Client/Menu/MenuWidget.h"
#include "Client/MyCharacter/Widget/Inventory/Widget/InventoryWidget.h"
#include "Client/MyCharacter/Widget/Party/Widget/PartyWidget.h"
#include "Client/MyCharacter/Widget/Party/Widget/PartySlotWiget.h"
#include "Client/MyCharacter/Widget/Party/Widget/PartyAcceptRejectWidget.h"
#include "Client/Menu/MenuWidget.h"
#include "Client/MainMap/MainMapGameMode.h"
#include "Client/MainMap/MainMapPlayerController.h"
#include "Client/MyCharacter/PC/MyCharacter.h"
#include "Client/MyCharacter/Widget/MyCharacterUI.h"
#include "Public/Animation/WidgetAnimation.h"

//서버 헤더
#include "NetWork/JobInfo.h"

void UMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InChannelText = Cast<UTextBlock>(GetWidgetFromName(TEXT("InChannelText")));

	
	MenuWidget = Cast<UMenuWidget>(GetWidgetFromName(TEXT("MenuWidget")));

	if (MenuWidget)
	{
		MenuWidget->SetVisibility(ESlateVisibility::Hidden);
		MenuWidget->OnLogOut.BindDynamic(this, &UMainWidget::LogOut);
		MenuWidget->OnCharacterSelect.BindDynamic(this, &UMainWidget::CharacterSelect);
	}

	InventoryWidget = Cast<UInventoryWidget>(GetWidgetFromName(TEXT("InventoryWidget")));

	if (InventoryWidget)
	{
		InventoryWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	PartyWidget = Cast<UPartyWidget>(GetWidgetFromName(TEXT("PartyWidget")));

	if (PartyWidget)
	{
		PartyWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	PartyAcceptRejectWidget = Cast<UPartyAcceptRejectWidget>(GetWidgetFromName(TEXT("PartyAcceptReject")));

	if (PartyAcceptRejectWidget)
	{
		PartyAcceptRejectWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	MainMapGameMode = Cast<AMainMapGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	MainMapPlayerController = Cast<AMainMapPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	UProperty* prop = GetClass()->PropertyLink;

	while (prop != nullptr)
	{
		if (prop->GetClass() == UObjectProperty::StaticClass())
		{
			UObjectProperty* objectProp = Cast<UObjectProperty>(prop);

			if (objectProp->PropertyClass == UWidgetAnimation::StaticClass())
			{
				UObject* object = objectProp->GetObjectPropertyValue_InContainer(this);

				UWidgetAnimation* widgetAnim = Cast<UWidgetAnimation>(object);

				if (widgetAnim != nullptr)
				{
					InChannelTextInVisibleAnimation = widgetAnim;
				}
			}
		}

		prop = prop->PropertyLinkNext;
	}

	if (InChannelTextInVisibleAnimation)
	{
		InChannelTextInVisibleAnimation->OnAnimationFinished.AddDynamic(this, &UMainWidget::InChannelTextHidden);
	}
}

UMenuWidget * UMainWidget::GetMenuWidget()
{
	return MenuWidget;
}

void UMainWidget::MenuWidgetToggle()
{
	if (MenuWidget)
	{
		if (MenuWidget->GetVisibility() == ESlateVisibility::Hidden)
		{
			MenuWidget->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			MenuWidget->SetVisibility(ESlateVisibility::Hidden);
			MenuWidget->ChannelChangeWidgetHidden();
		}
	}
}

void UMainWidget::LogOut()
{
	ReadyCharacterSelectLogOut("MainMapUnLoadCompleteToTitle");
}

void UMainWidget::CharacterSelect()
{
	ReadyCharacterSelectLogOut("MainMapUnLoadCompleteToCharacterSelect");
}

void UMainWidget::ReadyCharacterSelectLogOut(const FName & _BindFunctionName)
{
	SetVisibility(ESlateVisibility::Hidden);

	if (MainMapPlayerController)
	{
		auto MyPlayCharacter = Cast<AMyCharacter>(MainMapPlayerController->GetPawn());

		if (MyPlayCharacter)
		{
			MenuWidgetToggle();
			MyPlayCharacter->GetMyCharacterUI()->AllUIWidgetHidden();
			MyPlayCharacter->Destroy();
		}
	}

	MainMapGameMode->LoadingWidgetViewScreen();

	MainMapGameMode->LoginUserAllDestory();

	FLatentActionInfo MainMapUnLoadInfo;
	MainMapUnLoadInfo.CallbackTarget = this; // 콜백 타겟 지정
	MainMapUnLoadInfo.ExecutionFunction = _BindFunctionName; //작업 완료 할시 호출할 함수 이름
	MainMapUnLoadInfo.UUID = 123; //고유 식별자를 지정
	MainMapUnLoadInfo.Linkage = 0;

	UGameplayStatics::UnloadStreamLevel(this, TEXT("MainStageStartArea"), MainMapUnLoadInfo);
}

void UMainWidget::MainMapUnLoadCompleteToTitle()
{
	MainMapGameMode->LoadingWidgetHiddenScreen();

	auto CreateSelectCharacter = MainMapGameMode->GetCreateSelectCharacter();

	if (CreateSelectCharacter)
	{
		if (MainMapPlayerController)
		{
			MainMapPlayerController->Possess(CreateSelectCharacter);
			MainMapPlayerController->ToCharacterSelect();
		}
	}

	MainMapGameMode->LoginWidgetToggle();
}

void UMainWidget::MainMapUnLoadCompleteToCharacterSelect()
{
	MainMapGameMode->LoadingWidgetHiddenScreen();

	auto CreateSelectCharacter = MainMapGameMode->GetCreateSelectCharacter();

	if (CreateSelectCharacter)
	{
		if (MainMapPlayerController)
		{
			MainMapPlayerController->Possess(CreateSelectCharacter);
			MainMapPlayerController->ToCharacterSelect();
		}
	}

	MainMapGameMode->CharacterSelectWidgetToggle();
}

void UMainWidget::SetInChannelText(const FText & _ChannelInMessage)
{
	if (InChannelText)
	{
		InChannelText->SetVisibility(ESlateVisibility::Visible);
		InChannelText->SetText(_ChannelInMessage);
		PlayAnimation(InChannelTextInVisibleAnimation);
	}
}

void UMainWidget::InChannelTextHidden()
{
	if (InChannelText)
	{
		InChannelText->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UMainWidget::PartyWidgetVisible()
{
	if (PartyWidget)
	{
		PartyWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void UMainWidget::PartyWidgetHidden()
{
	if (PartyWidget)
	{
		PartyWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UMainWidget::PartyAcceptRejectWidgetVisible()
{
	if (PartyAcceptRejectWidget)
	{
		PartyAcceptRejectWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void UMainWidget::PartyAcceptRejectWidgetHidden()
{
	if (PartyAcceptRejectWidget)
	{
		PartyAcceptRejectWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

UPartyWidget * UMainWidget::GetPartyWidget()
{
	return PartyWidget;
}

UPartyAcceptRejectWidget * UMainWidget::GetPartyAcceptRejectWidget()
{
	return PartyAcceptRejectWidget;
}

void UMainWidget::PartyJoin(AMyCharacter* _PartyInCharacter, char * _CharacterCode, int32 _JobCode, char * _NickName, float _HP, float _MP, bool _Leader)
{
	if (_PartyInCharacter)
	{
		_PartyInCharacter->SetPartyLeader(_Leader);

		if (PartyWidget)
		{
			UPartySlotWiget* PartySlotWidget = PartyWidget->PartySlotCreate(); //파티 슬롯을 만든다.

			if (PartySlotWidget) //만든 파티슬롯의 정보를 업데이트 한다.
			{
				FPartySlot PartySlot;
				memset(&PartySlot, 0, sizeof(FPartySlot));
				PartySlot.PartyUser = _PartyInCharacter;
				memcpy(PartySlot.CharacterCode, _CharacterCode, strlen(_CharacterCode));
				PartySlot.JobCode = _JobCode;
				memcpy(PartySlot.NickName, _NickName, strlen(_NickName));
				PartySlot.HP = _HP;
				PartySlot.Leader = _Leader;
				int32 Index = PartySlots.Num();
				PartySlots.Add(PartySlot);

				if (_JobCode == CHARACTER_JOB::Gunner)
				{
					PartySlot.MP = _MP;
				}
				else
				{
					PartySlot.MP = 0;
				}

				PartySlotWidget->PartySlotUpdate(PartySlot, Index);
			}
			else
			{
				GLog->Log(FString::Printf(TEXT("파티 슬롯 위젯이 만들어지지 않음")));
			}
		}
	}
}

void UMainWidget::PartyKick(char * _CharacterCode)
{

}

void UMainWidget::PartyLeave()
{
	if (PartyWidget)
	{
		PartyWidget->PartyLeave();
	}
}

void UMainWidget::PartyLeave(char * _CharacterCode)
{
	if (PartyWidget)
	{
		for (int i = 0; i < PartySlots.Num(); i++)
		{
			if (strcmp(PartySlots[i].CharacterCode, _CharacterCode) == 0)
			{
				PartySlots.RemoveAt(i);
			}
		}

		PartyWidget->PartyLeave(_CharacterCode);
	}
}

void UMainWidget::PartyLeaderUpdate()
{
	if (PartyWidget)
	{
		PartyWidget->PartyLeaderUpdate();
	}
}

bool UMainWidget::IsPartyJoin()
{
	if (PartySlots.Num() <= 4)
	{
		return true; //파티 참여 가능 
	}
	else
	{
		return false; //파티 인원 초과
	}
}

int32 UMainWidget::GetPartySize()
{
	return PartySlots.Num();
}

void UMainWidget::MapLoadComplete()
{
	MainMapGameMode->SelectCharacterDestroy();
	GLog->Log(FString::Printf(TEXT("맵 로드 완료")));
	MainMapGameMode->LoadingWidgetHiddenScreen();

	MainMapPlayerController->C2S_ReqUserList();
}

