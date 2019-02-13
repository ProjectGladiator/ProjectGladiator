// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Client/MyCharacter/MyCharacter.h"
#include "Tanker.generated.h"

/**
 *
 */
UCLASS()
class PROJECTJ_API ATanker : public AMyCharacter
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon, Meta = (AllowPrivateAccess = true))
		class UCapsuleComponent* WeaponCapsule;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Effect, Meta = (AllowPrivateAccess = true))
		class UParticleSystem* HitEffectMonster;
public:
	ATanker();

	virtual void BeginPlay() override;
	virtual void ClickedReactionMontagePlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		virtual void LeftClick() override;
	UFUNCTION()
		virtual void RightClickOn() override;
	UFUNCTION()
		virtual void RightClickOff() override;
	UFUNCTION()
		virtual void OnComboMontageSave() override;
	UFUNCTION()
		virtual void OnAttackHit() override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
};
