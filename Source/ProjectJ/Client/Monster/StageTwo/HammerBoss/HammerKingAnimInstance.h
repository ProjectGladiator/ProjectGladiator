//// Fill out your copyright notice in the Description page of Project Settings.
//
//#pragma once
//
//#include "CoreMinimal.h"
//#include "Client/Monster/MonsterAnimInstance.h"
//#include "Client/State/MonsterState/MonsterState.h"
//#include "HammerKingAnimInstance.generated.h"
//
///**
// * 
// */
//UCLASS()
//class PROJECTJ_API UHammerKingAnimInstance : public UMonsterAnimInstance
//{
//	GENERATED_BODY()
//public:
//	UHammerKingAnimInstance();
//private:
//	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State, Meta = (AllowPrivateAccess = true))
//		EHammerKingState CurrentState;
//	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State, Meta = (AllowPrivateAccess = true))
//		EHammerKingAttackState CurrentAttackState;
//
//	UFUNCTION()
//		void AnimNotify_Death(UAnimNotify* Notify);
//public:
//	UFUNCTION()
//		virtual void NativeUpdateAnimation(float DeltaSeconds) override; // 틱 함수	
//};
