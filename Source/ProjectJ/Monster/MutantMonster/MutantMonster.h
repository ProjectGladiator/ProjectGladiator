// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "State/MonsterState/MonsterState.h"
#include "MutantMonster.generated.h"

UCLASS()
class PROJECTJ_API AMutantMonster : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMutantMonster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void OnSeeCharacter(APawn * Pawn);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
		EMonsterState CurrentState;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
		EMonsterAnimState CurrentAnimState;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "JumpState")
		EMonsterJumpState CurrentJumpState;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AttackState")
		EMonsterAttackState CurrentAttackState;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
		class UPawnSensingComponent* PawnSensing;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
		class UBehaviorTree* BehaviorTree;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Data")
		FRotator LookAtRotator;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		TArray<class APatrolPoint*> PatrolPoints;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
		class AActor* Target;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimMontage")
		class UAnimMontage* ReactionMontage;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Jump")
		bool CurrentFalling;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Jump")
		bool JumpEndFlag;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Jump")
		bool JumpRunCheckFlag;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Jump")
		bool RunCheckFlag;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Parrying")
		bool ParryingFlag;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Parrying")
		bool IsParrying;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat")
		float MaxHP;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat")
		float CurrentHP;
	FTimerHandle DeathTimer;
	float DeathMaterialsValue;
	UFUNCTION()
		virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	UFUNCTION()
		void Death();
};
