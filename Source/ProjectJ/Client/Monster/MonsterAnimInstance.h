// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MonsterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API UMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Velocity, Meta = (AllowPrivateAccess = true))
		float Speed; //몬스터의 속력
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = IsRun, Meta = (AllowPrivateAccess = true))
		bool IsAccelerating; //가속 중인지 아닌지
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = IsJump, Meta = (AllowPrivateAccess = true))
		bool IsJump; //점프 중인지 아닌지
public:
	UMonsterAnimInstance(); //생성자

	UFUNCTION()
		virtual void NativeUpdateAnimation(float DeltaSeconds) override; // 틱 함수
};
