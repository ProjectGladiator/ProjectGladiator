// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "State/ArcherState/ArcherState.h"
#include "ArcherAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API UArcherAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
	//// State
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	//	EArcherState CurrentState;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	//	EArcherAnimState CurrentAnimState;
	//
	//// Data
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	//	float Direction;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	//	FRotator LookAtRotator;

	//// etc
	//UFUNCTION(BlueprintCallable)
	//	virtual void NativeInitializeAnimation() override;
	//UFUNCTION(BlueprintCallable)
	//	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	
};
