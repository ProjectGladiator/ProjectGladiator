﻿// Fill out your copyright notice in the Description page of Project Settings.

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
#include "Client/MyCharacter/PC/MyCharacter.h"

//서버 헤더
#include "NetWork/JobInfo.h"

ClientInGameState::ClientInGameState(AMyCharacter* _MyCharacter)
{
	MyCharacter = _MyCharacter;
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

void ClientInGameState::MoveForward(float Value)
{
	if (MyCharacter)
	{
		ForwadBackwardCurrentValue = Value;

		if (ForwadBackwardCurrentValue == 1 || ForwadBackwardCurrentValue == -1)
		{
			if (ForwadBackwardPreviousValue == 0)
			{
				MyCharacter->MoveImplementation();
				GLog->Log(FString::Printf(TEXT("앞 뒤 움직임 시작")));
			}
		}

		if (ForwadBackwardCurrentValue == 0)
		{
			if (ForwadBackwardPreviousValue == 1 || ForwadBackwardPreviousValue == -1)
			{
				if (LeftRightCurrentValue == 0)
				{
					bool C2SMoveTimerActive = MyCharacter->MoveTimerActive();

					if (C2SMoveTimerActive)
					{
						MyCharacter->MoveUpdateTimerKill();
					}
				}
			}
		}

		if (Value != 0)
		{
			MyCharacter->AddMovementInput(MyCharacter->GetActorForwardVector(), Value);
		}

		ForwadBackwardPreviousValue = ForwadBackwardCurrentValue;
	}
}

void ClientInGameState::MoveRight(float Value)
{
	if (MyCharacter)
	{
		LeftRightCurrentValue = Value;

		if (LeftRightCurrentValue == 1 || LeftRightCurrentValue == -1)
		{
			if (LeftRightPreviousValue == 0)
			{
				MyCharacter->MoveImplementation();
				GLog->Log(FString::Printf(TEXT("좌 우 움직임 시작")));
			}
		}

		if (LeftRightCurrentValue == 0)
		{
			if (LeftRightPreviousValue == 1 || LeftRightPreviousValue == -1)
			{
				if (ForwadBackwardCurrentValue == 0)
				{
					//GLog->Log(FString::Printf(TEXT("좌 우 움직임 멈춤")));

					bool C2SMoveTimerActive = MyCharacter->MoveTimerActive();

					if (C2SMoveTimerActive)
					{
						MyCharacter->MoveUpdateTimerKill();
					}
				}
				else
				{
					//GLog->Log(FString::Printf(TEXT("앞뒤로 움직이는 중임")));
				}
			}
		}

		if (Value != 0)
		{
			MyCharacter->AddMovementInput(MyCharacter->GetActorRightVector(), Value);
		}

		LeftRightPreviousValue = LeftRightCurrentValue;
	}
}