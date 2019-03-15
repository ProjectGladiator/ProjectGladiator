// Fill out your copyright notice in the Description page of Project Settings.

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
	UFUNCTION()
		void AnimNotify_MonsterAttackHit(UAnimNotify* Notify);
	//UFUNCTION()
	//	void AnimNotify_MonsterSaveAttack(UAnimNotify* Notify);
	//UFUNCTION()
	//	void ANimNotify_MonsterAttackEnded();
	UFUNCTION()
		void AnimNotify_Death(UAnimNotify* Notify);
};
