// Fill out your copyright notice in the Description page of Project Settings.

#include "WarriorAnimInstance.h"
//클라 헤더
#include "UObject/ConstructorHelpers.h"
//서버 헤더

UWarriorAnimInstance::UWarriorAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage>Clicked_Montage(TEXT("AnimMontage'/Game/Blueprints/MyCharacter/User/Warrior/Animation/ClickedReaction_Montage.ClickedReaction_Montage'"));

	if (Clicked_Montage.Succeeded())
	{
		ClickedReactionMontage = Clicked_Montage.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage>LevelStart_Montage(TEXT("AnimMontage'/Game/Blueprints/MyCharacter/User/Warrior/Animation/LevelStart_Montage.LevelStart_Montage'"));

	if (LevelStart_Montage.Succeeded())
	{
		LevelStartMontage = LevelStart_Montage.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage>Attack_Montage(TEXT("AnimMontage'/Game/Blueprints/MyCharacter/User/Warrior/Animation/AttackMontage.AttackMontage'"));

	if (Attack_Montage.Succeeded())
	{
		AttackMontage = Attack_Montage.Object;
	}
}

void UWarriorAnimInstance::AnimNotify_SaveAttack(UAnimNotify * Notify)
{
	GLog->Log(FString::Printf(TEXT("콤보 공격 저장")));
	OnComboSave.Broadcast();
}

void UWarriorAnimInstance::AnimNotify_ResetCombo(UAnimNotify * Notify)
{

}

void UWarriorAnimInstance::AnimNotify_AttackEnded(UAnimNotify * Notify)
{
	GLog->Log(FString::Printf(TEXT("공격 몽타주 끝")));
	OnAttackEnded.Broadcast();
}

void UWarriorAnimInstance::PlayClickedReactionMontage()
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

void UWarriorAnimInstance::PlayLevelStartMontage()
{

}

void UWarriorAnimInstance::PlayAttackMontage()
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

void UWarriorAnimInstance::JumpAttackMontageSection(int32 NewSection)
{
	FName AttackMontageSection = GetAttackMontageSection(NewSection);
	Montage_JumpToSection(AttackMontageSection, AttackMontage);
}
