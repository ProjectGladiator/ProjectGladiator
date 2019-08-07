// Fill out your copyright notice in the Description page of Project Settings.

#include "Brute.h"

#pragma region ClientHeader
#include "UObject/ConstructorHelpers.h" // 경로 탐색 헤더
#include "Components/SkeletalMeshComponent.h" //스켈레탈 메쉬 헤더
#include "Kismet/GameplayStatics.h" //각종 유틸 헤더
#include "Client/Monster/Manager/AIManager.h" //AI담당 컴포넌트 헤더
#include "Client/MyCharacter/PC/MyCharacter.h" //캐릭터들 부모
#include "GameFrameWork/CharacterMovementComponent.h" //캐릭터 속도 관련 헤더
#include "Kismet/KismetSystemLibrary.h"  //라인 트레이스 헤더 관련 헤더
#include "Kismet/KismetMathLibrary.h" //수학 관련 헤더
#include "Components/CapsuleComponent.h" //캡슐 컴포넌트 헤더

#include "BruteAIController.h" //AI 컨트롤러 헤더
//#include "BruteAnimInstance.h" //애님 인스턴스 헤더
#pragma endregion 클라이언트 헤더

#pragma region ServerHeader
//Some ServerHeader
#pragma endregion 서버 헤더

#define SK_Address "SkeletalMesh'/Game/Assets/Monster/MixamoBrute/Anim/SK_BruteWR.SK_BruteWR'"
#define AnimBP_Address "AnimBlueprint'/Game/Assets/Monster/MixamoBrute/Anim/ABP_bruteWR.ABP_bruteWR_C'"

ABrute::ABrute()
{
	PrimaryActorTick.bCanEverTick = true;
	AIControllerClass = ABruteAIController::StaticClass();

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>SK_Brute(TEXT(SK_Address));
	if (SK_Brute.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_Brute.Object);
	}

	static ConstructorHelpers::FObjectFinder<UClass>ABP_Brute(TEXT(AnimBP_Address));
	if (ABP_Brute.Succeeded())
	{
		UClass* BruteAnimBlueprint = ABP_Brute.Object;
		if (BruteAnimBlueprint)
		{
			GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
			GetMesh()->SetAnimInstanceClass(BruteAnimBlueprint);
		}
	}

	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	GetCharacterMovement()->MaxWalkSpeed = 500.0f;
	DeathFlag = false;
	MaxHP = 100;
}

void ABrute::Init(MONSTER_CODE _MyMonsterCode, int _MyMonsterNum)
{
	Super::Init(_MyMonsterCode, _MyMonsterNum);

	CurrentState = EBruteState::Idle;

	CurrentHP = MaxHP;
}

void ABrute::SetAIController(AMonsterAIController * NewAIController)
{
	BruteAIController = Cast<ABruteAIController>(NewAIController);
}

void ABrute::BeginPlay()
{
	Super::BeginPlay();
	SetAIController(BruteAIController);

	TargetLimitDistance = 100.0f;
	AttackInfo.SetAttackInfo(50.0f, 80.0f, 120.0f);
	CurrentState = EBruteState::Idle;

	//BruteAnimInstance = Cast<UBruteAnimInstance>(GetMesh()->GetAnimInstance());
	/*if (BruteAnimInstance)
	{
		BruteAnimInstance->OnMonsterAttackHit.AddDynamic(this, &ABrute::AttackHit);
		BruteAnimInstance->OnDeath.AddDynamic(this, &ABrute::Death);
	}*/
}

void ABrute::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


EBruteState ABrute::GetCurrnetState()
{
	return CurrentState;
}

EBruteAttackState ABrute::GetCurrentAttackState()
{
	return CurrentAttackState;
}
