// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SInventorySlot.generated.h"

USTRUCT(BlueprintType)
struct PROJECTJ_API FSInventorySlot
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
		class AMasterItem* ItemClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
		int Amount;
};