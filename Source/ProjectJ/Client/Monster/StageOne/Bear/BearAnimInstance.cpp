// Fill out your copyright notice in the Description page of Project Settings.

#include "BearAnimInstance.h"
//클라 헤더
#include "Bear.h"
#include "UObject/ConstructorHelpers.h" // 경로 탐색

//서버 헤더

UBearAnimInstance::UBearAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage>BearAttack_Montage(TEXT("AnimMontage'/Game/Blueprints/Monster/StageOne/Bear/Animations/BearAttackMontage.BearAttackMontage'"));

	if (BearAttack_Montage.Succeeded())
	{
		GLog->Log(FString::Printf(TEXT("곰 공격 몽타주 셋팅")));
		AttackMontages.Add(BearAttack_Montage.Object);
	}
}

void UBearAnimInstance::AnimNotify_MonsterAttackHit(UAnimNotify * Notify)
{
	OnMonsterAttackHit.Broadcast();
}

void UBearAnimInstance::AnimNotify_MonsterSaveAttack(UAnimNotify * Notify)
{
	OnMonsterComboSave.Broadcast();
}

void UBearAnimInstance::ANimNotify_MonsterAttackEnded()
{
	GLog->Log(FString::Printf(TEXT("곰 공격 끝 애님 노티파이 호출")));
	OnMonsterAttackEnded.Broadcast();
}

void UBearAnimInstance::AnimNotify_Death(UAnimNotify * Notify)
{
	OnDeath.Broadcast();
}

void UBearAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Bear = Cast<ABear>(TryGetPawnOwner());

	if (Bear && Bear->IsValidLowLevelFast())
	{
		CurrentState = Bear->GetCurrentState();
	}
}

void UBearAnimInstance::PlayAttackMontage(int32 MontageSequence)
{
	Super::PlayAttackMontage(MontageSequence);
}

void UBearAnimInstance::JumpAttackMontageSection(int32 MontageSequence,int32 NewSection)
{
	Super::JumpAttackMontageSection(MontageSequence, NewSection);
}
