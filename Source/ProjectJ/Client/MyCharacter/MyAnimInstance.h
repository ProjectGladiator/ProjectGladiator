// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttackEndedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnComboSaveDelegate);

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
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = Montage)
		class UAnimMontage* ClickedReactionMontage;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Montage)
		class UAnimMontage* LevelStartMontage;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Montage)
		class UAnimMontage* AttackMontage;

	FName GetAttackMontageSection(int32 NewSection);

	virtual void PlayClickedReactionMontage();
	virtual void PlayLevelStartMontage();
	virtual void PlayAttackMontage();
	virtual void JumpAttackMontageSection(int32 NewSection);
public:
	FOnAttackEndedDelegate OnAttackEnded;
	FOnComboSaveDelegate OnComboSave;

	UMyAnimInstance();

	UFUNCTION()
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
