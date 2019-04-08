// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

#define NICKNAMESIZE 20
#define CHARACTERCODE 30

UCLASS()
class PROJECTJ_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	AMyCharacter(); //생성자
private:
	char nick[NICKNAMESIZE];
	char CharacterCode[CHARACTERCODE];

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		int32 Level; //현재 레벨
	UPROPERTY()
		int32 Money;
	UPROPERTY()
		class AMainMapOtherPlayerController* OtherCharacterController;
	UPROPERTY()
		class AMyCharacter* ClickCharacter;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		class UWidgetComponent* CharacterNickWidget;
	UPROPERTY()
		bool IsClick;
	UPROPERTY()
		float LookUpCurrentValue;
	UPROPERTY()
		float TurnCurrentValue;

	UPROPERTY()
		FVector GoalDirection;
	UPROPERTY()
		FVector GoalLocation;
	UPROPERTY()
		FRotator GoalRotator;
	UPROPERTY()
		FTimerHandle C2S_MoveUpdateTimer;
	UPROPERTY()
		FTimerHandle S2C_MoveTimer;
	UPROPERTY()
		FTimerHandle C2S_RotateUpdateTimer;
	UPROPERTY()
		bool IsPartyLeader;
protected:
	class ClientState* ClientCharacterState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat)
		float MaxHP; //최대 HP값
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat)
		float CurrentHP; //현재 HP값
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat)
		float MaxMP;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat)
		float CurrentMP;

	UPROPERTY()
		bool IsRightClick; //마우스 오른쪽 버튼 눌럿는지 안눌럿는지

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason)override;
	virtual void ClickedReactionMontagePlay();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attack)
		bool IsAttack; //공격중인지 아닌지
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attack)
		bool IsCombo;  //콤보공격중인지 아닌지
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attack)
		int32 CurrentCombo; //현재 콤보의 단계
	UPROPERTY()
		class UMyCharacterUI* MyCharacterUI;
	UPROPERTY()
		class UMyAnimInstance* MyAnimInstance;
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UCameraComponent* Camera;
	UPROPERTY()
		class AMainMapPlayerController* MainMapPlayerController;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		void MoveForward(float Value);
	UFUNCTION()
		void MoveRight(float Value);

	bool MoveTimerActive();
	void MoveImplementation();
	void MoveUpdateTimerKill();

	UFUNCTION()
		void LookUp(float Value);

	UFUNCTION()
		void Turn(float Value);

	bool RotateTimerActive();
	void RotateImplementation();
	void RotateUpdateTimerKill();

	UFUNCTION()
		void ViewExpand();

	UFUNCTION()
		void ViewReduce();

	UFUNCTION()
		void MouseToggle();

	UFUNCTION()
		void JumpStart();

	float GetCurrentHP();
	float GetMaxHP();

	float GetCurrentMP();
	float GetMaxMP();

	UFUNCTION()
		virtual void LeftClick();

	UFUNCTION()
		virtual void RightClickOn();

	UFUNCTION()
		virtual void RightClickOff();

	UFUNCTION()
		virtual void OnAttackHit();
	UFUNCTION()
		virtual void OnComboMontageSave();
	UFUNCTION()
		void OnAttackMontageEnded();

	bool GetIsRightClick();

	UMyAnimInstance* GetMyAnimInstance();

	bool GetIsClick();
	void SetIsClick(bool _IsClick);

	char* GetCharacterCode();

	void SetCharacterCode(char* _NewCharacterCode, char* _NewNickName);

	void C2S_MoveConfirm();
	
	void S2C_MoveUpdate();

	UFUNCTION()
		void S2C_ControlOtherCharacterMove(FVector& _GoalLocation);

	void C2S_RotateConfirm();

	UFUNCTION()
		void S2C_ControlOtherCharacterRotate(FRotator& _GoalRotator);

	void SetOtherCharacterController(class AMainMapOtherPlayerController* _OtherCharacterController);

	void InventoryToggle();
	void PartyToggle();
	void MenuToggle();

	void SetClientCharacterState(ClientState* _NewClientCharacterState);

	void SetDefaultMyCharacter();
	void SetDefaultOtherCharacter();

	char* GetCharacterNickName();

	AMainMapOtherPlayerController* GetOtherPlayerController();

	UMyCharacterUI* GetMyCharacterUI();

	void SetClickCharacter(AMyCharacter* _ClickCharacter);
	AMyCharacter* GetClickCharacter();

	bool GetPartyLeader();
	void SetPartyLeader(bool _IsPartyLeader);

	void ChattingInputStart();

	int32 GetMoney();
	void GetMoney(int32 _GetMoney);
	void LoseMoney(int32 _LoseMoney);
	bool IsBuyItem(int32 _LoseMoney);
};
