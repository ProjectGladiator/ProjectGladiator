// Fill out your copyright notice in the Description page of Project Settings.

#include "ClientInGameState.h"
//클라 헤더
#include "Client/MyCharacter/PC/Tanker/Tanker.h"
#include "Client/MyCharacter/PC/Warrior/Warrior.h"
#include "Client/MyCharacter/PC/Gunner/Gunner.h"
#include "Client/MainMap/MainMapPlayerController.h"
#include "Client/MainMap/MainMapOtherPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Client/MyCharacter/Widget/MyCharacterUI.h"
#include "Client/MyCharacter/Widget/CharacterInteraction/ClickCharacterInteraction.h"
#include "Client/MyCharacter/Widget/CharacterInteraction/Widget/ClickCharacterWidget.h"

//서버 헤더
#include "NetWork/JobInfo.h"

ClientInGameState::ClientInGameState()
{

}

ClientInGameState::~ClientInGameState()
{
	GLog->Log(FString::Printf(TEXT("인게임 캐릭터 선택 상태 소멸자 출력")));
}

void ClientInGameState::Click(AMainMapPlayerController* _MainMapPlayerController)
{
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	FHitResult HitResult;
	ObjectTypes.Add(EObjectTypeQuery::ObjectTypeQuery3); //Pawn타입으로 결정

	auto MyCharacter = Cast<AMyCharacter>(_MainMapPlayerController->GetPawn());

	if (_MainMapPlayerController->bEnableClickEvents)
	{
		if (_MainMapPlayerController->GetHitResultUnderCursorForObjects(ObjectTypes, true, HitResult))
		{
			if (MyCharacter)
			{
				auto OtherCharacter = Cast<AMyCharacter>(HitResult.Actor);

				if (OtherCharacter)
				{
					GLog->Log(ANSI_TO_TCHAR(OtherCharacter->GetCharacterNickName()));

					auto OtherController = Cast<AMainMapOtherPlayerController>(OtherCharacter->GetController());
					MyCharacter->GetMyCharacterUI()->GetClickCharacterInteractionComponent()->ClickCharacterWidgetVisible();

					if (OtherController)
					{
						MyCharacter->GetMyCharacterUI()->GetClickCharacterInteractionComponent()->ClickCharacterSetInfo(OtherCharacter);
						MyCharacter->GetMyCharacterUI()->GetClickCharacterInteractionComponent()->GetClickCharacterWidget()->ClickCharacterUpdate();
						MyCharacter->GetMyCharacterUI()->GetClickCharacterInteractionComponent()->ClickCharacterWidgetVisible();
					}
				}
			}
		}
		else
		{
			MyCharacter->GetMyCharacterUI()->GetClickCharacterInteractionComponent()->GetClickCharacterWidget()->CharacterInteractionWidgetHidden();
			MyCharacter->GetMyCharacterUI()->GetClickCharacterInteractionComponent()->ClickCharacterWidgetHidden();
		}
	}
}

void ClientInGameState::Tick(float _DeltaTime)
{

}
