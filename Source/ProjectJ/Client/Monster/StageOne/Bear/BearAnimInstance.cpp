// Fill out your copyright notice in the Description page of Project Settings.

#include "BearAnimInstance.h"
//클라 헤더
#include "Bear.h"

//서버 헤더

UBearAnimInstance::UBearAnimInstance()
{

}

void UBearAnimInstance::AnimNotify_MonsterAttackHit(UAnimNotify * Notify)
{
	OnMonsterAttackHit.Broadcast();
}

void UBearAnimInstance::AnimNotify_Death(UAnimNotify * Notify)
{
	OnDeath.Broadcast();
}

void UBearAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Bear = Cast<ABear>(TryGetPawnOwner());

	if (Bear && Bear->IsValidLowLevelFast())
	{
		CurrentState = Bear->GetCurrentState();
	}
}
