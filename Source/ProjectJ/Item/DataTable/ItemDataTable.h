// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemDataTable.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	UnKnown = 0 UMETA(DisplayName = "UnKnown"),
	Consumable = 1 UMETA(DisplayName = "Consumable"),
	Equip = 2 UMETA(DisplayName = "Equip"),
	Material = 3 UMETA(DisplayName = "Material")
};

UENUM(BlueprintType)
enum class EEquipSlot :uint8
{
	UnKnown = 0 UMETA(DisplayName = "UnKnown"),
	LeftHand = 1 UMETA(DisplayName = "LeftHand"),
	RightHand = 2 UMETA(DisplayName = "RightHand"),
	TwoHand = 3 UMETA(DisplayName = "TwoHand")
};

UENUM(BlueprintType)
enum class EJob :uint8
{
	UnKnown = 0 UMETA(DisplayName = "UnKnown"),
	Tanker = 1 UMETA(DisplayName = "Tanker"),
	Warrior = 2 UMETA(DisplayName = "Warrior"),
	Magician = 3 UMETA(DisplayName = "Magician"),
	All = 4 UMETA(DisplayName = "All")
};

USTRUCT(BlueprintType)
struct PROJECTJ_API FItemDataTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int ItemIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText ItemName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EItemType ItemType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EEquipSlot EquipSlot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText ItemExplanation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int ItemCurrentAmount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int ItemMaxAmount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int ItemUsePoint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EJob Job;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UTexture2D* ItemThumbnail;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UStaticMesh* ItemMesh;
};
