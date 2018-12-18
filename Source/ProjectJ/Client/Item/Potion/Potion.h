// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Client/Item/MasterItem.h"
#include "Potion.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API APotion : public AMasterItem
{
	GENERATED_BODY()
private:

public:
	APotion();

	virtual void BeginPlay() override;
	
	
};
