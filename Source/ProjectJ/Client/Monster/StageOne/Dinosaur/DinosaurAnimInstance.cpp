// Fill out your copyright notice in the Description page of Project Settings.

#include "DinosaurAnimInstance.h"
//클라 헤더
#include "Dinosaur.h"

//서버 헤더

UDinosaurAnimInstance::UDinosaurAnimInstance()
{

}

void UDinosaurAnimInstance::AnimNotify_MonsterAttackHit(UAnimNotify * Notify)
{
	OnMonsterAttackHit.Broadcast();
}

void UDinosaurAnimInstance::AnimNotify_Death(UAnimNotify * Notify)
{
	OnDeath.Broadcast();
}

void UDinosaurAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Dinosaur = Cast<ADinosaur>(TryGetPawnOwner());

	if (Dinosaur && Dinosaur->IsValidLowLevelFast())
	{
		CurrentState = Dinosaur->GetCurrentState();
		CurrentAttackState = Dinosaur->GetCurrentAttackState();
	}
}
