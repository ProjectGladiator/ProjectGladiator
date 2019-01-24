// Fill out your copyright notice in the Description page of Project Settings.

#include "Bear.h"
//클라 헤더
#include "UObject/ConstructorHelpers.h" // 경로 탐색 헤더
#include "BearAIController.h" //곰 AI 컨트롤러 헤더
#include "Components/SkeletalMeshComponent.h" //스켈레탈 메쉬 헤더

//서버 헤더

ABear::ABear()
{
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = ABearAIController::StaticClass();

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>SK_Bear(TEXT("SkeletalMesh'/Game/Assets/Monster/InfinityBladeAdversaries/Enemy/Enemy_Bear/Enemy_Bear.Enemy_Bear'"));

	if (SK_Bear.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_Bear.Object);
	}
	// 애님블루프린트 찾아 메쉬에 세팅
	static ConstructorHelpers::FObjectFinder<UClass>ABP_Bear(TEXT("AnimBlueprint'/Game/Blueprints/Monster/Bear/Blueprints/ABP_Bear.ABP_Bear_C'"));

	if (ABP_Bear.Succeeded())  //찾는것에 성공햇으면
	{
		UClass* BearAnimBlueprint = ABP_Bear.Object; //오브젝트를 구하고

		if (BearAnimBlueprint)
		{
			//메쉬에 사용할 애니메이션을 블루프린트로 정한다.
			GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
			GetMesh()->SetAnimInstanceClass(BearAnimBlueprint);  //찾은 애니메이션블루프린트를 넣어준다.
		}
	}

	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
}

void ABear::Tick(float DeltaTime)
{
	switch (CurrentState)
	{
	case EBearState::Idle:
		break;
	case EBearState::Chase:
		break;
	case EBearState::Attack:
		break;
	case EBearState::Death:
		break;
	}
}
