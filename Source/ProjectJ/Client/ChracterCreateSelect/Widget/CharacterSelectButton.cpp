// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterSelectButton.h"
//클라 헤더
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Client/ChracterCreateSelect/ChracterCreateSelectPC.h"
//서버 헤더
#include "NetWork/StorageManager.h"

void UCharacterSelectButton::NativeConstruct()
{
	Super::NativeConstruct();

	CharacterSelectButton = Cast<UButton>(GetWidgetFromName(TEXT("CharacterSelectButton")));

	CharacterNickName = Cast<UTextBlock>(GetWidgetFromName(TEXT("CharacterNickName")));

	CharacterLevel = Cast<UTextBlock>(GetWidgetFromName(TEXT("CharacterLevel")));

	ClassName = Cast<UTextBlock>(GetWidgetFromName(TEXT("ClassName")));

	if (CharacterSelectButton)
	{
		CharacterSelectButton->OnClicked.AddDynamic(this, &UCharacterSelectButton::CharacterSelect);
	}

	PC = Cast<AChracterCreateSelectPC>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

void UCharacterSelectButton::NativeTick(const FGeometry & MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	PacketData* Data;
	//bool ResultFlag;

	if (StorageManager::GetInstance()->GetFront(Data))
	{
		/*switch (Data->protocol)
		{

		}*/
	}
}

void UCharacterSelectButton::CharacterSelect()
{
	if (CharacterSelectButton)
	{
	/*	PC->CharacterSelectWidgetToggle();
		PC->CharacterCreateWidgetToggle();	*/	

		FString str = this->GetName();

		if (str.Compare("CharacterSelectButtonOne") == 0)
		{
			PC->select_index = 1;
		}
		else if (str.Compare("CharacterSelectButtonTwo") == 0)
		{
			PC->select_index = 2;
		}
		else if (str.Compare("CharacterSelectButtonThree") == 0)
		{
			PC->select_index = 3;
		}
	}
}

void UCharacterSelectButton::CharacterInfoInput(const FText & NickName, const FText & Level, const FText & JobName)
{
	if (CharacterNickName && CharacterLevel && ClassName)
	{
		CharacterNickName->SetText(NickName);
		CharacterLevel->SetText(Level);
		ClassName->SetText(JobName);
	}
}

