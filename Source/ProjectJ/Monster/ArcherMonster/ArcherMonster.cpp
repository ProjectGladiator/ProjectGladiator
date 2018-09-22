// Fill out your copyright notice in the Description page of Project Settings.

#include "ArcherMonster.h"
#include "UObject/ConstructorHelpers.h"				
#include "Components/SkeletalMeshComponent.h"		// For GetMesh
#include "Perception/PawnSensingComponent.h"		// For PawnSensingComponent
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Animation/AnimBlueprint.h"

// Sets default values
AArcherMonster::AArcherMonster()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 스켈레탈메시 
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>ArcherMonster_SkeletalMesh(TEXT("SkeletalMesh'/Game/Assets/Monster/Archer/Mesh/erika_archer_bow_arrow.erika_archer_bow_arrow'"));
	if (ArcherMonster_SkeletalMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(ArcherMonster_SkeletalMesh.Object);
	}

	// 애님블루프린트
	static ConstructorHelpers::FObjectFinder<UAnimBlueprint>Archer_AnimBlueprint(TEXT("AnimBlueprint'/Game/Blueprints/Monster/Mutant/Blueprints/ABP_MutantAnim.ABP_MutantAnim'"));
	if (Archer_AnimBlueprint.Succeeded())
	{
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		GetMesh()->SetAnimInstanceClass(Archer_AnimBlueprint.Object->GeneratedClass);
	}

	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));			// 감각 컴포넌트

																								//AIControllerClass = AArcherAIController::StaticClass();		// 클래스 설정

																								// 메시 위치 변환
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	// PawnSensing 세팅
	PawnSensing->bHearNoises = false;
	PawnSensing->bSeePawns = true;
	PawnSensing->SetPeripheralVisionAngle(45.0f);	// 감지 각도
	PawnSensing->SightRadius = 2000.0f;				// 감지 거리
	PawnSensing->SensingInterval = 0.1f;				// 감지 간격

														// Data 세팅
	PatrolGoalPosition = FVector::ZeroVector;

	// MaxHP = 서버로부터 체력 받아옴
	// CurrentHP = MaxHP;
	// Speed = 서버로부터 스피드를 받아옴
	// 공격력 = 서버로부터 공격력을 받아옴
	// 방어력 = 서버로부터 방어력을 받아옴
	// DistanceForAttack = 공격사거리 설정
	// DistanceForPlayer = 0.0f;				// 타겟과의 거리
}

// Called when the game starts or when spawned
void AArcherMonster::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AArcherMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 서버로부터 현재 상태를 받는다

	// 타겟이 존재할 때, 타겟과의 거리를 구함
	if (Target)
		DistanceForPlayer = FVector::Distance(GetActorLocation(), Target->GetActorLocation());


	switch (CurrentState)
	{
	case EArcherState::Idle:			// 아이들상태
		// 시간을 랜덤으로 구해서 서버로 전달
		// 시간만큼 타이머로 대기

		// 아이들 상태동안 타겟발견
		if (Target)
		{
			// 서버로 사실 전달

			// 서버로 상태 전달
			// 타이머 중단

			// 전투 상태로 변환
			CurrentState = EArcherState::Battle;
		}
		// 타겟 미발견
		else
		{
			// 서버로 상태 전달

			// 순찰 상태로 변환
			CurrentState = EArcherState::Patrol;
		}
		break;
	case EArcherState::Patrol:		// 순찰 상태
		// 순찰 상태일때 타겟 발견
		if (Target)
		{
			CurrentState = EArcherState::Chase;					// 추적상태
			// 속도 설정 - 서버로부터 받아오는것이 아니라면 임의의 수로 설정

			// 타겟을 바라봄
			FRotator LookRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Target->GetActorLocation());
			SetActorRotation(LookRotation);
		}
		// 타겟 미발견
		else
		{
			CurrentAnimState = EArcherAnimState::Walk;

			// 제로 벡터면 랜덤위치 구함
			if(PatrolGoalPosition.IsZero())
				PatrolGoalPosition = UKismetMathLibrary::RandomPointInBoundingBox(GetActorLocation(), FVector(300.0f, 300.0f, 0.0f));			// 예시

			// 서버로 현재 위치정보 보냄

			// 랜덤위치로 이동(테스트 요함)
			// UKismetSystemLibrary::MoveComponentTo(GetMesh(), PatrolGoalPosition, FRotator(0.0f, 0.0f, 0.0f), false, false, 0.2f, false,

			// 랜덤위치에 도달하면
			//{
			//	PatrolGoalPosition = FVector::ZeroVector;			// 랜덤위치 초기화
			//	CurrentState = EArcherState::Idle;
			//}
		}
		break;
	case EArcherState::Chase:		// 추적 상태
		// 공격 가능 범위에 진입
		if (DistanceForPlayer < DistanceForAttack)
		{
			CurrentState = EArcherState::Battle;				// 전투 상태로 변경
			Speed = 0.0f;			// 속도 0
		}
		// 미진입
		else
		{
			CurrentAnimState = EArcherAnimState::Run;		// 달리기

			// 서버로 타겟의 위치를 보냄
			// 서버로 현재 위치를 보냄

			// 타겟을 바라봄
			FRotator LookRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Target->GetActorLocation());
			SetActorRotation(LookRotation);

			// 타겟으로 이동(테스트 요함)
			// UKismetSystemLibrary::MoveComponentTo(GetMesh(), Target->GetActorLocation(), FRotator(0.0f, 0.0f, 0.0f), false, false, 0.2f, false,
		}
		break;
	case EArcherState::Battle:		// 전투 상태
		// 공격 가능 범위 벗어남
		if (DistanceForPlayer > DistanceForAttack)
		{
			CurrentState = EArcherState::Chase;				// 추적 상태로 변경
			// 속도 설정 - 서버로부터 받아오는것이 아니라면 임의의 수로 설정
		}
		// 공격 가능 범위
		else
		{
			CurrentAnimState = EArcherAnimState::Attack;		// 공격
			Speed = 0.0f;			// 속도 0
		}
		break;
	case EArcherState::Dead:		// 죽음 상태
		// 듁음
		CurrentAnimState = EArcherAnimState::Death;

		// Death 애니메이션으로 변환
		// 임의의 수만큼 타이머로 대기
		// 삭제
		break;
	}
}

// Called to bind functionality to input
void AArcherMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AArcherMonster::OnSeeCharacter(APawn * Pawn)
{
	if (Pawn->ActorHasTag("Character"))
	{
		if (!Target)
		{
			Target = Pawn;
			CurrentState = EArcherState::Chase;
			CurrentAnimState = EArcherAnimState::Run;
		}
	}
}

float AArcherMonster::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	return 0.0f;
}

