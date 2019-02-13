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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		float MaxHP; //최대 HP값
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		float CurrentHP; //현재 HP값
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		int32 Level; //현재 레벨
	UPROPERTY()
		bool IsClick;
public:
	// Sets default values for this character's properties
	AMyCharacter(); //생성자
protected:
	UPROPERTY()
		bool RightClickFlag; //마우스 오른쪽 버튼 눌럿는지 안눌럿는지

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void ClickedReactionMontagePlay();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attack)
		bool IsAttack; //공격중인지 아닌지
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attack)
		bool IsCombo;  //콤보공격중인지 아닌지
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attack)
		int32 CurrentCombo; //현재 콤보의 단계
	UPROPERTY()
		class UMyAnimInstance* MyAnimInstance;
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UCameraComponent* Camera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UInventory* Inventory;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FRotator CurrentRotator;

	class AMainMapPlayerController* MainMapPlayerController = nullptr;

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
		void SightOff();

	UFUNCTION()
		void SightOn();

	UFUNCTION()
		void JumpStart();

	UFUNCTION()
		virtual void LeftClick();

	UFUNCTION()
		virtual void RightClickOn();

	UFUNCTION()
		virtual void RightClickOff();

	void CharacterSelect();

	UFUNCTION()
		virtual void OnAttackHit();
	UFUNCTION()
		virtual void OnComboMontageSave();
	UFUNCTION()
		void OnAttackMontageEnded();

	bool GetRightClickFlag();

	UMyAnimInstance* GetMyAnimInstance();

	bool GetIsClick();
	void SetIsClick(bool _IsClick);
};
