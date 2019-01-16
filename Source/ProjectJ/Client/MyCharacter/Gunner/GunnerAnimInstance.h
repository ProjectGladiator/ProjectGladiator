// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Client/MyCharacter/MyAnimInstance.h"
#include "GunnerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API UGunnerAnimInstance : public UMyAnimInstance
{
	GENERATED_BODY()
public:
	UGunnerAnimInstance();

	virtual void PlayClickedReactionMontage() override;
	virtual void PlayLevelStartMontage() override;	
};
