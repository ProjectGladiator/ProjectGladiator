//// Fill out your copyright notice in the Description page of Project Settings.
//
//#include "HammerKingAnimInstance.h"
//#include "HammerKing.h"
//#include "UObject/ConstructorHelpers.h"
//
//UHammerKingAnimInstance::UHammerKingAnimInstance()
//{
//
//}
//void UHammerKingAnimInstance::AnimNotify_Death(UAnimNotify * Notify)
//{
//	OnDeath.Broadcast();
//}
//
//void UHammerKingAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
//{
//	Super::NativeUpdateAnimation(DeltaSeconds);
//
//	auto Monster = Cast<AHammerKing>(TryGetPawnOwner());
//
//	if (Monster && Monster->IsValidLowLevelFast())
//	{
//		CurrentState = Monster->GetCurrentState();
//		CurrentAttackState = Monster->GetCurrentAttackState();
//	}
//}
//
