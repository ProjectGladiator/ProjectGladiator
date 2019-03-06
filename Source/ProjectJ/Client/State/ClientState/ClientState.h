// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ClientState.generated.h"

UENUM(BlueprintType)
enum class EClientState : uint8
{
	Title,
	CharacterSelectCreate,
	GameStart
};

class ClientState
{
public:
	virtual void Click(class AMainMapPlayerController* _MainMapPlayerController) = 0;
	virtual void Tick(float _DeltaTime) = 0;
	virtual ~ClientState() {};
};