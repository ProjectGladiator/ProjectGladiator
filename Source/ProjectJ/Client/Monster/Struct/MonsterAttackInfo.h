// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MonsterAttackInfo.generated.h"

USTRUCT(BlueprintType)
struct PROJECTJ_API FMonsterAttackInfo
{
	GENERATED_USTRUCT_BODY()
public:
	float AttackStartLocation;
	float AttackEndLocation;
	float AttackWidth;

	void SetAttackInfo(float _AttackStartLocation, float _AttackEndLocation, float _AttackWidth );
};