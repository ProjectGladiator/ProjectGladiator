﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "Dog.h"

#pragma region ClientHeader
#include "UObject/ConstructorHelpers.h" // 경로 탐색 헤더
#include "DogAIController.h" //AI 컨트롤러 헤더
#include "Components/SkeletalMeshComponent.h" //스켈레탈 메쉬 헤더
#include "Kismet/GameplayStatics.h" //각종 유틸 헤더
#include "Client/Monster/Manager/AIManager.h" //AI담당 컴포넌트 헤더
#include "Client/MyCharacter/PC/MyCharacter.h" //캐릭터들 부모
#include "GameFrameWork/CharacterMovementComponent.h" //캐릭터 속도 관련 헤더
#include "DogAnimInstance.h" //애님 인스턴스 헤더
#include "Kismet/KismetSystemLibrary.h"  //라인 트레이스 헤더 관련 헤더
#include "Kismet/KismetMathLibrary.h" //수학 관련 헤더
#include "Components/CapsuleComponent.h" //캡슐 컴포넌트 헤더
#pragma endregion 클라이언트 헤더

#pragma region ServerHeader
//Some ServerHeader
#pragma endregion 서버 헤더

ADog::ADog()
{
	PrimaryActorTick.bCanEverTick = true;
	AIControllerClass = ADogAIController::StaticClass();

#pragma region SkeletalMesh Set
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>SK_Dog(TEXT("SkeletalMesh'/Game/Assets/Monster/QuadrapedCreatures/Barghest/Meshes/SK_BARGHEST.SK_BARGHEST'"));

	if (SK_Dog.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_Dog.Object);
	}
#pragma endregion 스켈레탈 메쉬 세팅

#pragma region AnimBlueprint Set
	// 애님블루프린트 찾아 메쉬에 세팅
	static ConstructorHelpers::FObjectFinder<UClass>ABP_Dog(TEXT("AnimBlueprint'/Game/Blueprints/Monster/StageTwo/Dog/Blueprints/ABP_Dog.ABP_Dog_C'"));

	if (ABP_Dog.Succeeded())  //찾는것에 성공햇으면
	{
		UClass* DogAnimBlueprint = ABP_Dog.Object; //오브젝트를 구하고

		if (DogAnimBlueprint)
		{
			//메쉬에 사용할 애니메이션을 블루프린트로 정한다.
			GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
			GetMesh()->SetAnimInstanceClass(DogAnimBlueprint);  //찾은 애니메이션블루프린트를 넣어준다.
		}
	}
#pragma endregion 애님 블루프린트 메쉬 세팅

#pragma region Mesh Set To World pos
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
#pragma endregion 매쉬를 월드에 적용하기 위한 위치값

	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
}

void ADog::BeginPlay()
{
	Super::BeginPlay();

#pragma region HP, TagetLimit_Distance, AttackRange, State Set
	//MaxHP = 100.0f;
	//CurrentHP = MaxHP;
	init();

	TargetLimitDistance = 50.0f;

	AttackInfo.SetAttackInfo(50.0f, 80.0f, 120.0f);

	CurrentState = EDogState::Idle;
#pragma endregion 수치로 표현되는 초기화 값 모음

	Target = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	DogAnimInstance = Cast<UDogAnimInstance>(GetMesh()->GetAnimInstance());

	if (DogAnimInstance)
	{
		DogAnimInstance->OnMonsterAttackHit.AddDynamic(this, &ADog::AttackHit);
		//DogAnimInstance->OnMonsterComboSave.AddDynamic(this, &ADog::OnComboSave);
		//DogAnimInstance->OnMonsterAttackEnded.AddDynamic(this, &ADog::OnMonsterAttackEnded);
		DogAnimInstance->OnDeath.AddDynamic(this, &ADog::Death);
	}
}


