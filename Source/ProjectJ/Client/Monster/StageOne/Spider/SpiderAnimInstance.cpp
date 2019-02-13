// Fill out your copyright notice in the Description page of Project Settings.

#include "SpiderAnimInstance.h"
//클라 헤더
#include "Spider.h" //거미 헤더
#include "UObject/ConstructorHelpers.h" // 경로 탐색

//서버 헤더

USpiderAnimInstance::USpiderAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage>SpiderDefaultAttack_Montage(TEXT("AnimMontage'/Game/Blueprints/Monster/StageOne/Spider/Animations/SpiderDefaultAttackMontage.SpiderDefaultAttackMontage'"));

	if (SpiderDefaultAttack_Montage.Succeeded())
	{
		AttackMontages.Add(SpiderDefaultAttack_Montage.Object);
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage>SpiderChargeAttack_Montage(TEXT("AnimMontage'/Game/Blueprints/Monster/StageOne/Spider/Animations/SpiderChargeAttackMontage.SpiderChargeAttackMontage'"));

	if (SpiderChargeAttack_Montage.Succeeded())
	{
		AttackMontages.Add(SpiderChargeAttack_Montage.Object);
	}
}

void USpiderAnimInstance::AnimNotify_MonsterAttackHit(UAnimNotify * Notify)
{
	OnMonsterAttackHit.Broadcast();	
}

void USpiderAnimInstance::AnimNotify_MonsterSaveAttack(UAnimNotify * Notify)
{
	OnMonsterComboSave.Broadcast();
}

void USpiderAnimInstance::AnimNotify_MonsterAttackEnded(UAnimNotify * Notify)
{
	OnMonsterAttackEnded.Broadcast();
}

void USpiderAnimInstance::AnimNotify_MonsterAttackChanged()
{
	OnMonsterAttackChanged.Broadcast();
}

void USpiderAnimInstance::AnimNotify_Death(UAnimNotify * Notify)
{
	OnDeath.Broadcast();
}

void USpiderAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Spider = Cast<ASpider>(TryGetPawnOwner());

	if (Spider && Spider->IsValidLowLevelFast())
	{
		CurrentState = Spider->GetCurrentState();
		CurrentAttackState = Spider->GetCurrentAttackState();
	}
}

void USpiderAnimInstance::PlayAttackMontage(int32 MontageSequence)
{
	Super::PlayAttackMontage(MontageSequence);
}

void USpiderAnimInstance::JumpAttackMontageSection(int32 MontageSequence, int32 NewSection)
{
	Super::JumpAttackMontageSection(MontageSequence, NewSection);
}
