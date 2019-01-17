// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttackEndedDelegate); //���� �ִϸ��̼� ��������Ʈ
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnComboSaveDelegate); //�޺� ���� �ִϸ��̼� ��������Ʈ

/**
 * 
 */
UCLASS()
class PROJECTJ_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Velocity, Meta = (AllowPrivateAccess = true))
		float Speed; //ĳ������ �ӷ�
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Velocity, Meta = (AllowPrivateAccess = true))
		float Direction; //ĳ������ ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = IsRun, Meta = (AllowPrivateAccess = true))
		bool IsAccelerating; //���� ������ �ƴ���
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = IsJump, Meta = (AllowPrivateAccess = true))
		bool IsJump; //���� ������ �ƴ���
protected:
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = Montage)
		class UAnimMontage* ClickedReactionMontage; //ĳ���� ����â���� ���ý� ������� �ִϸ��̼�
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Montage)
		class UAnimMontage* LevelStartMontage; //ĳ���� ����â���� ���� ���ý� ������� �ִϸ��̼�
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Montage)
		class UAnimMontage* AttackMontage; //ĳ���� ���ݾִϸ��̼� 

	FName GetAttackMontageSection(int32 NewSection); //ĳ���� ���ݾִϸ��̼�

	virtual void PlayClickedReactionMontage(); //ĳ���� ����â ���� �ִϸ��̼� ����
	virtual void PlayLevelStartMontage(); //ĳ���� ����â ���� ���� �ִϸ��̼� ����
	virtual void PlayAttackMontage(); //���� �ִϸ��̼� ����
	virtual void JumpAttackMontageSection(int32 NewSection); //���� �ִϸ��̼� ��Ÿ�� ���� ���� ���ִ� �Լ�
public:
	FOnAttackEndedDelegate OnAttackEnded; //���� �ִϸ��̼� �� ��������Ʈ ����
	FOnComboSaveDelegate OnComboSave; //�޺� ���� ��������Ʈ ����

	UMyAnimInstance(); //������

	UFUNCTION()
	virtual void NativeUpdateAnimation(float DeltaSeconds) override; // ƽ �Լ�
};
