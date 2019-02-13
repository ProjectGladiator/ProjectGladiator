// Fill out your copyright notice in the Description page of Project Settings.

#include "SpiderBossAnimInstance.h"
//클라 헤더
#include "SpiderBoss.h" //거미 보스 헤더
#include "UObject/ConstructorHelpers.h" // 경로 탐색

//서버 헤더

USpiderBossAnimInstance::USpiderBossAnimInstance()
{

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
