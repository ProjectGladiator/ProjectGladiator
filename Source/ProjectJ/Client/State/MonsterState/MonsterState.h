// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MonsterState.generated.h"

UENUM(BlueprintType)
enum class EBearState : uint8
{
	Idle,
	Chase,
	Attack,
	Death
};
