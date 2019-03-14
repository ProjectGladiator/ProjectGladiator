// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Client/State/ClientState/ClientState.h"

class ClientCharacterTitleState : public ClientState
{
public:
	ClientCharacterTitleState();
	~ClientCharacterTitleState();

	virtual void Click(class AMainMapPlayerController* _MainMapPlayerController) override;
	virtual void Tick(float _DeltaTime) override;
};
