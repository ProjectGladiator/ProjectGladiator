// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAnimInstance.h"
#include "MyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	AMyCharacter* MyCharacter = Cast<AMyCharacter>(TryGetPawnOwner());

	if (MyCharacter && MyCharacter->IsValidLowLevelFast())
	{
		Direction = CalculateDirection(MyCharacter->GetCharacterMovement()->Velocity, MyCharacter->GetActorRotation());
		Speed = MyCharacter->GetCharacterMovement()->Velocity.Size();

		IsJump = MyCharacter->GetCharacterMovement()->IsFalling();
		if (MyCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0)
		{
			IsAccelerating = true;
		}		
		else
		{
			IsAccelerating = false;
		}
	}
}
