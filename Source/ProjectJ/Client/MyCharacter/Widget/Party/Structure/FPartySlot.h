// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPartySlot.generated.h"

USTRUCT(BlueprintType)
struct PROJECTJ_API FPartySlot
{
	GENERATED_USTRUCT_BODY()
public:
	char CharacterCode[30];
	int32 JobCode;
	char NickName[20];
	float HP;
	float MP;
	bool Leader;
};
