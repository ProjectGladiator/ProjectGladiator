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
		ClickedReactionMontage = Clicked_Montage.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage>LevelStart_Montage(TEXT("AnimMontage'/Game/Blueprints/MyCharacter/User/Gunner/Animation/LevelStart_Montage.LevelStart_Montage'"));

	if (LevelStart_Montage.Succeeded())
	{
		LevelStartMontage = LevelStart_Montage.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage>Attack_Montage(TEXT("AnimMontage'/Game/Blueprints/MyCharacter/User/Gunner/Animation/AttackMontage.AttackMontage'"));

	if (Attack_Montage.Succeeded())
	{
		AttackMontage = Attack_Montage.Object;
	}
}

void UGunnerAnimInstance::AnimNotify_SaveAttack(UAnimNotify * Notify)
{
	OnComboSave.Broadcast();
}

void UGunnerAnimInstance::AnimNotify_ResetCombo(UAnimNotify * Notify)
{

}

void UGunnerAnimInstance::AnimNotify_AttackEnded(UAnimNotify * Notify)
{
	OnAttackEnded.Broadcast();
}

void UGunnerAnimInstance::PlayClickedReactionMontage()
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

void UGunnerAnimInstance::PlayLevelStartMontage()
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

void UGunnerAnimInstance::PlayAttackMontage()
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

void UGunnerAnimInstance::JumpAttackMontageSection(int32 NewSection)
{
	FName AttackMontageSection = GetAttackMontageSection(NewSection);
	Montage_JumpToSection(AttackMontageSection, AttackMontage);
}
