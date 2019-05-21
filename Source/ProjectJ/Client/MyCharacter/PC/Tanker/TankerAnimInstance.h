// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Client/MyCharacter/PC/MyAnimInstance.h"
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
private:
	UFUNCTION()
		void AnimNotify_SaveAttack(UAnimNotify* Notify);
	UFUNCTION()
		void AnimNotify_AttackHit(UAnimNotify* Notify);
	UFUNCTION()
		void AnimNotify_AttackEnded(UAnimNotify* Notify);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Montage, Meta = (AllowPrivateAccess = true))
		class UAnimMontage* StopRightClickAbilityMontage; //캐릭터 공격애니메이션
public:
	virtual void PlayClickedReactionMontage() override;
	virtual void PlayLevelStartMontage() override;
	virtual void PlayAttackMontage(float _RateScale) override;
	virtual void PlayRightClickAbilityMontage() override;
	virtual void PlayStopRightClickAbilityMontage() override;
	virtual void JumpAttackMontageSection(int32 NewSection) override;
};
