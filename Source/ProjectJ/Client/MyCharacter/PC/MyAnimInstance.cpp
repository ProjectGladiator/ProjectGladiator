﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAnimInstance.h"
//클라 헤더
#include "MyCharacter.h" //캐릭터 부모 헤더
#include "GameFramework/CharacterMovementComponent.h" //캐릭터 속도 관련 헤더
//서버헤더

UMyAnimInstance::UMyAnimInstance()
{
	
}

FName UMyAnimInstance::GetAttackMontageSection(int32 NewSection)
{
	//공격 몽타주의 섹션을 문자열로 조립해서 반환시켜준다.
	return FName(*FString::Printf(TEXT("Attack%d"), NewSection)); 
}

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);	

	auto MyCharacter = Cast<AMyCharacter>(TryGetPawnOwner()); //애님인스턴스를 사용하고 있는 폰을 얻어서 MyCharacter에 저장한다.

	//MyCharacter가 존재하는지, 메모리상에 유효한지 확인한다.
	if (MyCharacter && MyCharacter->IsValidLowLevelFast()) 
	{
		IsDead = MyCharacter->IsDead;
		//캐릭터의 속력과 회전값으로 방향값을 구해서 Direction에 저장한다.
		Direction = CalculateDirection(MyCharacter->GetCharacterMovement()->Velocity, MyCharacter->GetActorRotation());
		//캐릭터의 속력을 구한다.
		Speed = MyCharacter->GetCharacterMovement()->Velocity.Size();
		//캐릭터가 현재 점프중인지 아닌지 확인해준다.
		//true면 점프중, false면 지상
		IsJump = MyCharacter->GetCharacterMovement()->IsFalling();

		IsRightClick = MyCharacter->GetIsRightClick();
		//캐릭터의 속력이 0이상이면 가속중이라고 판단하고 0보다 작으면 비가속중이라고 판단한다.
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
	//캐릭터 생성창에서 캐릭터 선택시 실행해줄 애니메이션 자식 함수에서 따로 구현
}

void UMyAnimInstance::PlayLevelStartMontage()
{
	//캐릭터 선택창에서 슬롯 선택시 출력해줄 애니메이션 자식 함수에서 따로 구현
}

void UMyAnimInstance::PlayAttackMontage(float _RateScale)
{
	//공격 애니메이션 실행 자식 함수에서 따로 구현
}

void UMyAnimInstance::PlayRightClickAbilityMontage()
{
	
}

void UMyAnimInstance::PlayStopRightClickAbilityMontage()
{

}

void UMyAnimInstance::JumpAttackMontageSection(int32 NewSection)
{
	//공격 애니메이션 몽타주의 섹션을 매개변수로 받은 섹션으로 넘겨주는 함수 자식 함수에서 따로 구현
}
