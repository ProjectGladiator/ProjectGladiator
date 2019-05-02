// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Client/Monster/Monster.h"
#include "Client/State/MonsterState/MonsterState.h"
#include "Dog.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API ADog : public AMonster
{
	GENERATED_BODY()
public:
	ADog();
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Controller, Meta = (AllowPrivateAccess = true))
		class ADogAIController* DogAIController;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State, Meta = (AllowPrivateAccess = true))
		EDogState CurrentState;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State, Meta = (AllowPrivateAccess = true))
		EDogAttackState CurrentAttackState;
	UPROPERTY()
		class UDogAnimInstance* DogAnimInstance;
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;

	virtual void init() override;

	void SetAIController(class AMonsterAIController* NewAIController);

	EDogState GetCurrentState();

	EDogAttackState GetCurrentAttackState();

	UFUNCTION()
		virtual void AttackHit() override;
	UFUNCTION()
		virtual void Death() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
};
