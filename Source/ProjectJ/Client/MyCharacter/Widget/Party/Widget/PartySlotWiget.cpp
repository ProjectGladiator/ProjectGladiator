// Fill out your copyright notice in the Description page of Project Settings.

#include "PartySlotWiget.h"
//클라 헤더
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Client/MyCharacter/PC/MyCharacter.h"

//서버 헤더

void UPartySlotWiget::NativeConstruct()
{
	Super::NativeConstruct();

	PartyCharacterButton = Cast<UButton>(GetWidgetFromName(TEXT("PartyCharacterButton")));
	NickNameText = Cast<UTextBlock>(GetWidgetFromName(TEXT("CharacterNickName")));
	HPText = Cast<UTextBlock>(GetWidgetFromName(TEXT("CharacterHPText")));
	MPText = Cast<UTextBlock>(GetWidgetFromName(TEXT("CharacterMPText")));
	HPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PartyCharacterHPBar")));
	MPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PartyCharacterMPBar")));
}

void UPartySlotWiget::SetPartySlotIndex(int32 _Index)
{
	PartySlotIndex = _Index;
}

void UPartySlotWiget::SetPartySlotInfo(FPartySlot & _PartySlotInfo)
{
	PartySlotInfo = _PartySlotInfo;
}

void UPartySlotWiget::PartySlotUpdate()
{
	if (NickNameText)
	{
		
	}
	else
	{
		GLog->Log(FString::Printf(TEXT("NickNameText가 없음")));
	}
}
