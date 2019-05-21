// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Client/MyCharacter/PC/MyAnimInstance.h"
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
private:
	UFUNCTION()
		void AnimNotify_SaveAttack(UAnimNotify* Notify);
	UFUNCTION()
		void AnimNotify_ResetCombo(UAnimNotify* Notify);
	UFUNCTION()
		void AnimNotify_AttackHit(UAnimNotify* Notify);
	UFUNCTION()
		void AnimNotify_AttackEnded(UAnimNotify* Notify);
public:
	virtual void PlayClickedReactionMontage() override;
	virtual void PlayLevelStartMontage() override;
	virtual void PlayAttackMontage(float _RateScale) override;
	virtual void JumpAttackMontageSection(int32 NewSection) override;
};
