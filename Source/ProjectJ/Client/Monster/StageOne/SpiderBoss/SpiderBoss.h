﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Client/Monster/Monster.h"
#include "Client/State/MonsterState/MonsterState.h"
#include "SpiderBoss.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API ASpiderBoss : public AMonster
{
	GENERATED_BODY()
public:
	ASpiderBoss();
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Controller, Meta = (AllowPrivateAccess = true))
		class ASpiderBossAIController* SpiderBossAIController;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Controller, Meta = (AllowPrivateAccess = true))
		ESpiderBossState CurrentState;
	UPROPERTY()
		class USpiderBossAnimInstance* SpiderBossAnimInstance;
	UPROPERTY()
		FVector StartLocation;
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;

	void SetAIController(class AMonsterAIController* NewAIController);

	ESpiderBossState GetCurrentState();

	UFUNCTION()
		virtual void AttackHit() override;
	UFUNCTION()
		virtual void OnComboSave() override;
	UFUNCTION()
		virtual void OnMonsterAttackEnded() override;
	UFUNCTION()
		virtual void Death() override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
};