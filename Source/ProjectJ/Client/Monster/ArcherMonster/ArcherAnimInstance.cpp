// Fill out your copyright notice in the Description page of Project Settings.

#include "ArcherAnimInstance.h"

void UArcherAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UArcherAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}


// 애니메이션으로 공격동작일때
// 투사체 생성
// 생성된 투사체에게 특정방향으로 힘을 줆 or 생성된 투사체가 특정방향으로 이동하게 함
// 투사체 제거는 타겟에게 오버랩 or 특정시간이 지난 후 투사체C++에서 제거