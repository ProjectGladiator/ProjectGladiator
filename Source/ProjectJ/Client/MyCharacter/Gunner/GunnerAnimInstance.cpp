// Fill out your copyright notice in the Description page of Project Settings.

#include "GunnerAnimInstance.h"
//클라 헤더
#include "UObject/ConstructorHelpers.h" // 경로 탐색
//서버 헤더

UGunnerAnimInstance::UGunnerAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage>Clicked_Montage(TEXT("AnimMontage'/Game/Blueprints/MyCharacter/User/Gunner/Animation/ClickedReaction_Montage.ClickedReaction_Montage'"));

	if (Clicked_Montage.Succeeded())
	{
		ClickedReaction = Clicked_Montage.Object;
	}
}

void UGunnerAnimInstance::PlayClickedReactionMontage()
{
	if (ClickedReaction)
	{
		if (!Montage_IsPlaying(ClickedReaction))
		{
			Montage_Play(ClickedReaction, 1.0f);
		}
	}
	else
	{
		GLog->Log(FString::Printf(TEXT("반응 몽타주가 존재하지 않음")));
	}
}
