// Fill out your copyright notice in the Description page of Project Settings.

#include "SpiderAnimInstance.h"
//클라 헤더
#include "Spider.h"

//서버 헤더

USpiderAnimInstance::USpiderAnimInstance()
{
	
}

void USpiderAnimInstance::AnimNotify_MonsterAttackHit(UAnimNotify * Notify)
{
	OnMonsterAttackHit.Broadcast();	
}

void USpiderAnimInstance::AnimNotify_MonsterAttackEnded(UAnimNotify * Notify)
{
	OnMonsterAttackEnded.Broadcast();
}

void USpiderAnimInstance::AnimNotify_Death(UAnimNotify * Notify)
{
	OnDeath.Broadcast();
}

void USpiderAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Spider = Cast<ASpider>(TryGetPawnOwner());

	if (Spider && Spider->IsValidLowLevelFast())
	{
		CurrentState = Spider->GetCurrentState();
		CurrentAttackState = Spider->GetCurrentAttackState();
	}
}
