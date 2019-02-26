// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ClientState.generated.h"

UENUM(BlueprintType)
enum class EClientState : uint8
{
	Title,
	CharacterSelectCreate,
	GameStart
};