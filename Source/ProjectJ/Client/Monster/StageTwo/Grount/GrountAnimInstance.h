// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Client/Monster/MonsterAnimInstance.h"
#include "Client/State/MonsterState/MonsterState.h"
#include "GrountAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API UGrountAnimInstance : public UMonsterAnimInstance
{
	GENERATED_BODY()
public:
	UGrountAnimInstance();
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State, Meta = (AllowPrivateAccess = true))
		EGrountState CurrentState;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State, Meta = (AllowPrivateAccess = true))
		EGrountAttackState CurrentAttackState;
	UFUNCTION()
		void AnimNotify_MonsterAttackHit(UAnimNotify* Notify);
	UFUNCTION()
		void AnimNotify_Death(UAnimNotify* Notify);
public:
	UFUNCTION()
		virtual void NativeUpdateAnimation(float DeltaSeconds) override; // Æ½ ÇÔ¼ö	
};