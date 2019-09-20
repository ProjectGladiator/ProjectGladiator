// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Client/Monster/MonsterAnimInstance.h"
#include "Client/State/MonsterState/MonsterState.h"
#include "GriffonAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API UGriffonAnimInstance : public UMonsterAnimInstance
{
	GENERATED_BODY()
public:
	UGriffonAnimInstance();
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State, Meta = (AllowPrivateAccess = true))
		EGriffonState CurrentState;

public:
	UFUNCTION()
		virtual void NativeUpdateAnimation(float DeltaSeconds) override; // 틱 함수	
	
	virtual void PlayAttackMontage(int32 MontageSequence) override;
	virtual void JumpAttackMontageSection(int32 MontageSequence, int32 NewSection) override;
};
