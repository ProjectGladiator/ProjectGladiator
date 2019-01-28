// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Client/Monster/Monster.h"
#include "Client/State/MonsterState/MonsterState.h"
#include "Bear.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API ABear : public AMonster
{
	GENERATED_BODY()
public:
	ABear();
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Controller, Meta = (AllowPrivateAccess = true))
		class ABearAIController* BearAIController;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State, Meta = (AllowPrivateAccess = true))
		EBearState CurrentState;
	UPROPERTY()
		class UBearAnimInstance* BearAnimInstance;
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;

	void SetAIController(class AMonsterAIController* NewAIController);

	EBearState GetCurrentState();
	
	UFUNCTION()
		virtual void AttackHit() override;
	UFUNCTION()
		virtual void Death() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
};
