// Fill out your copyright notice in the Description page of Project Settings.

#include "Grount.h"

#pragma region ClientHeader
#include "UObject/ConstructorHelpers.h" // 경로 탐색 헤더
#include "GrountAIController.h" //AI 컨트롤러 헤더
#include "Components/SkeletalMeshComponent.h" //스켈레탈 메쉬 헤더
#include "Kismet/GameplayStatics.h" //각종 유틸 헤더
#include "Client/Monster/Manager/AIManager.h" //AI담당 컴포넌트 헤더
#include "Client/MyCharacter/PC/MyCharacter.h" //캐릭터들 부모
#include "GameFrameWork/CharacterMovementComponent.h" //캐릭터 속도 관련 헤더
#include "GrountAnimInstance.h" //애님 인스턴스 헤더
#include "Kismet/KismetSystemLibrary.h"  //라인 트레이스 헤더 관련 헤더
#include "Kismet/KismetMathLibrary.h" //수학 관련 헤더
#include "Components/CapsuleComponent.h" //캡슐 컴포넌트 헤더
#pragma endregion 클라이언트 헤더

#pragma region ServerHeader
#pragma endregion 서버 헤더

#define SK_Address "SkeletalMesh'/Game/Assets/Monster/InfinityBladeAdversaries/Enemy/Enemy_Master_Grunt/SK_Master_Grunt.SK_Master_Grunt'"
#define AnimBP_Address "AnimBlueprint'/Game/Blueprints/Monster/StageTwo/Grunt/Blueprints/ABP_Grunt.ABP_Grunt_C'"

AGrount::AGrount()
{
	PrimaryActorTick.bCanEverTick = true;
	AIControllerClass = AGrountAIController::StaticClass();

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>SK_Grount(TEXT(SK_Address));
	if (SK_Grount.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_Grount.Object);
	}

	static ConstructorHelpers::FObjectFinder<UClass>ABP_Grount(TEXT(AnimBP_Address));
	if (ABP_Grount.Succeeded())  //찾는것에 성공햇으면
	{
		UClass* GrountAnimBlueprint = ABP_Grount.Object; //오브젝트를 구하고

		if (GrountAnimBlueprint)
		{
			//메쉬에 사용할 애니메이션을 블루프린트로 정한다.
			GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
			GetMesh()->SetAnimInstanceClass(GrountAnimBlueprint);  //찾은 애니메이션블루프린트를 넣어준다.
		}
	}

	//first set Mesh Relative's
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
}

void AGrount::BeginPlay()
{
	Super::BeginPlay();
	SetAIController(GrountAIcontroller);

	init();

	TargetLimitDistance = 150.0f;
	AttackInfo.SetAttackInfo(100, 100, 150);

	CurrentState = EGrountState::Idle;

	
	GrountAnimInstance = Cast<UGrountAnimInstance>(GetMesh()->GetAnimInstance());
	if (GrountAnimInstance)
	{
		//Add Dynamic Anim
		GrountAnimInstance->OnMonsterAttackHit.AddDynamic(this, &AGrount::AttackHit);
		GrountAnimInstance->OnDeath.AddDynamic(this, &AGrount::Death);
	}

}

void AGrount::Tick(float DeltaTime)
{
	if (Target)
	{
		float Distance = AIManager->DistanceCalculate(this, Target);

		switch (CurrentState)
		{
		case EGrountState::Ready:
			break;
		case EGrountState::Idle:
		{
			CurrentState = EGrountState::Chase;
		}
			break;
		case EGrountState::Chase:
		{
			EPathFollowingRequestResult::Type GoalResult = AIManager->TargetChase(GrountAIcontroller, Target, TargetLimitDistance);

			//추적 상태 변화값
			switch (GoalResult)
			{
			case EPathFollowingRequestResult::AlreadyAtGoal:
				//GLog->Log(FString::Printf(TEXT("골에 도착")));
				//CurrentAttackState = EGrountAttackState::
				CurrentState = EGrountState::Attack;
				break;
			case EPathFollowingRequestResult::Failed:
				//GLog->Log(FString::Printf(TEXT("요청 실패")));
				break;
			case EPathFollowingRequestResult::RequestSuccessful:
				//GLog->Log(FString::Printf(TEXT("성공")));
				CurrentState = EGrountState::Chase;
				break;
			}
		}
			break;
		//공격 상태
		case EGrountState::Attack:
		{
			FRotator LooAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Target->GetActorLocation());

			FRotator ToCharacterRotator = UKismetMathLibrary::NormalizedDeltaRotator(LooAtRotation, GetActorRotation());

			SetActorRotation(LooAtRotation);


			if (Distance > TargetLimitDistance*1.5f)
			{
				CurrentState = EGrountState::Chase;
			}
			else
			{

			}
		}
			break;
		//죽은 상태
		case EGrountState::Death:
		{
			DeathInVisibleValue += 0.01;
			GetMesh()->SetScalarParameterValueOnMaterials(TEXT("Amount"), DeathInVisibleValue);

			if (DeathFlag)
			{
				//We Not Use Destroy Function
				//Destroy();
				bisActive = false;
				Monster_SetActive(this, bisActive);
			}
		}
			break;
		}
	}
	else
	{
		GLog->Log(FString::Printf(TEXT("그런트: 타겟 존재 하지 않음")));
	}
}

void AGrount::init()
{
	Super::init();
	MaxHP = 300.0f;
	CurrentHP = MaxHP;
}

void AGrount::SetAIController(AMonsterAIController * NewAIController)
{
	GrountAIcontroller = Cast<AGrountAIController>(NewAIController);
}

EGrountState AGrount::GetCurrentState()
{
	return CurrentState;
}

EGrountAttackState AGrount::GetCurrentAttackState()
{
	return CurrentAttackState;
}

void AGrount::AttackHit()
{
	AIManager->AttackMeleeHitCreate(this, AttackInfo, false);
}

void AGrount::Death()
{
	DeathFlag = true;
}
