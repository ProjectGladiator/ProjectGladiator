// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyNonPlayerCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API UMyNonPlayerCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
private:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
	
	
};
