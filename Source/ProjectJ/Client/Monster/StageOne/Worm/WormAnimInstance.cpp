// Fill out your copyright notice in the Description page of Project Settings.

#include "WormAnimInstance.h"
//클라 헤더
#include "UObject/ConstructorHelpers.h" // 경로 탐색

//서버 헤더

UWormAnimInstance::UWormAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage>Explosion_Montage(TEXT("AnimMontage'/Game/Blueprints/Monster/StageOne/Worm/Animations/Explosion_Montage.Explosion_Montage'"));

	if (Explosion_Montage.Succeeded())
	{
		AttackMontages.Add(Explosion_Montage.Object);
	}
}

void UWormAnimInstance::AnimNotify_Death(UAnimNotify * Notify)
{
	GLog->Log(FString::Printf(TEXT("죽음 애님노티파이 호출")));
	OnDeath.Broadcast();
}

void UWormAnimInstance::PlayAttackMontage(int32 MontageSequence)
{
	if (AttackMontages[MontageSequence])
	{
		if (!Montage_IsPlaying(AttackMontages[MontageSequence]))
		{
			Montage_Play(AttackMontages[MontageSequence]);
		}
	}
}
