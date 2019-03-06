// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FClickCharacterInfo.generated.h"

USTRUCT(BlueprintType)
struct PROJECTJ_API FClickCharacterInfo
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AMyCharacter* ClickCharacter;
};
