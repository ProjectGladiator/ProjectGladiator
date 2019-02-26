// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterSelectButton.h"
//클라 헤더
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Client/MainMap/MainMapPlayerController.h"
#include "Client/MainMap/MainMapGameMode.h"

//서버 헤더
#include "NetWork/StorageManager.h"
#include "NetWork/JobInfo.h"

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

	MainMapPlayerController = Cast<AMainMapPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	MainMapGameMode = Cast<AMainMapGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
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
		FString str = this->GetName();

		if (str.Compare("CharacterSelectButtonOne") == 0)
		{
			MainMapPlayerController->SetSelectIndex(1);
		}
		else if (str.Compare("CharacterSelectButtonTwo") == 0)
		{
			MainMapPlayerController->SetSelectIndex(2);
		}
		else if (str.Compare("CharacterSelectButtonThree") == 0)
		{
			MainMapPlayerController->SetSelectIndex(3);
		}

		str = ClassName->GetText().ToString();

		if (str.Compare("Tanker") == 0)
		{
			MainMapGameMode->SelectCharacterSpawn(CHARACTER_JOB::Tanker);
		}
		else if (str.Compare("Warrior") == 0)
		{
			MainMapGameMode->SelectCharacterSpawn(CHARACTER_JOB::Warrior);
		}
		else if (str.Compare("Gunner") == 0)
		{
			MainMapGameMode->SelectCharacterSpawn(CHARACTER_JOB::Gunner);
		}
		else
		{
			GLog->Log(FString::Printf(TEXT("선택한 버튼의 클래스 이름이 존재하지 않음")));
		}

		MainMapPlayerController->ToCharacterZoomInCamera();
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

