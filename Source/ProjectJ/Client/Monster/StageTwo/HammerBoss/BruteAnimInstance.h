// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Client/Monster/MonsterAnimInstance.h"
#include "Client/State/MonsterState/MonsterState.h"
#include "BruteAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API UBruteAnimInstance : public UMonsterAnimInstance
{
	GENERATED_BODY()
public:
	UBruteAnimInstance();
	UFUNCTION()
	virtual void NativeUpdateAnimation(float DeltaSecnds)override;
	virtual void PlayAttackMontage(int32 MontageSequence) override;
	virtual void JumpAttackMontageSection(int32 MontageSequence, int32 NewSection)override;
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State, Meta = (AllowPrivateAccess = true))
		EBruteState CurrentState;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State, Meta = (AllowPrivateAccess = true))
		EBruteAttackState CurrentAttackState;
	/*UFUNCTION()
		void AnimNotify_MonsterAttackHit(UAnimNotify* Notify);
	UFUNCTION()
		void AnimNotify_MonsterSaveAttack(UAnimNotify* Notify);
	UFUNCTION()
		void AnimNotify_MonsterAttackEnded(UAnimNotify* Notify);
	UFUNCTION()
		void AnimNotify_MonsterAttackChanged();
	UFUNCTION()
		void AnimNotify_Death(UAnimNotify* Notify);*/
	
};
