// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Client/Monster/Struct/MonsterAttackInfo.h"
#include "Monster.generated.h"

UCLASS()
class PROJECTJ_API AMonster : public ACharacter
{
	GENERATED_BODY()
public:
	AMonster();
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat)
		float MaxHP;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat)
		float CurrentHP;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category = AI)
		class UAIManager* AIManager;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Target)
		class AMyCharacter* Target;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AI)
		float DeathInVisibleValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attack)
		float TargetLimitDistance;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attack)
		FMonsterAttackInfo AttackInfo;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Effect)
		class UParticleSystem* HitEffectTarget;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY()
		bool DeathFlag;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ComboAttack)
		bool IsAttack; //공격중인지 아닌지
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ComboAttack)
		bool IsCombo;  //콤보공격중인지 아닌지
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ComboAttack)
		int32 CurrentCombo; //현재 콤보의 단계

	UFUNCTION()
		virtual void AttackHit();
	UFUNCTION()
		virtual void OnMonsterAttackEnded();
	UFUNCTION()
		virtual void OnComboSave();
	UFUNCTION()
		virtual void OnMonsterAttackChanged();
	UFUNCTION()
		virtual void Death();
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		float GetHP();
};
