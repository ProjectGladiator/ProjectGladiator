// Fill out your copyright notice in the Description page of Project Settings.

#include "Dinosaur.h"
//클라 헤더
#include "UObject/ConstructorHelpers.h" // 경로 탐색
#include "Components/SkeletalMeshComponent.h" //스켈레탈 메쉬 헤더
#include "Animation/AnimBlueprint.h" // 애님 블루프린트
#include "DinosaurAnimInstance.h" //공룡 애님인스턴스 헤더
#include "DinosaurAIController.h"
#include "Particles/ParticleSystem.h"  //파티클 관련 헤더 파일
#include "Client/MyCharacter/MyCharacter.h" //캐릭터들 부모
#include "Kismet/GameplayStatics.h" //각종 유틸 헤더
#include "Client/Monster/Manager/AIManager.h" //AI담당 컴포넌트 헤더
#include "Components/CapsuleComponent.h" //캡슐 컴포넌트 헤더
#include "GameFrameWork/CharacterMovementComponent.h" //캐릭터 속도 관련 헤더
#include "Kismet/KismetMathLibrary.h" //수학 관련 헤더

//서버 헤더

ADinosaur::ADinosaur()
{
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = ADinosaurAIController::StaticClass();

	// 스켈레탈 메시찾아 메쉬에 세팅
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>SK_DinosaurMesh(TEXT("SkeletalMesh'/Game/Assets/Monster/ParagonMinions/Characters/Buff/Buff_Black/Meshes/Buff_Black.Buff_Black'"));
	if (SK_DinosaurMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_DinosaurMesh.Object);
	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem>PT_HitEffectTarget(TEXT("ParticleSystem'/Game/Assets/Monster/ParagonMinions/FX/Particles/Buffs/Buff_Black/Abilities/MeleeAttack/FX/P_BiteAttack_Impact.P_BiteAttack_Impact'"));

	if (PT_HitEffectTarget.Succeeded())
	{
		HitEffectTarget = PT_HitEffectTarget.Object;
	}

	// 애님블루프린트 찾아 메쉬에 세팅
	static ConstructorHelpers::FObjectFinder<UClass>ABP_Dinosaur(TEXT("AnimBlueprint'/Game/Blueprints/Monster/StageOne/Dinosaur/Blueprints/ABP_Dinosaur.ABP_Dinosaur_C'"));

	if (ABP_Dinosaur.Succeeded())  //찾는것에 성공햇으면
	{
		UClass* DinosaurAnimBlueprint = ABP_Dinosaur.Object; //오브젝트를 구하고

		if (DinosaurAnimBlueprint)
		{
			//메쉬에 사용할 애니메이션을 블루프린트로 정한다.
			GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
			GetMesh()->SetAnimInstanceClass(DinosaurAnimBlueprint);  //찾은 애니메이션블루프린트를 넣어준다.
		}
	}

	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	GetCharacterMovement()->MaxWalkSpeed = 400.0f;
}

void ADinosaur::BeginPlay()
{
	Super::BeginPlay();

	MaxHP = 100.0f;
	CurrentHP = MaxHP;

	TargetLimitDistance = 500.0f;
	AttackInfo.SetAttackInfo(150.0f, 70.0f, 120.0f);

	CurrentState = EDinosaurState::Idle;
	CurrentAttackState = EDinosaurAttackState::Idle;

	Target = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	DinosaurAnimInstance = Cast<UDinosaurAnimInstance>(GetMesh()->GetAnimInstance());

	if (DinosaurAnimInstance)
	{
		DinosaurAnimInstance->OnMonsterAttackHit.AddDynamic(this, &ADinosaur::AttackHit);
		DinosaurAnimInstance->OnDeath.AddDynamic(this, &ADinosaur::Death);
	}
}

void ADinosaur::Tick(float DeltaTime)
{
	if (Target)
	{
		float Distance = AIManager->DistanceCalculate(this, Target);

		switch (CurrentState)
		{
		case EDinosaurState::Idle:
			CurrentState = EDinosaurState::Chase;
			break;
		case EDinosaurState::Chase:
		{
			EPathFollowingRequestResult::Type GoalResult = AIManager->TargetChase(DinosaurAIController, Target, TargetLimitDistance);

			switch (GoalResult)
			{
			case EPathFollowingRequestResult::AlreadyAtGoal:
				CurrentAttackState = EDinosaurAttackState::RangeAttack;
				CurrentState = EDinosaurState::Attack;
				GLog->Log(FString::Printf(TEXT("공룡 골에 도착")));
				break;
			case EPathFollowingRequestResult::Failed:
				//GLog->Log(FString::Printf(TEXT("요청 실패")));
				break;
			case EPathFollowingRequestResult::RequestSuccessful:
				//GLog->Log(FString::Printf(TEXT("성공")));
				break;
			}
		}
			break;
		case EDinosaurState::Attack:
		{
			FRotator LooAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Target->GetActorLocation());
			//GLog->Log(FString::Printf(TEXT("Pitch : %f Yaw : %f"), LooAtRotation.Pitch, LooAtRotation.Yaw));
			SetActorRotation(LooAtRotation);

			if (Distance > TargetLimitDistance*1.5f)
			{
				CurrentState = EDinosaurState::Chase;
			}
			else
			{

			}
		}
			break;
		case EDinosaurState::Death:
			DeathInVisibleValue += 0.01;
			GetMesh()->SetScalarParameterValueOnMaterials(TEXT("Amount"), DeathInVisibleValue);

			if (DeathFlag)
			{
				Destroy();
			}
			break;
		}
	}
}

void ADinosaur::SetAIController(AMonsterAIController * NewAIController)
{
	DinosaurAIController = Cast<ADinosaurAIController>(NewAIController);
}

EDinosaurState ADinosaur::GetCurrentState()
{
	return CurrentState;
}

EDinosaurAttackState ADinosaur::GetCurrentAttackState()
{
	return CurrentAttackState;
}

void ADinosaur::AttackHit()
{
	FHitResult HitResult = AIManager->AttackRangeHitCreate(this, 1000.0f, TEXT("Muzzle_01"),false);

	if (HitResult.Actor.IsValid()) //원거리 데미지를 받은 액터가 현재 유효한지 판단한다.
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffectTarget, HitResult.Location);
	}
	
}

void ADinosaur::Death()
{
	DeathFlag = true;
}

float ADinosaur::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	CurrentHP -= DamageAmount;

	if (CurrentHP <= 0)
	{
		GetCapsuleComponent()->SetCollisionProfileName("OverlapOnlyPawn");
		CurrentHP = 0;
		CurrentState = EDinosaurState::Death;
	}

	return DamageAmount;
}
