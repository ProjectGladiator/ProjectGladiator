// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class PROJECTJ_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ViewRightClick", Meta = (AllowPrivateAccess = true))
		bool RightClickFlag;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RunToggle", Meta = (AllowPrivateAccess = true))
		bool ToRunFlag;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat", Meta = (AllowPrivateAccess = true))
		float MaxHP;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat", Meta = (AllowPrivateAccess = true))
		float CurrentHP;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat", Meta = (AllowPrivateAccess = true))
		int32 Level;
public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void ClickedReactionMontagePlay();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UCameraComponent* Camera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UInventory* Inventory;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FRotator CurrentRotator;

	class AChracterCreateSelectPC* CharacterCreateSelectPC;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		void MoveForward(float Value);

	UFUNCTION()
		void MoveRight(float Value);

	UFUNCTION()
		void LookUp(float Value);

	UFUNCTION()
		void Turn(float Value);

	UFUNCTION()
		void ViewExpand();

	UFUNCTION()
		void ViewReduce();

	UFUNCTION()
		void ViewRightClickOn();

	UFUNCTION()
		void ViewRightClickOff();

	UFUNCTION()
		void SightOff();

	UFUNCTION()
		void SightOn();

	UFUNCTION()
		void ToRun();

	UFUNCTION()
		void JumpStart();

	UFUNCTION()
		void LeftClick();

	bool GetRunFlag();

};
