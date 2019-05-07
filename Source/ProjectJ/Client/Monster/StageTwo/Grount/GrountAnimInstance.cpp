// Fill out your copyright notice in the Description page of Project Settings.

#include "GrountAnimInstance.h"
#include "Grount.h"

UGrountAnimInstance::UGrountAnimInstance()
{

}
void UGrountAnimInstance::AnimNotify_MonsterAttackHit(UAnimNotify * Notify)
{
	OnMonsterAttackHit.Broadcast();
}

void UGrountAnimInstance::AnimNotify_Death(UAnimNotify * Notify)
{
	OnDeath.Broadcast();
}

void UGrountAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Grount = Cast<AGrount>(TryGetPawnOwner());

	if (Grount&& Grount->IsValidLowLevelFast())
	{
		CurrentState = Grount->GetCurrentState();
		CurrentAttackState = Grount->GetCurrentAttackState();
	}
}
