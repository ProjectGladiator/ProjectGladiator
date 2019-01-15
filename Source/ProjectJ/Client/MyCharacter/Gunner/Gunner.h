// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Client/MyCharacter/MyCharacter.h"
#include "Gunner.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API AGunner : public AMyCharacter
{
	GENERATED_BODY()
public:
	AGunner();
	
	virtual void BeginPlay() override;
	virtual void ClickedReactionMontagePlay() override;	
};
