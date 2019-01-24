// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Client/Monster/MonsterAnimInstance.h"
#include "WormAnimInstance.generated.h"

/**
 *
 */
UCLASS()
class PROJECTJ_API UWormAnimInstance : public UMonsterAnimInstance
{
	GENERATED_BODY()
public:
	UWormAnimInstance(); //생성자
private:
	UFUNCTION()
		void AnimNotify_Death(UAnimNotify* Notify);
public:
	virtual void PlayAttackMontage() override; //공격 몽타주 실행
};