void ADog::Tick(float DeltaTime)
{
	//타겟이 존재하면
	if (Target)
	{
		//타겟과의 거리 계산 return 값으로 (float)Distance가 반환
		float Distance = AIManager->DistanceCalculate(this, Target);

		//현재 State상태에 따라 변동 FSM
#pragma region Custom_FSM
		switch (CurrentState)
		{
			//대기 상태
		case EDogState::Idle:
		{
			CurrentState = EDogState::Chase;
		}
			break;
			//추적 상태	
		case EDogState::Chase:
		{
			//거리에 따른 추적 상태 변환 문구
			EPathFollowingRequestResult::Type GoalResult = AIManager->TargetChase(DogAIController, Target, TargetLimitDistance);

			//추적 상태 변화값
			switch (GoalResult)
			{
			case EPathFollowingRequestResult::AlreadyAtGoal:
				//GLog->Log(FString::Printf(TEXT("골에 도착")));
				CurrentState = EDogState::Attack;
				break;
			case EPathFollowingRequestResult::Failed:
				//GLog->Log(FString::Printf(TEXT("요청 실패")));
				break;
			case EPathFollowingRequestResult::RequestSuccessful:
				//GLog->Log(FString::Printf(TEXT("성공")));
				CurrentState = EDogState::Chase;
				break;
			}

		}
			break;
			//공격 상태
		case EDogState::Attack:
		{
			// 콤보 존재시 공격중에 콤보활성화 bool문
			if (IsAttack)
			{
				IsCombo = true;
			}
			//처음 공격시 활성화 문
			else
			{
				GLog->Log(FString::Printf(TEXT("개 처음 공격")));
				IsAttack = true;

			/*	if (DogAnimInstance)
				{
					DogAnimInstance->PlayAttackMontage(0);
					CurrentCombo += 1;
					DogAnimInstance->JumpAttackMontageSection(0, CurrentCombo);
				}*/
			}

#pragma region  RotateToTarget
			FRotator DogRotator = GetActorRotation();
			FRotator LooAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Target->GetActorLocation());

			FRotator ToCharacterRotator = UKismetMathLibrary::NormalizedDeltaRotator(LooAtRotation, DogRotator);

			//GLog->Log(FString::Printf(TEXT("ToCharacterRotator Yaw :%f\n"), ToCharacterRotator.Yaw));

			//GLog->Log(FString::Printf(TEXT("Pitch : %f Yaw : %f"), LooAtRotation.Pitch, LooAtRotation.Yaw));
			SetActorRotation(LooAtRotation);

			if (Distance > TargetLimitDistance*2.0f)
			{
				IsCombo = false;
				CurrentState = EDogState::Chase;
			}
#pragma endregion 공격시 타겟을 향해 회전
		}
			break;
			//죽은 상태
		case EDogState::Death:
		{
			DeathInVisibleValue += 0.01;
			GetMesh()->SetScalarParameterValueOnMaterials(TEXT("Amount"), DeathInVisibleValue);

			if (DeathFlag)
			{
				Destroy();
			}
		}
			break;
		}
#pragma endregion FMS (상태에 따라 행동변화)
	}
	//타겟이 없다면
	else
	{
		GLog->Log(FString::Printf(TEXT("개 : 타겟이 존재하지 않음")));
	}

}

void ADog::init()
{
	MaxHP = 50.0f;
	CurrentHP = MaxHP;
}


void ADog::SetAIController(AMonsterAIController * NewAIController)
{
	DogAIController = Cast<ADogAIController>(NewAIController);
}

EDogState ADog::GetCurrentState()
{
	return CurrentState;
}

void ADog::AttackHit()
{
	AIManager->AttackMeleeHitCreate(this, AttackInfo, false);
}

void ADog::Death()
{
	DeathFlag = true;
}

float ADog::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	CurrentHP -= DamageAmount;

	if (CurrentHP <= 0)
	{
		SetActorEnableCollision(false);
		CurrentHP = 0;
		CurrentState = EDogState::Death;
	}

	return DamageAmount;
}
