// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Client/Monster/Monster.h"
#include "Client/State/MonsterState/MonsterState.h"
#include "Dinosaur.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API ADinosaur : public AMonster
{
	GENERATED_BODY()
public:
	ADinosaur();
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Controller, Meta = (AllowPrivateAccess = true))
		class ADinosaurAIController* DinosaurAIController;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State, Meta = (AllowPrivateAccess = true))
		EDinosaurState CurrentState;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State, Meta = (AllowPrivateAccess = true))
		EDinosaurAttackState CurrentAttackState;
	UPROPERTY()
		class UDinosaurAnimInstance* DinosaurAnimInstance;
	UPROPERTY()
		float MaxHP;
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;
	virtual void Init(MONSTER_CODE _MyMonsterCode, int _MyMonsterNum) override;
	void SetAIController(class AMonsterAIController* NewAIController);

	EDinosaurState GetCurrentState();
	EDinosaurAttackState GetCurrentAttackState();

	UFUNCTION()
		virtual void AttackHit() override;
	UFUNCTION()
		virtual void Death() override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
};
