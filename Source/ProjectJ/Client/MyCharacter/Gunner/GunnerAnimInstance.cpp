// Fill out your copyright notice in the Description page of Project Settings.

#include "GunnerAnimInstance.h"
//클라 헤더
#include "UObject/ConstructorHelpers.h" // 경로 탐색
//서버 헤더

UGunnerAnimInstance::UGunnerAnimInstance()
{
	//총잡이 클릭반응 애니메이션을 에디터에서 찾고 Clicked_Montage에 저장한다.
	static ConstructorHelpers::FObjectFinder<UAnimMontage>Clicked_Montage(TEXT("AnimMontage'/Game/Blueprints/MyCharacter/User/Gunner/Animation/ClickedReaction_Montage.ClickedReaction_Montage'"));

	//잘 찾앗는지 확인한다.
	if (Clicked_Montage.Succeeded())
	{
		//찾앗으면 ClickedReactionMontage에 저장한다.
		ClickedReactionMontage = Clicked_Montage.Object;
	}

	//총잡이 레벨시작 애니메이션을 에디터에서 찾고 LevelStart_Montage에 저장한다.
	static ConstructorHelpers::FObjectFinder<UAnimMontage>LevelStart_Montage(TEXT("AnimMontage'/Game/Blueprints/MyCharacter/User/Gunner/Animation/LevelStart_Montage.LevelStart_Montage'"));

	//잘 찾앗는지 확인한다.
	if (LevelStart_Montage.Succeeded())
	{
		//찾앗으면 LevelStartMontage에 저장한다.
		LevelStartMontage = LevelStart_Montage.Object;
	}

	//총잡이 공격 애니메이션을 에디터에서 찾고 Attack_Montage에 저장한다.
	static ConstructorHelpers::FObjectFinder<UAnimMontage>Attack_Montage(TEXT("AnimMontage'/Game/Blueprints/MyCharacter/User/Gunner/Animation/AttackMontage.AttackMontage'"));

	//잘 찾앗는지 확인한다.
	if (Attack_Montage.Succeeded())
	{
		//찾앗으면 AttackMontage에 저장한다.
		AttackMontage = Attack_Montage.Object;
	}
}

void UGunnerAnimInstance::AnimNotify_SaveAttack(UAnimNotify * Notify)
{
	OnComboSave.Broadcast(); //OnComboSave 델리게이트에 연결된 모든 함수를 호출한다.
}

void UGunnerAnimInstance::AnimNotify_ResetCombo(UAnimNotify * Notify)
{

}

void UGunnerAnimInstance::AnimNotify_AttackHit(UAnimNotify * Notify)
{
	OnAttackHit.Broadcast();
}

void UGunnerAnimInstance::AnimNotify_AttackEnded(UAnimNotify * Notify)
{
	OnAttackEnded.Broadcast(); //OnAttackEnded 델리게이트에 연결된 모든 함수를 호출한다.
}

void UGunnerAnimInstance::PlayClickedReactionMontage()
{
	if (ClickedReactionMontage) //클릭반응 애니메이션 몽타주가 잇는지 확인하고
	{
		if (!Montage_IsPlaying(ClickedReactionMontage)) //현재 플레이 중이 아니면
		{
			Montage_Play(ClickedReactionMontage, 1.0f); //몽타주를 실행해준다.
		}
	}
	else
	{
		GLog->Log(FString::Printf(TEXT("반응 몽타주가 존재하지 않음")));
	}
}

void UGunnerAnimInstance::PlayLevelStartMontage()
{
	GLog->Log(FString::Printf(TEXT("총잡이 애님 인스턴스 레벨스타트 몽타주")));
	if (LevelStartMontage) //레벨시작 애니메이션 몽타주가 잇는지 확인하고
	{
		if (!Montage_IsPlaying(LevelStartMontage)) //현재 플레이 중이 아니면
		{
			Montage_Play(LevelStartMontage, 1.0f); //몽타주를 실행한다.
		}
	}
	else
	{
		GLog->Log(FString::Printf(TEXT("레벨 스타트 몽타주가 존재하지 않음")));
	}
}

void UGunnerAnimInstance::PlayAttackMontage()
{
	if (AttackMontage) //공격 애니메이션 몽타주가 있는지 확인하고
	{
		if (!Montage_IsPlaying(AttackMontage)) //현재 플레이 중이 아니면
		{
			Montage_Play(AttackMontage, 1.0f); //몽타주를 실행한다.
		}
	}
	else
	{
		GLog->Log(FString::Printf(TEXT("일반 공격 몽타주가 존재하지 않음")));
	}
}

void UGunnerAnimInstance::JumpAttackMontageSection(int32 NewSection)
{
	//다음에 실행할 섹션의 이름을 구해온다.
	FName AttackMontageSection = GetAttackMontageSection(NewSection); 
	//공격 애니메이션 몽타주에서 구해온 섹션 애니메이션을 실행해준다.
	Montage_JumpToSection(AttackMontageSection, AttackMontage);
}
