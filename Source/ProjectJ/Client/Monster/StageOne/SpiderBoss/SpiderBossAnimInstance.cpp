// Fill out your copyright notice in the Description page of Project Settings.

#include "SpiderBossAnimInstance.h"
//클라 헤더
#include "SpiderBoss.h" //거미 보스 헤더
#include "UObject/ConstructorHelpers.h" // 경로 탐색

//서버 헤더

USpiderBossAnimInstance::USpiderBossAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage>SpiderBossDefaultAttack_Montage(TEXT("AnimMontage'/Game/Blueprints/Monster/StageOne/SpiderBoss/Animations/SpiderBossDefaultAttackMontage.SpiderBossDefaultAttackMontage'"));

	if (SpiderBossDefaultAttack_Montage.Succeeded())
	{
		AttackMontages.Add(SpiderBossDefaultAttack_Montage.Object);
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage>SpiderBossChargeAttack_Montage(TEXT("AnimMontage'/Game/Blueprints/Monster/StageOne/SpiderBoss/Animations/SpiderBossChargeAttackMontage.SpiderBossChargeAttackMontage'"));

	if (SpiderBossChargeAttack_Montage.Succeeded())
	{
		AttackMontages.Add(SpiderBossChargeAttack_Montage.Object);
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage>SpiderBossSummon_Montage(TEXT("AnimMontage'/Game/Blueprints/Monster/StageOne/SpiderBoss/Animations/SpiderBossSummonMontage.SpiderBossSummonMontage'"));

	if (SpiderBossSummon_Montage.Succeeded())
	{
		AttackMontages.Add(SpiderBossSummon_Montage.Object);
	}
}

void USpiderBossAnimInstance::AnimNotify_MonsterAttackHit()
{
	OnMonsterAttackHit.Broadcast();
}

void USpiderBossAnimInstance::AnimNotify_MonsterSaveAttack()
{
	OnMonsterComboSave.Broadcast();
}

void USpiderBossAnimInstance::AnimNotify_MonsterAttackEnded()
{
	OnMonsterAttackEnded.Broadcast();
}

void USpiderBossAnimInstance::AnimNotify_Death()
{
	OnDeath.Broadcast();
}

void USpiderBossAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto SpiderBoss = Cast<ASpiderBoss>(TryGetPawnOwner());

	if (SpiderBoss && SpiderBoss->IsValidLowLevelFast())
	{
		CurrentState = SpiderBoss->GetCurrentState();
	}
}

void USpiderBossAnimInstance::PlayAttackMontage(int32 MontageSequence)
{
	Super::PlayAttackMontage(MontageSequence);
}

void USpiderBossAnimInstance::JumpAttackMontageSection(int32 MontageSequence, int32 NewSection)
{
	Super::JumpAttackMontageSection(MontageSequence, NewSection);
}
