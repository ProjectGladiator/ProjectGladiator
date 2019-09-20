// Fill out your copyright notice in the Description page of Project Settings.

#include "GriffonAnimInstance.h"
//클라 헤더
#include "Griffon.h"
#include "UObject/ConstructorHelpers.h"

UGriffonAnimInstance::UGriffonAnimInstance()
{

}

//서버 헤더
void UGriffonAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Griffon = Cast<AGriffon>(TryGetPawnOwner());

	if (Griffon && Griffon->IsValidLowLevelFast())
	{
		CurrentState = Griffon->GetCurrentState();
	}
}

void UGriffonAnimInstance::PlayAttackMontage(int32 MontageSequence)
{
	Super::PlayAttackMontage(MontageSequence);
}

void UGriffonAnimInstance::JumpAttackMontageSection(int32 MontageSequence, int32 NewSection)
{
	Super::JumpAttackMontageSection(MontageSequence, NewSection);
}
