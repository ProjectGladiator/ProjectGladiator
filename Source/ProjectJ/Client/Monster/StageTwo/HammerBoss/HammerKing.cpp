//// Fill out your copyright notice in the Description page of Project Settings.
//#include "HammerKing.h"
//#include "UObject/ConstructorHelpers.h" //경로 탐색 헤더
//#include "Components/SkeletalMeshComponent.h" //스켈레탈 메쉬 헤더
//#include "GameFrameWork/CharacterMovementComponent.h" //캐릭터 속도 관련 헤더
//#include "Client/MyCharacter/PC/MyCharacter.h" //캐릭터들 부모
//#include "Kismet/GameplayStatics.h" //각종 유틸 헤더
//#include "Client/Monster/Manager/AIManager.h" //AI담당 컴포넌트 헤더
////#include "HammerKingAIController.h" //HammerKing AI
//#include "Kismet/KismetMathLibrary.h" //수학 관련 헤더
////#include "HammerKingAnimInstance.h"
//#include "Components/CapsuleComponent.h"
//#include <time.h>
//
//#define SK_Address "SkeletalMesh'/Game/Assets/Monster/MixamoBrute/Anim/SK_BruteWR.SK_BruteWR'"
//#define AnimBP_Address "AnimBlueprint'/Game/Assets/Monster/MixamoBrute/Anim/ABP_bruteWR.ABP_bruteWR_C'"
//
//AHammerKing::AHammerKing()
//{
//	PrimaryActorTick.bCanEverTick = true;
//
//	//AIControllerClass = AHammerKingAIController::StaticClass();
//
//	static ConstructorHelpers::FObjectFinder<USkeletalMesh>SK_HammerKing(TEXT(SK_Address));
//	if (SK_HammerKing.Succeeded())
//	{
//		GetMesh()->SetSkeletalMesh(SK_HammerKing.Object);
//	}
//
//	static ConstructorHelpers::FObjectFinder<UClass>ABP_HammerKing(TEXT(AnimBP_Address));
//	if (ABP_HammerKing.Succeeded())
//	{
//		UClass* HammerKingBlueprint = ABP_HammerKing.Object;
//		if (HammerKingBlueprint)
//		{
//			GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
//			GetMesh()->SetAnimInstanceClass(HammerKingBlueprint);
//		}
//	}
//
//	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
//	GetMesh()->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
//	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
//
//	GetCharacterMovement()->MaxWalkSpeed = 700.0f;
//	DeathFlag = false;
//	MaxHP = 100;
//}
//
//void AHammerKing::BeginPlay()
//{
//	Super::BeginPlay();
//	//SetAIController(HammerKingAIController);
//
//	TargetLimitDistance = 150.0f;
//
//	AttackInfo.SetAttackInfo(50.0f, 80.0f, 120.0f);
//
//	CurrentState = EHammerKingState::Idle;
//
//	HammerKingAnimInstance = Cast<UHammerKingAnimInstance>(GetMesh()->GetAnimInstance());
//
//	if (HammerKingAnimInstance)
//	{
//		//HammerKingAnimInstance->OnMonsterAttackHit.AddDynamic(this, &AHammerKing::AttackHit);
//		//HammerKingAnimInstance->OnDeath.AddDynamic(this, &AHammerKing::Death);
//	}
//}
//
//void AHammerKing::Tick(float DeltaTime)
//{
//}
//
//void AHammerKing::Init(MONSTER_CODE _MyMonsterCode, int _MyMonsterNum)
//{
//}
//
//void AHammerKing::SetAIController(AMonsterAIController * NewAIController)
//{
//}
//
//EHammerKingState AHammerKing::GetCurrentState()
//{
//	return EHammerKingState();
//}
//
//EHammerKingAttackState AHammerKing::GetCurrentAttackState()
//{
//	return EHammerKingAttackState();
//}
//
//void AHammerKing::AttackHit()
//{
//}
//
//void AHammerKing::OnComboSave()
//{
//}
//
//void AHammerKing::OnMonsterAttackEnded()
//{
//}
//
//void AHammerKing::OnMonsterAttackChanged()
//{
//}
//
//void AHammerKing::Death()
//{
//}
//
//void AHammerKing::RandomAttack()
//{
//}
