// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TimerManager.h"

class ClientState
{
public:
	virtual void Click(class AMainMapPlayerController* _MainMapPlayerController) = 0;
	virtual void Tick(float _DeltaTime) = 0;
	virtual void MoveForward(float Value) = 0;
	virtual void MoveRight(float Value) = 0;
	virtual ~ClientState() {};
};