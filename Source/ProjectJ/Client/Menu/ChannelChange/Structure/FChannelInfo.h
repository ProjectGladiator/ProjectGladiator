// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FChannelInfo.generated.h"

USTRUCT(BlueprintType)
struct PROJECTJ_API FChannelInfo
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AMainMapGameMode* MainMapGameMode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AMyCharacter* MyCharacter;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 ChannelIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 CurrentChannelUserCount;
};
