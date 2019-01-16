﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "WarriorAnimInstance.h"
//클라 헤더
#include "UObject/ConstructorHelpers.h"
//서버 헤더

UWarriorAnimInstance::UWarriorAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage>Clicked_Montage(TEXT("AnimMontage'/Game/Blueprints/MyCharacter/User/Warrior/Animation/ClickedReaction_Montage.ClickedReaction_Montage'"));

	if (Clicked_Montage.Succeeded())
	{
		ClickedReaction = Clicked_Montage.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage>LevelStart_Montage(TEXT("AnimMontage'/Game/Blueprints/MyCharacter/User/Warrior/Animation/LevelStart_Montage.LevelStart_Montage'"));

	if (LevelStart_Montage.Succeeded())
	{
		LevelStart = LevelStart_Montage.Object;
	}
}

void UWarriorAnimInstance::PlayClickedReactionMontage()
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

void UWarriorAnimInstance::PlayLevelStartMontage()
{

}
