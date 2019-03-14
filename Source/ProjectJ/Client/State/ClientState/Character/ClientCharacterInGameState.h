// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Client/State/ClientState/ClientState.h"

class ClientCharacterInGameState : public ClientState
{
private:
	class AMyCharacter* MyCharacter;
	class AMainMapPlayerController* MainMapPlayerController;

	float ForwadBackwardCurrentValue;
	float ForwadBackwardPreviousValue;
	float LeftRightCurrentValue;
	float LeftRightPreviousValue;
public:
	ClientCharacterInGameState(class AMyCharacter* _MyCharacter);
	~ClientCharacterInGameState();

	virtual void Click(class AMainMapPlayerController* _MainMapPlayerController) override;
	virtual void Tick(float _DeltaTime) override;
	virtual void MoveForward(float Value) override;
	virtual void MoveRight(float Value) override;
};
