// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Client/Monster/Monster.h"
#include "Client/State/MonsterState/MonsterState.h"
#include "Spider.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API ASpider : public AMonster
{
	GENERATED_BODY()
public:
	ASpider();
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Controller, Meta = (AllowPrivateAccess = true))
		class ASpiderAIController* SpiderAIController;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State, Meta = (AllowPrivateAccess = true))
		ESpiderState CurrentState;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State, Meta = (AllowPrivateAccess = true))
		ESpiderAttackState CurrentAttackState;
	UPROPERTY()
		class USpiderAnimInstance* SpiderAnimInstance;
	UPROPERTY()
		float RandomAttackValue;
	UPROPERTY()
		float MaxHP;
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;
	virtual void Init(MONSTER_CODE _MyMonsterCode, int _MyMonsterNum) override;

	void SetAIController(class AMonsterAIController* NewAIController);

	ESpiderState GetCurrentState();
	ESpiderAttackState GetCurrentAttackState();

	UFUNCTION()
		virtual void AttackHit() override;
	UFUNCTION()
		virtual void OnComboSave() override;
	UFUNCTION()
		virtual void OnMonsterAttackEnded() override;
	UFUNCTION()
		virtual void OnMonsterAttackChanged() override;
	UFUNCTION()
		virtual void Death() override;
	void RandomAttack();
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
};
