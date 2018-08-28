// Fill out your copyright notice in the Description page of Project Settings.

#include "ArcherMonster.h"
#include "UObject/ConstructorHelpers.h"				
#include "Components/SkeletalMeshComponent.h"		// For GetMesh
#include "Perception/PawnSensingComponent.h"		// For PawnSensingComponent

#include "Monster/ArcherMonster/ArcherAIController.h"		// connect class
#include "BehaviorTree/BehaviorTree.h"				// connect BehaviorTree
#include "Animation/AnimBlueprint.h"				// connect AnimationBlueprint
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

	// 비헤이비어트리
	static ConstructorHelpers::FObjectFinder<UBehaviorTree>ArcherMonster_BehaviorTree(TEXT("BehaviorTree'/Game/Blueprints/Monster/Archer/Bluepirnts/AI/ArcherBehaviorTree.ArcherBehaviorTree'"));
	if (ArcherMonster_BehaviorTree.Succeeded())
	{
		BehaviorTree = ArcherMonster_BehaviorTree.Object;
	}

	// 애님블루프린트
	static ConstructorHelpers::FObjectFinder<UAnimBlueprint>Archer_AnimBlueprint(TEXT("AnimBlueprint'/Game/Blueprints/Monster/Mutant/Blueprints/ABP_MutantAnim.ABP_MutantAnim'"));
	if (Archer_AnimBlueprint.Succeeded())
	{
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		GetMesh()->SetAnimInstanceClass(Archer_AnimBlueprint.Object->GeneratedClass);
	}

	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));

	AIControllerClass = AArcherAIController::StaticClass();

	PawnSensing->bHearNoises = false;
	PawnSensing->bSeePawns = true;
	PawnSensing->SetPeripheralVisionAngle(40.0f);
	PawnSensing->SightRadius = 1500.0f;
	PawnSensing->SensingInterval = 0.1f;

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

}

// Called to bind functionality to input
void AArcherMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AArcherMonster::OnSeeCharacter(APawn * Pawn)
{
}

float AArcherMonster::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	return 0.0f;
}

