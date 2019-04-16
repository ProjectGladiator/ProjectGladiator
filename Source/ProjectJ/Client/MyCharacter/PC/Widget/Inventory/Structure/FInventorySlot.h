// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Client/Item/Struct/FItemInfo.h"
#include "FInventorySlot.generated.h"

USTRUCT(BlueprintType)
struct PROJECTJ_API FInventorySlot
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY()
		FItemInfo ItemInfo;
	UPROPERTY()
		int Amount;
};
