// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Client/State/ClientState/ClientState.h"

class ClientPCInGameState : public ClientState
{	
private:
	class AMainMapGameMode* MainMapGameMode;
public:
	ClientPCInGameState(AMainMapGameMode* _MainMapGameMode);
	~ClientPCInGameState();

	virtual void Tick(float _DeltaTime) override;
};
