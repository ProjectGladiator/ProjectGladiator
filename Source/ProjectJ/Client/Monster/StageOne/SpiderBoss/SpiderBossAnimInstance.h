// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Client/Monster/MonsterAnimInstance.h"
#include "Client/State/MonsterState/MonsterState.h"
#include "SpiderBossAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API USpiderBossAnimInstance : public UMonsterAnimInstance
{
	GENERATED_BODY()
public:
	USpiderBossAnimInstance();
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State, Meta = (AllowPrivateAccess = true))
		ESpiderBossState CurrentState;
public:
	UFUNCTION()
		virtual void NativeUpdateAnimation(float DeltaSeconds) override; // 틱 함수	
	
};
