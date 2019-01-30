// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Client/Monster/Monster.h"
#include "Client/State/MonsterState/MonsterState.h"
#include "Worm.generated.h"

/**
 *
 */
UCLASS()
class PROJECTJ_API AWorm : public AMonster
{
	GENERATED_BODY()
public:
	AWorm();
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Controller, Meta = (AllowPrivateAccess = true))
		class AWormAIController* WormAIController;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State, Meta = (AllowPrivateAccess = true))
		EWormState CurrentState;
	UPROPERTY()
		class UWormAnimInstance* WormAnimInstance;
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;

	void SetAIController(class AMonsterAIController* NewAIController);
	UFUNCTION()
		virtual void Death() override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
};
