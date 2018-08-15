// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimNotifyState_ParryingAttack.h"

#include "Components/SkeletalMeshComponent.h"
#include "Monster/MutantMonster/MutantMonster.h"

void UAnimNotifyState_ParryingAttack::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	AMutantMonster* Mutant = Cast<AMutantMonster>(MeshComp->GetOwner());
	
	if (Mutant)
	{
		Mutant->ParryingFlag = true;
	}
}

void UAnimNotifyState_ParryingAttack::NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);

	AMutantMonster* Mutant = Cast<AMutantMonster>(MeshComp->GetOwner());

	if (Mutant)
	{
		
	}
}

void UAnimNotifyState_ParryingAttack::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	AMutantMonster* Mutant = Cast<AMutantMonster>(MeshComp->GetOwner());

	if (Mutant)
	{
		Mutant->ParryingFlag = false;
	}
}
