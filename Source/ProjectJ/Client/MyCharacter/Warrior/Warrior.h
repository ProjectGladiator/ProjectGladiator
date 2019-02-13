// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Client/MyCharacter/MyCharacter.h"
#include "Warrior.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API AWarrior : public AMyCharacter
{
	GENERATED_BODY()
public:
	AWarrior();	

	virtual void BeginPlay() override;
	virtual void ClickedReactionMontagePlay() override;

	UFUNCTION()
		virtual void LeftClick() override;
	UFUNCTION()
		virtual void OnComboMontageSave() override;
	UFUNCTION()
		virtual void OnAttackHit() override;
};
