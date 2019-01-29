// Fill out your copyright notice in the Description page of Project Settings.

#include "MonsterAttackInfo.h"

void FMonsterAttackInfo::SetAttackInfo(float _AttackStartLocation, float _AttackEndLocation, float _AttackWidth)
{
	AttackStartLocation = _AttackStartLocation;
	AttackEndLocation = _AttackEndLocation;
	AttackWidth = _AttackWidth;
}
