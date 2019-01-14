// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAnimInstance.h"
//클라 헤더
#include "MyCharacter.h" //캐릭터 부모 헤더
#include "GameFramework/CharacterMovementComponent.h" //캐릭터 속도 관련 헤더
//서버헤더

UMyAnimInstance::UMyAnimInstance()
{

}

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

void UMyAnimInstance::PlayClickedReactionMontage()
{

}
