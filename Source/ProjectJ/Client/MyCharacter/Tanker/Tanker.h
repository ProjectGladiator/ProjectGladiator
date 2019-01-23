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
	UPROPERTY()
		class UTankerAnimInstance* TankerAnimInstance;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon, Meta = (AllowPrivateAccess = true))
		class UCapsuleComponent* WeaponCapsule;
public:
	ATanker();

	virtual void BeginPlay() override;
	virtual void ClickedReactionMontagePlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		virtual void LeftClick() override;
	UFUNCTION()
		virtual void OnComboMontageSave() override;
	UFUNCTION()
		virtual void OnAttackHit() override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
};
