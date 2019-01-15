// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Client/MyCharacter/MyAnimInstance.h"
#include "WarriorAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API UWarriorAnimInstance : public UMyAnimInstance
{
	GENERATED_BODY()
public:
	UWarriorAnimInstance();

	virtual void PlayClickedReactionMontage() override;
	
};
