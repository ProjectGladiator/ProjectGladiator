// Fill out your copyright notice in the Description page of Project Settings.

#include "MutantAnimInstance.h"
#include "Monster/MutantMonster/MutantMonster.h"
#include "Kismet/GameplayStatics.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

void UMutantAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	CurrentFalling = false;
	PreviousFalling = false;

}

void UMutantAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	AMutantMonster* MutantMonster = Cast<AMutantMonster>(TryGetPawnOwner());
	FFindFloorResult FloorDistance;

	if (MutantMonster && MutantMonster->IsValidLowLevelFast())
	{
		Direction = CalculateDirection(MutantMonster->GetCharacterMovement()->Velocity, MutantMonster->GetActorRotation());
		CurrentState = MutantMonster->CurrentState;
		CurrentAnimState = MutantMonster->CurrentAnimState;
		CurrentJumpState = MutantMonster->CurrentJumpState;
		CurrentAttackState = MutantMonster->CurrentAttackState;
		LookAtRotator = MutantMonster->LookAtRotator;
	}
}

void UMutantAnimInstance::AnimNotify_JumpAttackStart(UAnimNotify * Notify)
{
	AMutantMonster* Mutant = Cast<AMutantMonster>(TryGetPawnOwner());

	if (Mutant)
	{
		FVector LaunchVector;
		FVector GoalVector = Mutant->Target->GetActorLocation();
		UGameplayStatics::SuggestProjectileVelocity_CustomArc(GetWorld(),
			LaunchVector,
			Mutant->GetActorLocation(),
			GoalVector,
			0,
			0.5f);
		UE_LOG(LogClass, Warning, TEXT("X : %f Y : %f Z :%f"), LaunchVector.X, LaunchVector.Y, LaunchVector.Z);
		Mutant->LaunchCharacter(LaunchVector, true, true);
	}
}

void UMutantAnimInstance::AnimNotify_JumpAttackEnd(UAnimNotify * Notify)
{
	AMutantMonster* Mutant = Cast<AMutantMonster>(TryGetPawnOwner());

	if (Mutant)
	{
		Mutant->CurrentJumpState = EMonsterJumpState::Idle;
		Mutant->CurrentAnimState = EMonsterAnimState::Run;
	}
}
