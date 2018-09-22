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

	// ���̷�Ż�޽� 
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>ArcherMonster_SkeletalMesh(TEXT("SkeletalMesh'/Game/Assets/Monster/Archer/Mesh/erika_archer_bow_arrow.erika_archer_bow_arrow'"));
	if (ArcherMonster_SkeletalMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(ArcherMonster_SkeletalMesh.Object);
	}

	// �ִԺ������Ʈ
	static ConstructorHelpers::FObjectFinder<UAnimBlueprint>Archer_AnimBlueprint(TEXT("AnimBlueprint'/Game/Blueprints/Monster/Mutant/Blueprints/ABP_MutantAnim.ABP_MutantAnim'"));
	if (Archer_AnimBlueprint.Succeeded())
	{
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		GetMesh()->SetAnimInstanceClass(Archer_AnimBlueprint.Object->GeneratedClass);
	}

	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));			// ���� ������Ʈ

																								//AIControllerClass = AArcherAIController::StaticClass();		// Ŭ���� ����

																								// �޽� ��ġ ��ȯ
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	// PawnSensing ����
	PawnSensing->bHearNoises = false;
	PawnSensing->bSeePawns = true;
	PawnSensing->SetPeripheralVisionAngle(45.0f);	// ���� ����
	PawnSensing->SightRadius = 2000.0f;				// ���� �Ÿ�
	PawnSensing->SensingInterval = 0.1f;				// ���� ����

														// Data ����
	PatrolGoalPosition = FVector::ZeroVector;

	// MaxHP = �����κ��� ü�� �޾ƿ�
	// CurrentHP = MaxHP;
	// Speed = �����κ��� ���ǵ带 �޾ƿ�
	// ���ݷ� = �����κ��� ���ݷ��� �޾ƿ�
	// ���� = �����κ��� ������ �޾ƿ�
	// DistanceForAttack = ���ݻ�Ÿ� ����
	// DistanceForPlayer = 0.0f;				// Ÿ�ٰ��� �Ÿ�
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

	// �����κ��� ���� ���¸� �޴´�

	// Ÿ���� ������ ��, Ÿ�ٰ��� �Ÿ��� ����
	if (Target)
		DistanceForPlayer = FVector::Distance(GetActorLocation(), Target->GetActorLocation());


	switch (CurrentState)
	{
	case EArcherState::Idle:			// ���̵����
		// �ð��� �������� ���ؼ� ������ ����
		// �ð���ŭ Ÿ�̸ӷ� ���

		// ���̵� ���µ��� Ÿ�ٹ߰�
		if (Target)
		{
			// ������ ��� ����

			// ������ ���� ����
			// Ÿ�̸� �ߴ�

			// ���� ���·� ��ȯ
			CurrentState = EArcherState::Battle;
		}
		// Ÿ�� �̹߰�
		else
		{
			// ������ ���� ����

			// ���� ���·� ��ȯ
			CurrentState = EArcherState::Patrol;
		}
		break;
	case EArcherState::Patrol:		// ���� ����
		// ���� �����϶� Ÿ�� �߰�
		if (Target)
		{
			CurrentState = EArcherState::Chase;					// ��������
			// �ӵ� ���� - �����κ��� �޾ƿ��°��� �ƴ϶�� ������ ���� ����

			// Ÿ���� �ٶ�
			FRotator LookRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Target->GetActorLocation());
			SetActorRotation(LookRotation);
		}
		// Ÿ�� �̹߰�
		else
		{
			CurrentAnimState = EArcherAnimState::Walk;

			// ���� ���͸� ������ġ ����
			if(PatrolGoalPosition.IsZero())
				PatrolGoalPosition = UKismetMathLibrary::RandomPointInBoundingBox(GetActorLocation(), FVector(300.0f, 300.0f, 0.0f));			// ����

			// ������ ���� ��ġ���� ����

			// ������ġ�� �̵�(�׽�Ʈ ����)
			// UKismetSystemLibrary::MoveComponentTo(GetMesh(), PatrolGoalPosition, FRotator(0.0f, 0.0f, 0.0f), false, false, 0.2f, false,

			// ������ġ�� �����ϸ�
			//{
			//	PatrolGoalPosition = FVector::ZeroVector;			// ������ġ �ʱ�ȭ
			//	CurrentState = EArcherState::Idle;
			//}
		}
		break;
	case EArcherState::Chase:		// ���� ����
		// ���� ���� ������ ����
		if (DistanceForPlayer < DistanceForAttack)
		{
			CurrentState = EArcherState::Battle;				// ���� ���·� ����
			Speed = 0.0f;			// �ӵ� 0
		}
		// ������
		else
		{
			CurrentAnimState = EArcherAnimState::Run;		// �޸���

			// ������ Ÿ���� ��ġ�� ����
			// ������ ���� ��ġ�� ����

			// Ÿ���� �ٶ�
			FRotator LookRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Target->GetActorLocation());
			SetActorRotation(LookRotation);

			// Ÿ������ �̵�(�׽�Ʈ ����)
			// UKismetSystemLibrary::MoveComponentTo(GetMesh(), Target->GetActorLocation(), FRotator(0.0f, 0.0f, 0.0f), false, false, 0.2f, false,
		}
		break;
	case EArcherState::Battle:		// ���� ����
		// ���� ���� ���� ���
		if (DistanceForPlayer > DistanceForAttack)
		{
			CurrentState = EArcherState::Chase;				// ���� ���·� ����
			// �ӵ� ���� - �����κ��� �޾ƿ��°��� �ƴ϶�� ������ ���� ����
		}
		// ���� ���� ����
		else
		{
			CurrentAnimState = EArcherAnimState::Attack;		// ����
			Speed = 0.0f;			// �ӵ� 0
		}
		break;
	case EArcherState::Dead:		// ���� ����
		// ����
		CurrentAnimState = EArcherAnimState::Death;

		// Death �ִϸ��̼����� ��ȯ
		// ������ ����ŭ Ÿ�̸ӷ� ���
		// ����
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

