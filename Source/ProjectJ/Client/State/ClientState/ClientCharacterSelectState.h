// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ClientState.h"

/**
 * 
 */
class ClientCharacterSelectState : public ClientState
{
public:
	ClientCharacterSelectState();
	~ClientCharacterSelectState();

	virtual void Click(class AMainMapPlayerController* _MainMapPlayerController) override;
	virtual void Tick(float _DeltaTime) override;
};
