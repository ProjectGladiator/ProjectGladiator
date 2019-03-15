// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MonsterState.generated.h"

UENUM(BlueprintType)
enum class EWormState : uint8
{
	Idle,
	Chase,
	Attack,
	Death
};

UENUM(BlueprintType)
enum class EBearState : uint8
{
	Idle,
	Chase,
	Attack,
	Death
};

UENUM(BlueprintType)
enum class EDogState : uint8
{
	Idle,
	Chase,
	Attack,
	Death
};

UENUM(BlueprintType)
enum class ESpiderState : uint8
{
	Idle,
	Chase,
	Attack,
	Death
};

UENUM(BlueprintType)
enum class ESpiderAttackState : uint8
{
	Idle,
	DefaultAttack,
	ChargeAttack
};

UENUM(BlueprintType)
enum class EDinosaurState : uint8
{
	Idle,
	Chase,
	Attack,
	Death
};

UENUM(BlueprintType)
enum class EDinosaurAttackState : uint8
{
	Idle,
	DefaultAttack,
	RangeAttack
};

UENUM(BlueprintType)
enum class ESpiderBossState : uint8
{
	Start,
	Idle,
	Chase,
	Attack,
	Summon,
	Death
};