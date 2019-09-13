// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MonsterState.generated.h"

UENUM(BlueprintType)
enum class EWormState : uint8
{
	Ready,
	Idle,
	Chase,
	Attack,
	Death
};

UENUM(BlueprintType)
enum class EBearState : uint8
{
	Ready,
	Idle,
	Chase,
	Attack,
	Death
};

UENUM(BlueprintType)
enum class EDogState : uint8
{
	Ready,
	Idle,
	Chase,
	Attack,
	Death
};

UENUM(BlueprintType)
enum class EDogAttackState : uint8
{
	Ready,
	Idle,
	DefaultAttack,
	ChargeAttack
};

UENUM(BlueprintType)
enum class ESpiderState : uint8
{
	Ready,
	Idle,
	Chase,
	Attack,
	Death
};

UENUM(BlueprintType)
enum class ESpiderAttackState : uint8
{
	Ready,
	Idle,
	DefaultAttack,
	ChargeAttack
};

UENUM(BlueprintType)
enum class EGrountState : uint8
{
	Ready,
	Idle,
	Chase,
	Attack,
	Death
};

UENUM(BlueprintType)
enum class EGrountAttackState : uint8
{
	Ready,
	Idle,
	Chase,
	Attack,
	Death
};

UENUM(BlueprintType)
enum class EDinosaurState : uint8
{
	Ready,
	Idle,
	Chase,
	Attack,
	Death
};

UENUM(BlueprintType)
enum class EDinosaurAttackState : uint8
{
	Ready,
	Idle,
	DefaultAttack,
	RangeAttack
};

UENUM(BlueprintType)
enum class ESpiderBossState : uint8
{
	Ready,
	Start,
	Idle,
	Chase,
	Attack,
	Death
};

UENUM(BlueprintType)
enum class ESpiderBossAttackState : uint8
{
	Ready,
	Idle,
	DefaultAttack,
	ChargeAttack,
	Summon,
};

UENUM(BlueprintType)
enum class EGriffonState : uint8
{
	Ready,
	Idle,
	Chase,
	Attack,
	Death
};

UENUM(BlueprintType)
enum class EBruteState : uint8
{
	Ready,
	Idle,
	Chase,
	Attack,
	Death
};
UENUM(BlueprintType)
enum class EBruteAttackState : uint8
{
	Ready,
	Idle,
	DefaultAttack,
	KickAttack,
	JumpLandAttack
};

UENUM()
enum class MONSTER_ATTACK_CODE
{
	DEFAULT_ATTACK_CODE = -1,
	SPIDER_FIRST_ATTACK = 10011,
	SPIDER_SECOND_ATTACK = 10021,
	WORM_FIRST_ATTACK = 10012,
	BOSS_SPIDER_FIRST_ATTACK = 10013,
	BOSS_SPIDER_SECOND_ATTACK = 10023,
	DOG_FIRST_ATTACK = 20011,
	ORCCANNONSOLDIER_FIRST_ATTACK = 20012,
	KING_OF_THEAXE_FIRST_ATTACK = 20013,
	KING_OF_THEAXE_SECOND_ATTACK = 20023,
	KING_OF_THEAXE_THIRD_ATTACK = 20033,
	BEAR_FIRST_ATTACK = 30011,
	DINOSAUR_FIRST_ATTACK = 30012
};