// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Client/Monster/MonsterAnimInstance.h"
#include "Client/State/MonsterState/MonsterState.h"
#include "BearAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API UBearAnimInstance : public UMonsterAnimInstance
{
	GENERATED_BODY()
public:
	UBearAnimInstance();
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State, Meta = (AllowPrivateAccess = true))
		EBearState CurrentState;
	UFUNCTION()
		void AnimNotify_MonsterAttackHit(UAnimNotify* Notify);
	UFUNCTION()
		void AnimNotify_Death(UAnimNotify* Notify);
public:
	UFUNCTION()
		virtual void NativeUpdateAnimation(float DeltaSeconds) override; // 틱 함수
};
