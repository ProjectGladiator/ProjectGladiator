// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "WarriorAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API UWarriorAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Velocity")
		float Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Velocity")
		float Direction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RunToggle")
		bool ToRunFlag;
	UFUNCTION(BlueprintCallable)
		virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
	
	
};
