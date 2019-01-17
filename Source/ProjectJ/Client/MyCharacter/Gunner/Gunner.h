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
private:
	UPROPERTY()
		class UGunnerAnimInstance* GunnerAnimInstance;
public:
	AGunner();
	
	virtual void BeginPlay() override;
	virtual void ClickedReactionMontagePlay() override;	

	UFUNCTION()
		virtual void LeftClick() override;
	UFUNCTION()
		virtual void OnComboMontageSave() override;
};
