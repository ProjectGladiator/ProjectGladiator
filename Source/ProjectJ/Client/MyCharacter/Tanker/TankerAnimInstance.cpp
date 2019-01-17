﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "TankerAnimInstance.h"
//클라 헤더
#include "UObject/ConstructorHelpers.h" // 경로 탐색
//서버 헤더

UTankerAnimInstance::UTankerAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage>Clicked_Montage(TEXT("AnimMontage'/Game/Blueprints/MyCharacter/User/Tanker/Animations/ClickedReaction_Montage.ClickedReaction_Montage'"));

	if (Clicked_Montage.Succeeded())
	{
		ClickedReactionMontage = Clicked_Montage.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage>LevelStart_Montage(TEXT("AnimMontage'/Game/Blueprints/MyCharacter/User/Tanker/Animations/LevelStart_Montage.LevelStart_Montage'"));

	if (LevelStart_Montage.Succeeded())
	{
		LevelStartMontage = LevelStart_Montage.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage>Attack_Montage(TEXT("AnimMontage'/Game/Blueprints/MyCharacter/User/Tanker/Animations/AttackMontage.AttackMontage'"));

	if (Attack_Montage.Succeeded())
	{
		AttackMontage = Attack_Montage.Object;
	}
}

void UTankerAnimInstance::AnimNotify_SaveAttack(UAnimNotify* Notify)
{
	GLog->Log(FString::Printf(TEXT("콤보 공격 저장")));
	OnComboSave.Broadcast();
}

void UTankerAnimInstance::AnimNotify_ResetCombo(UAnimNotify* Notify)
{
	GLog->Log(FString::Printf(TEXT("콤보 공격 초기화")));
}

void UTankerAnimInstance::AnimNotify_AttackEnded(UAnimNotify* Notify)
{
	GLog->Log(FString::Printf(TEXT("공격 몽타주 끝")));
	OnAttackEnded.Broadcast();
}

void UTankerAnimInstance::PlayClickedReactionMontage()
{
	if (ClickedReactionMontage)
	{
		if (!Montage_IsPlaying(ClickedReactionMontage))
		{
			Montage_Play(ClickedReactionMontage, 1.0f);
		}
	}
	else
	{
		GLog->Log(FString::Printf(TEXT("반응 몽타주가 존재하지 않음")));
	}
}

void UTankerAnimInstance::PlayLevelStartMontage()
{
	if (LevelStartMontage)
	{
		if (!Montage_IsPlaying(LevelStartMontage))
		{
			Montage_Play(LevelStartMontage, 1.0f);
		}
	}
	else
	{
		GLog->Log(FString::Printf(TEXT("레벨 스타트 몽타주가 존재하지 않음")));
	}
}

void UTankerAnimInstance::PlayAttackMontage()
{
	if (AttackMontage)
	{
		if (!Montage_IsPlaying(AttackMontage))
		{
			Montage_Play(AttackMontage, 1.0f);
		}
	}
	else
	{
		GLog->Log(FString::Printf(TEXT("일반 공격 몽타주가 존재하지 않음")));
	}
}

void UTankerAnimInstance::JumpAttackMontageSection(int32 NewSection)
{
	FName AttackMontageSection = GetAttackMontageSection(NewSection);
	Montage_JumpToSection(AttackMontageSection, AttackMontage);
}
