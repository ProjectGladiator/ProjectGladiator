//// Fill out your copyright notice in the Description page of Project Settings.
//
//#pragma once
//
//#include "CoreMinimal.h"
//#include "Client/Monster/Monster.h"
//#include "Client/State/MonsterState/MonsterState.h"
//#include "HammerKing.generated.h"
//
///**
// * 
// */
//UCLASS()
//class PROJECTJ_API AHammerKing : public AMonster
//{
//	GENERATED_BODY()
//	
//public:
//	AHammerKing();
//private:
//	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Controller, Meta = (AllowPrivateAccess = true))
//		class AHammerKingAIController* HammerKingAIController;
//	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State, Meta = (AllowPrivateAccess = true))
//		EHammerKingState CurrentState;
//	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State, Meta = (AllowPrivateAccess = true))
//		EHammerKingAttackState CurrentAttackState;
//	UPROPERTY()
//		class UHammerKingAnimInstance* HammerKingAnimInstance;
//	UPROPERTY()
//		float RandomAttackValue;
//	UPROPERTY()
//		float MaxHP;
//protected:
//	virtual void BeginPlay() override;
//public:
//	virtual void Tick(float DeltaTime) override;
//	virtual void Init(MONSTER_CODE _MyMonsterCode, int _MyMonsterNum) override;
//
//	void SetAIController(class AMonsterAIController* NewAIController);
//
//	EHammerKingState GetCurrentState();
//	EHammerKingAttackState GetCurrentAttackState();
//
//	UFUNCTION()
//		virtual void AttackHit() override;
//	UFUNCTION()
//		virtual void OnComboSave() override;
//	UFUNCTION()
//		virtual void OnMonsterAttackEnded() override;
//	UFUNCTION()
//		virtual void OnMonsterAttackChanged() override;
//	UFUNCTION()
//		virtual void Death() override;
//	void RandomAttack();
//	
//	
//};
