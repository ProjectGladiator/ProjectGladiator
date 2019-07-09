// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttackEndedDelegate); //공격 끝 애니메이션 델리게이트
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnComboSaveDelegate); //콤보 저장 애니메이션 델리게이트
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttackHitDelegate); //공격 판정 애니메이션 델리게이트

/**
 * 
 */
UCLASS()
class PROJECTJ_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
private:
	//캐릭터의 속력
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Velocity, Meta = (AllowPrivateAccess = true))
		float Speed;
	//캐릭터의 현재 방향
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Velocity, Meta = (AllowPrivateAccess = true))
		float Direction; 
	//가속 중인지 아닌지
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = IsRun, Meta = (AllowPrivateAccess = true))
		bool IsAccelerating; 
	//점프 중인지 아닌지
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = IsJump, Meta = (AllowPrivateAccess = true))
		bool IsJump;
	//오른쪽 클릭중인지 아닌지
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = IsRightClick, Meta = (AllowPrivateAccess = true))
		bool IsRightClick;
	//죽었는지 안 죽었는지
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = IsDead, Meta = (AllowPrivateAccess = true))
		bool IsDead;
protected:
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = Montage)
		class UAnimMontage* ClickedReactionMontage; //캐릭터 생성창에서 선택시 출력해줄 애니메이션
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Montage)
		class UAnimMontage* LevelStartMontage; //캐릭터 선택창에서 슬롯 선택시 출력해줄 애니메이션
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Montage)
		class UAnimMontage* AttackMontage; //캐릭터 공격애니메이션 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Montage)
		class UAnimMontage* RightClickAbilityMontage; //캐릭터 공격애니메이션 

	FName GetAttackMontageSection(int32 NewSection); //캐릭터 공격애니메이션

public:
	virtual void PlayClickedReactionMontage(); //캐릭터 생성창 선택 애니메이션 실행
	
	virtual void PlayLevelStartMontage(); //캐릭터 선택창 슬롯 선택 애니메이션 실행
	
	virtual void PlayAttackMontage(float _RateScale); //공격 애니메이션 실행
	
	virtual void PlayRightClickAbilityMontage();
	virtual void PlayStopRightClickAbilityMontage();

	virtual void JumpAttackMontageSection(int32 NewSection); //공격 애니메이션 몽타주 섹션 점프 해주는 함수

	FOnAttackEndedDelegate OnAttackEnded; //공격 애니메이션 끝 델리게이트 변수
	FOnComboSaveDelegate OnComboSave; //콤보 저장 델리게이트 변수
	FOnAttackHitDelegate OnAttackHit; //공격 판정 델리게이트 변수

	UMyAnimInstance(); //생성자

	UFUNCTION()
	virtual void NativeUpdateAnimation(float DeltaSeconds) override; // 틱 함수
};
