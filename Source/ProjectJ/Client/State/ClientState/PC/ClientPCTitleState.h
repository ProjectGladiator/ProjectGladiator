// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Client/State/ClientState/ClientState.h"

/**
 * 
 */
class ClientPCTitleState : public ClientState
{
public:
	ClientPCTitleState();
	~ClientPCTitleState();

	virtual void Tick(float _DeltaTime) override;
};
