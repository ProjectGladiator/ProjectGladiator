// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Client/Item/MasterItem.h"
#include "BattleAxe.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API ABattleAxe : public AMasterItem
{
	GENERATED_BODY()
public:
	ABattleAxe();
	
	virtual void BeginPlay() override;
	
	
};
