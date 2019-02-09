// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MonsterAnimInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathDelegate); //죽음 애니메이션 델리게이트
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMonsterAttackHitDelegate); //몬스터 공격 판정 애니메이션 델리게이트
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMonsterComboSaveDelegate); //몬스터 콤보 저장 애니메이션 델리게이트
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMonsterAttackEndedDelegate); //공격 끝 애니메이션 델리게이트
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMonsterAttackChanged);

/**
 * 
 */
UCLASS()
class PROJECTJ_API UMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UMonsterAnimInstance(); //생성자
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Velocity, Meta = (AllowPrivateAccess = true))
		float Speed; //몬스터의 속력
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = IsRun, Meta = (AllowPrivateAccess = true))
		bool IsAccelerating; //가속 중인지 아닌지
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = IsJump, Meta = (AllowPrivateAccess = true))
		bool IsJump; //점프 중인지 아닌지
protected:
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = Montage)
		TArray<class UAnimMontage*> AttackMontages;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = IsAttack)
		bool IsAttack;

	FName GetMonsterAttackMontageSection(int32 NewSection);

	virtual void PlayAttackMontage(int32 MontageSequence); //공격 애니메이션 몽타주 실행
	virtual void JumpAttackMontageSection(int32 MontageSequence, int32 NewSection); //공격 애니메이션 몽타주 섹션 점프 해주는 함수
public:
	FOnDeathDelegate OnDeath;
	FOnMonsterAttackHitDelegate OnMonsterAttackHit;
	FOnMonsterComboSaveDelegate OnMonsterComboSave;
	FOnMonsterAttackEndedDelegate OnMonsterAttackEnded;
	FOnMonsterAttackChanged OnMonsterAttackChanged;

	UFUNCTION()
		virtual void NativeUpdateAnimation(float DeltaSeconds) override; // 틱 함수
	void SetIsAttack(bool _IsAttack);
};
