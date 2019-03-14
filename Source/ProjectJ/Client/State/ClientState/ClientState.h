// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TimerManager.h"

class ClientState
{
public:
	ClientState() {};
	virtual ~ClientState() {};

	virtual void Click(class AMainMapPlayerController* _MainMapPlayerController) {};
	virtual void Tick(float _DeltaTime) = 0;
	virtual void MoveForward(float Value) {};
	virtual void MoveRight(float Value) {};
	virtual void LookUp(float Value) {};
	virtual void Turn(float Value) {};
};