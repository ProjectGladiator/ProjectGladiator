// Fill out your copyright notice in the Description page of Project Settings.

#include "TankerAnimInstance.h"
//클라 헤더
#include "UObject/ConstructorHelpers.h" // 경로 탐색
//서버 헤더

UTankerAnimInstance::UTankerAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage>Clicked_Montage(TEXT("AnimMontage'/Game/Blueprints/MyCharacter/User/Tanker/Animations/ClickedReaction_Montage.ClickedReaction_Montage'"));

	if (Clicked_Montage.Succeeded())
	{
		ClickedReaction = Clicked_Montage.Object;
	}
}

void UTankerAnimInstance::PlayClickedReactionMontage()
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
