// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "NetWork/NetworkManager.h"
#include "WinterGameInstance.generated.h"

using namespace NetworkClient_main;

/**
 * 
 */
UCLASS()
class PROJECTJ_API UWinterGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	virtual void Init() override;
	virtual void Shutdown() override;
	
	
	
};
