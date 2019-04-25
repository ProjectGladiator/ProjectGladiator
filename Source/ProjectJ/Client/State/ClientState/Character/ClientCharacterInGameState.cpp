// Fill out your copyright notice in the Description page of Project Settings.

#include "ClientCharacterInGameState.h"
//클라 헤더
#include "Client/MyCharacter/PC/Tanker/Tanker.h"
#include "Client/MyCharacter/PC/Warrior/Warrior.h"
#include "Client/MyCharacter/PC/Gunner/Gunner.h"
#include "Client/MainMap/MainMapPlayerController.h"
#include "Client/MainMap/MainMapOtherPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Client/MyCharacter/PC/Widget/MyCharacterUI.h"
#include "Client/MyCharacter/PC/Widget/CharacterInteraction/ClickCharacterInteraction.h"
#include "Client/MyCharacter/PC/Widget/Info/MyCharacterWidget.h"
#include "Client/MyCharacter/PC/MyCharacter.h"
#include "Client/MyCharacter/NPC/MyNonPlayerCharacter.h"

//서버 헤더
#include "NetWork/JobInfo.h"

ClientCharacterInGameState::ClientCharacterInGameState(AMyCharacter* _MyCharacter)
{
	MyCharacter = _MyCharacter;
}

ClientCharacterInGameState::~ClientCharacterInGameState()
{
	GLog->Log(FString::Printf(TEXT("클라이언트 캐릭터 인게임 상태 소멸자 출력")));
}

void ClientCharacterInGameState::Click(AMainMapPlayerController * _MainMapPlayerController)
{
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	FHitResult HitResult;
	ObjectTypes.Add(EObjectTypeQuery::ObjectTypeQuery3); //Pawn타입으로 결정

	if (_MainMapPlayerController->bEnableClickEvents)
	{
		if (_MainMapPlayerController->GetHitResultUnderCursorForObjects(ObjectTypes, true, HitResult))
		{
			GLog->Log(HitResult.Actor->GetName());
			auto OtherCharacter = Cast<AMyCharacter>(HitResult.Actor);

			if (OtherCharacter)
			{
				auto OtherController = Cast<AMainMapOtherPlayerController>(OtherCharacter->GetController());

				if (OtherController)
				{
					if (MyCharacter->GetClickCharacter()) //이미 클릭한 캐릭터가 존재하면
					{
						ClickCharacterInfoHidden(); //클릭한 캐릭터의 정보를 숨겨주고
						ClickCharacterInfoVisible(OtherCharacter); //새로 클릭한 캐릭터의 정보를 보여준다.
					}
					else
					{
						//이미 클릭한 캐릭터가 없다면
						ClickCharacterInfoVisible(OtherCharacter); //새로 클릭한 캐릭터의 정보를 보여준다.
					}
				}
				else
				{
					GLog->Log(FString::Printf(TEXT("OtherController이 없음")));
				}
			}
			else
			{
				auto OtherNonPlayerCharacter = Cast<AMyNonPlayerCharacter>(HitResult.Actor);

				if (OtherNonPlayerCharacter)
				{
					OtherNonPlayerCharacter->StoreWidgetToggle();
				}
				//내 캐릭터가 아닌 다른 캐릭터일때 
				//ClickCharacterInfoHidden(); //상대방 UI를 숨긴다.
			}
		}
		else
		{
			ClickCharacterInfoHidden(); //상대방 UI를 숨긴다.
		}
	}
}

void ClientCharacterInGameState::Tick(float _DeltaTime)
{
	bool IsPartyLeader = false;

	if (MyCharacter)
	{
		IsPartyLeader = MyCharacter->GetPartyLeader();

		if (IsPartyLeader)
		{
			MyCharacter->MonsterInfoAssemble();
		}
	}
}

void ClientCharacterInGameState::MoveForward(float Value)
{
	if (MyCharacter)
	{
		ForwadBackwardCurrentValue = Value;

		if (ForwadBackwardCurrentValue == 1 || ForwadBackwardCurrentValue == -1)
		{
			if (ForwadBackwardPreviousValue == 0)
			{
				MyCharacter->MoveImplementation();
				//GLog->Log(FString::Printf(TEXT("앞 뒤 움직임 시작")));
			}
		}

		if (ForwadBackwardCurrentValue == 0)
		{
			if (ForwadBackwardPreviousValue == 1 || ForwadBackwardPreviousValue == -1)
			{
				if (LeftRightCurrentValue == 0)
				{
					//GLog->Log(FString::Printf(TEXT("앞 뒤 움직임 멈춤")));

					bool C2SMoveTimerActive = MyCharacter->MoveTimerActive();

					if (C2SMoveTimerActive)
					{
						MyCharacter->MoveUpdateTimerKill();
					}
				}
				else
				{
					//GLog->Log(FString::Printf(TEXT("좌 우로 움직이는 중임")));
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

void ClientCharacterInGameState::MoveRight(float Value)
{
	if (MyCharacter)
	{
		LeftRightCurrentValue = Value;

		if (LeftRightCurrentValue == 1 || LeftRightCurrentValue == -1)
		{
			if (LeftRightPreviousValue == 0)
			{
				MyCharacter->MoveImplementation();
				//GLog->Log(FString::Printf(TEXT("좌 우 움직임 시작")));
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
					//GLog->Log(FString::Printf(TEXT("앞 뒤로 움직이는 중임")));
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

void ClientCharacterInGameState::LookUp(float Value)
{
	if (MyCharacter)
	{
		LookUpCurrentValue = Value;

		if (Value != 0)
		{
			MyCharacter->RotateImplementation();

			MyCharacter->AddControllerPitchInput(Value);
		}
		else
		{
			if (TurnCurrentValue == 0)
			{
				bool C2SRotateTimerActive = MyCharacter->RotateTimerActive();

				if (C2SRotateTimerActive)
				{
					MyCharacter->RotateUpdateTimerKill();
				}
			}
		}
	}
}

void ClientCharacterInGameState::Turn(float Value)
{
	if (MyCharacter)
	{
		TurnCurrentValue = Value;

		if (Value != 0)
		{
			MyCharacter->RotateImplementation();

			MyCharacter->AddControllerYawInput(Value);
		}
		else
		{
			if (LookUpCurrentValue == 0)
			{
				bool C2SRotateTimerActive = MyCharacter->RotateTimerActive();

				if (C2SRotateTimerActive)
				{
					MyCharacter->RotateUpdateTimerKill();
				}
			}
		}
	}
}

void ClientCharacterInGameState::ClickCharacterInfoVisible(AMyCharacter* _ClickCharacter)
{
	if (_ClickCharacter)
	{
		MyCharacter->SetClickCharacter(_ClickCharacter);

		GLog->Log(ANSI_TO_TCHAR(MyCharacter->GetClickCharacter()->GetCharacterNickName()));

		MyCharacter->GetClickCharacter()->GetMyCharacterUI()->GetMyCharacterInteraction()->GetMyCharacterWidget()->SetPosition(FVector2D(1500.0f, 640.0f));
		MyCharacter->GetClickCharacter()->GetMyCharacterUI()->GetMyCharacterInteraction()->MyCharacterWidgetVisible();
	}
}

void ClientCharacterInGameState::ClickCharacterInfoHidden()
{
	if (MyCharacter->GetClickCharacter())
	{
		MyCharacter->GetClickCharacter()->GetMyCharacterUI()->GetMyCharacterInteraction()->MyCharacterWidgetHidden();
		MyCharacter->SetClickCharacter(nullptr);
	}
}
