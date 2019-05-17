// Fill out your copyright notice in the Description page of Project Settings.

#include "ClientCharacterTitleState.h"
//클라 헤더
#include "Client/MyCharacter/PC/Tanker/Tanker.h"
#include "Client/MyCharacter/PC/Warrior/Warrior.h"
#include "Client/MyCharacter/PC/Gunner/Gunner.h"
#include "Client/MainMap/MainMapPlayerController.h"

//서버 헤더
#include "NetWork/JobInfo.h"

void ClientCharacterTitleState::Click(AMainMapPlayerController * _MainMapPlayerController)
{
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	FHitResult HitResult;
	ObjectTypes.Add(EObjectTypeQuery::ObjectTypeQuery3); //Pawn타입으로 결정

	if (_MainMapPlayerController->GetHitResultUnderCursorForObjects(ObjectTypes, true, HitResult))
	{
		auto Character = Cast<AWarrior>(HitResult.Actor);

		if (Character)
		{
			Character->ClickedReactionMontagePlay();
			GLog->Log(FString::Printf(TEXT("전사 클릭")));
			_MainMapPlayerController->SelectCharacter(CHARACTER_JOB::Warrior);
		}
		else
		{
			auto Character = Cast<ATanker>(HitResult.Actor);

			if (Character)
			{
				Character->ClickedReactionMontagePlay();
				GLog->Log(FString::Printf(TEXT("탱커 클릭")));
				_MainMapPlayerController->SelectCharacter(CHARACTER_JOB::Tanker);
			}
			else
			{
				auto Character = Cast<AGunner>(HitResult.Actor);

				if (Character)
				{
					Character->ClickedReactionMontagePlay();
					GLog->Log(FString::Printf(TEXT("총잡이 클릭")));
					_MainMapPlayerController->SelectCharacter(CHARACTER_JOB::Gunner);
				}
			}
		}
	}
}

void ClientCharacterTitleState::Tick(float _DeltaTime)
{
	
}

ClientCharacterTitleState::ClientCharacterTitleState()
{

}

ClientCharacterTitleState::~ClientCharacterTitleState()
{
	GLog->Log(FString::Printf(TEXT("클라이언트 캐릭터 선택 상태 소멸자 출력")));
}
