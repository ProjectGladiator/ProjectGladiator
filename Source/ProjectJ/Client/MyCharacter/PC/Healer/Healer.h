// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Client/MyCharacter/PC/MyCharacter.h"
#include "Healer.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API AHealer : public AMyCharacter
{
	GENERATED_BODY()
public:
	AHealer();
private:
public:
	virtual void BeginPlay() override;
	
	
};
