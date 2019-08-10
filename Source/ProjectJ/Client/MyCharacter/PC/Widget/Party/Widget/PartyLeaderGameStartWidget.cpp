// Fill out your copyright notice in the Description page of Project Settings.

#include "PartyLeaderGameStartWidget.h"
//클라 헤더
#include "Components/Button.h"
#include "Client/MainMap/MainMapPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Client/MyCharacter/PC/MyCharacter.h"

//서버 헤더

void UPartyLeaderGameStartWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PartyLeaderGameStartButton = Cast<UButton>(GetWidgetFromName(TEXT("PartyLeaderGameStartButton")));

	if (PartyLeaderGameStartButton)
	{
		PartyLeaderGameStartButton->OnClicked.AddDynamic(this, &UPartyLeaderGameStartWidget::PartyLeaderGameStartButtonClick);
	}
}

void UPartyLeaderGameStartWidget::PartyLeaderGameStartButtonClick()
{
	auto MainMapPlayerController = Cast<AMainMapPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (MainMapPlayerController)
	{
		auto MyCharacter = Cast<AMyCharacter>(MainMapPlayerController->GetPawn());

		if (MyCharacter)
		{
			if (MyCharacter->GetPartyLeader())
			{

			}
		}
	}
}
