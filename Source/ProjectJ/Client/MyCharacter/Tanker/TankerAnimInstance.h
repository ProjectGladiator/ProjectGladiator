// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Client/MyCharacter/MyAnimInstance.h"
#include "TankerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API UTankerAnimInstance : public UMyAnimInstance
{
	GENERATED_BODY()

public:
	UTankerAnimInstance();

	virtual void PlayClickedReactionMontage() override;
	
};
