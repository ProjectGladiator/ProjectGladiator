// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Client/Monster/Monster.h"
#include "Client/State/MonsterState/MonsterState.h"
#include "Grount.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API AGrount : public AMonster
{
	GENERATED_BODY()

public:
	AGrount();

private:
	//OPP 설계 원칙에 따라서 Private의 메소드에 접근 가능하게 만들어 주는 Access를 제공함.(AllowPrivateAccess)
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = Controller, Meta = (AllowPrivateAccess = true))
		class AGrountAIController* GrountAIcontroller;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State, Meta = (AllowPrivateAccess = true))
	EGrountState CurrentState;
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = State, Meta = (AllowPrivateAccess = true))
	EGrountAttackState CurrentAttackState;
	UPROPERTY()
		class UGrountAnimInstance* GrountAnimInstance;
	UPROPERTY()
		float MaxHP;

protected:
	virtual void BeginPlay() override;
	
public:
	virtual void Tick(float DeltaTime) override;

	virtual void  Init(MONSTER_CODE _MyMonsterCode, int _MyMonsterNum) override;

	void SetAIController(class AMonsterAIController* NewAIController);

	EGrountState GetCurrentState();
	EGrountAttackState GetCurrentAttackState();

	UFUNCTION()
		virtual void AttackHit() override;
	UFUNCTION()
		virtual void Death() override;
};
