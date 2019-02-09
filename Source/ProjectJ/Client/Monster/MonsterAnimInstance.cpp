// Fill out your copyright notice in the Description page of Project Settings.

#include "MonsterAnimInstance.h"
//클라 헤더
#include "Monster.h"
#include "GameFramework/CharacterMovementComponent.h" //캐릭터 속도 관련 헤더
//서버 헤더

UMonsterAnimInstance::UMonsterAnimInstance()
{

}

FName UMonsterAnimInstance::GetMonsterAttackMontageSection(int32 NewSection)
{
	return FName(*FString::Printf(TEXT("MonsterAttack%d"), NewSection));
}

void UMonsterAnimInstance::PlayAttackMontage(int32 MontageSequence)
{
	if (AttackMontages[MontageSequence])
	{
		if (!Montage_IsPlaying(AttackMontages[MontageSequence]))
		{
			Montage_Play(AttackMontages[MontageSequence]);
		}
	}
}

void UMonsterAnimInstance::JumpAttackMontageSection(int32 MontageSequence, int32 NewSection)
{
	FName AttackMontageSection = GetMonsterAttackMontageSection(NewSection);
	Montage_JumpToSection(AttackMontageSection, AttackMontages[MontageSequence]);
}

void UMonsterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Monster = Cast<AMonster>(TryGetPawnOwner());

	if (Monster && Monster->IsValidLowLevelFast())
	{
		//몬스터의 속력을 구한다.
		Speed = Monster->GetCharacterMovement()->Velocity.Size();

		//몬스터의 속력이 0이상이면 가속중이라고 판단하고 0보다 작으면 비가속중이라고 판단한다.
		if (Monster->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0)
		{
			GLog->Log(FString::Printf(TEXT("몬스터 가속중")));
			IsAccelerating = true;
		}
		else
		{
			IsAccelerating = false;
		}
	}
}

void UMonsterAnimInstance::SetIsAttack(bool _IsAttack)
{
	IsAttack = _IsAttack;
}