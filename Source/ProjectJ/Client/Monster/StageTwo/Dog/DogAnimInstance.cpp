// Fill out your copyright notice in the Description page of Project Settings.

#include "DogAnimInstance.h"
#include "Dog.h"
#include "UObject/ConstructorHelpers.h" // °æ·Î Å½»ö


UDogAnimInstance::UDogAnimInstance()
{
	//Dog'sSomething_Montage
	//static ConstructorHelpers::FObjectFinder<UAnimMontage>)MontageName(TEXT("AnimMontage'/Game/Blueprints/Monster/StageOne/Bear/Animations/BearAttackMontage.BearAttackMontage'"));

	/*if (something_Montage.Succeeded())
	{
		
		AttackMontages.Add(BearAttack_Montage.Object);
	}*/
}

void UDogAnimInstance::AnimNotify_MonsterAttackHit(UAnimNotify * Notify)
{
	OnMonsterAttackHit.Broadcast();
}

void UDogAnimInstance::AnimNotify_Death(UAnimNotify * Notify)
{
	OnDeath.Broadcast();
}
