// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EArcherState : uint8
{
	Idle = 0 UMETA(DisplayName = "Idle"),
	Patrol = 1 UMETA(DisplayName = "Patrol"),
	Chase = 2 UMETA(DisplayName = "Chase"),
	Battle = 3 UMETA(DisplayName = "Battle"),
	Beaten = 4 UMETA(DisplayName = "Beaten"),
	Dead = 5 UMETA(DisplayName = "Dead")
};

UENUM(BlueprintType)
enum class EArcherAnimState : uint8
{
	Wait = 0 UMETA(DisplayName = "Wait"),
	Walk = 1 UMETA(DisplayName = "Walk"),
	Run = 2 UMETA(DisplayName = "Run"),
	Beaten = 3 UMETA(DisplayName = "Beaten"),
	Attack = 4 UMETA(DisplayName = "Attack"),
	Death = 5 UMETA(DisplayName = "Death")
};

