// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Velocity, Meta = (AllowPrivateAccess = true))
		float Speed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Velocity, Meta = (AllowPrivateAccess = true))
		float Direction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = IsRun, Meta = (AllowPrivateAccess = true))
		bool IsAccelerating;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = IsJump, Meta = (AllowPrivateAccess = true))
		bool IsJump;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Montage)
		class UAnimMontage* ClickedReaction;
public:
	UMyAnimInstance();

	UFUNCTION()
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	virtual void PlayClickedReactionMontage();
};
