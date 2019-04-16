// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FItemInfo.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	UnKnown = 0 UMETA(DisplayName ="UnKnown"),
	Consumable = 1 UMETA(DisplayName = "Consumable"),
	Equip = 2 UMETA(DisplayName = "Equip")
};

UENUM(BlueprintType)
enum class EEquipSlot : uint8
{
	UnKnown = 0 UMETA(DisplayName = "UnKnown"),
	Tanker = 1 UMETA(DisplayName = "Tanker"),
	Warrior = 2 UMETA(DisplayName = "Warrior"),
	Gunner = 3 UMETA(DisplayName = "Gunner"),
	All = 4 UMETA(DisplayName = "All")
};

USTRUCT(BlueprintType)
struct PROJECTJ_API FItemInfo
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY()
		bool IsActive;
	UPROPERTY()
		FText ItemNameText;
	UPROPERTY()
		EItemType ItemType;
	UPROPERTY()
		int32 ItemMaxCount;
	UPROPERTY()
		int32 EquipAbilityIncreasePoint;
	UPROPERTY()
		class UTexture2D* ItemThumbnail;
};