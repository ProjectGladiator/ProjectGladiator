// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "State/MonsterState/MonsterState.h"
#include "MutantAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API UMutantAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Direction")
		float Direction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
		EMonsterState CurrentState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
		EMonsterAnimState CurrentAnimState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JumpState")
		EMonsterJumpState CurrentJumpState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackState")
		EMonsterAttackState CurrentAttackState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FRotator LookAtRotator;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JumpData")
		bool CurrentFalling;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JumpData")
		bool PreviousFalling;

	UFUNCTION(BlueprintCallable)
		virtual void NativeInitializeAnimation() override;
	UFUNCTION(BlueprintCallable)
		virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = "AI")
		void AnimNotify_JumpAttackStart(UAnimNotify* Notify);
	UFUNCTION(BlueprintCallable, Category = "AI")
		void AnimNotify_JumpAttackEnd(UAnimNotify* Notify);
};
