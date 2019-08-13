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
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State, Meta = (AllowPrivateAccess = true))
		EBruteState CurrentState;
	UPROPERTY(VisibleAnywhere, BlueprintType, Category = State, Meta = (AllowPrivateAccess = true))
		EBruteAttackState CurrentAttackState;

};
