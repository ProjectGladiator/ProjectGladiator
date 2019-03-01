// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Client/MyCharacter/PC/MyAnimInstance.h"
#include "GunnerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API UGunnerAnimInstance : public UMyAnimInstance
{
	GENERATED_BODY()
public:
	UGunnerAnimInstance();
private:
	UFUNCTION()
		void AnimNotify_SaveAttack(UAnimNotify* Notify); //콤보 저장 노티파이
	UFUNCTION()
		void AnimNotify_ResetCombo(UAnimNotify* Notify); //콤보 리셋 노티파이
	UFUNCTION()
		void AnimNotify_AttackHit(UAnimNotify* Notify);
	UFUNCTION()
		void AnimNotify_AttackEnded(UAnimNotify* Notify); //공격 끝 노티파이
public:
	virtual void PlayClickedReactionMontage() override;  //캐릭터 생성창 선택 애니메이션 실행
	virtual void PlayLevelStartMontage() override;  //캐릭터 선택창 슬롯 선택 애니메이션 실행
	virtual void PlayAttackMontage() override; //공격 애니메이션 실행
	virtual void JumpAttackMontageSection(int32 NewSection) override; //공격 애니메이션 몽타주 섹션 점프 해주는 함수
};
