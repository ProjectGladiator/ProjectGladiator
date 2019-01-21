// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Monster.generated.h"

UCLASS()
class PROJECTJ_API AMonster : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		float MaxHP;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		float CurrentHP;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category = AI)
		class UDistanceCheckAIManager* DistanceCheckAIManager;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AI)
		float TargetLimitDistance;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Target)
		class AMyCharacter* Target;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this character's properties
	AMonster();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		float GetHP();	
};
