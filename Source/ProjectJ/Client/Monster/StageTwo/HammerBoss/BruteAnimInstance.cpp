// Fill out your copyright notice in the Description page of Project Settings.

#include "BruteAnimInstance.h"
#include "Brute.h"
#include "UObject/ConstructorHelpers.h" 


UBruteAnimInstance::UBruteAnimInstance()
{

}

void UBruteAnimInstance::NativeUpdateAnimation(float DeltaSecnds)
{
	Super::NativeUpdateAnimation(DeltaSecnds);

	auto Brute = Cast<ABrute>(TryGetPawnOwner());

	if (Brute && Brute->IsValidLowLevelFast())
	{
		CurrentState = Brute->GetCurrnetState();
		CurrentAttackState = Brute->GetCurrentAttackState();
	}
}

void UBruteAnimInstance::AnimNotify_NomalAttackHit(UAnimNotify * Notify)
{
	OnMonsterAttackHit.Broadcast();
}

void UBruteAnimInstance::AnimNotify_KickAttackHit(UAnimNotify * Notify)
{
	OnKickAttack.Broadcast();
}

void UBruteAnimInstance::AnimNotify_JumpAttackHit(UAnimNotify * Notify)
{
	OnEarthQuake.Broadcast();
}

void UBruteAnimInstance::AnimNotify_Death(UAnimNotify * Notify)
{
	OnDeath.Broadcast();
}

