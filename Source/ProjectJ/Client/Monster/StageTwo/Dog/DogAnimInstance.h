﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Client/Monster/MonsterAnimInstance.h"
#include "Client/State/MonsterState/MonsterState.h"
#include "DogAnimInstance.generated.h"

/**
 *
 */
UCLASS()
class PROJECTJ_API UDogAnimInstance : public UMonsterAnimInstance
{
	GENERATED_BODY()
public:
	UDogAnimInstance();
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State, Meta = (AllowPrivateAccess = true))
		EDogState CurrentState;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State, Meta = (AllowPrivateAccess = true))
	EDogAttackState CurrentAttackState;
	UFUNCTION()
		void AnimNotify_MonsterAttackHit(UAnimNotify* Notify);
	UFUNCTION()
		void AnimNotify_Death(UAnimNotify* Notify);
public:
	UFUNCTION()
		virtual void NativeUpdateAnimation(float DeltaSeconds) override; // 틱 함수	
};
