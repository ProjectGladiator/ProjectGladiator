// Fill out your copyright notice in the Description page of Project Settings.

#include "MutantMonster.h"
#include "Components/SkeletalMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

#include "Perception/PawnSensingComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Monster/MutantMonster/MutantAIController.h"
#include "MyCharacter/MyCharacter.h"

#include "Components/BoxComponent.h"

#include "Animation/AnimBlueprint.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Animation/AnimMontage.h"

#include "Engine/World.h"
#include "TimerManager.h"

// Sets default values
AMutantMonster::AMutantMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>Monster_SK_Mesh(TEXT("SkeletalMesh'/Game/Assets/Monster/Mutant/Mesh/mutant.mutant'"));

	if (Monster_SK_Mesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(Monster_SK_Mesh.Object);
	}

	GetMesh()->SetRelativeLocation(FVector(0, 0, -88.0f));
	GetMesh()->SetRelativeRotation(FRotator(0, -90.0f, 0));

	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));
	PawnSensing->bHearNoises = false;
	PawnSensing->bSeePawns = true;
	PawnSensing->SetPeripheralVisionAngle(40.0f);
	PawnSensing->SightRadius = 1500.0f;
	PawnSensing->SensingInterval = 0.1f;

	static ConstructorHelpers::FObjectFinder<UBehaviorTree>Monster_BT(TEXT("BehaviorTree'/Game/Blueprints/Monster/Mutant/Blueprints/AI/BT_Mutant.BT_Mutant'"));

	if (Monster_BT.Succeeded())
	{
		BehaviorTree = Monster_BT.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimBlueprint>ABP_Mutant(TEXT("AnimBlueprint'/Game/Blueprints/Monster/Mutant/Blueprints/ABP_MutantAnim.ABP_MutantAnim'"));

	if (ABP_Mutant.Succeeded())
	{
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		GetMesh()->SetAnimInstanceClass(ABP_Mutant.Object->GeneratedClass);
	}

	AIControllerClass = AMutantAIController::StaticClass();

	static ConstructorHelpers::FObjectFinder<UAnimMontage>Reaction_Montage(TEXT("AnimMontage'/Game/Blueprints/Monster/Mutant/Animations/ReactionMontage.ReactionMontage'"));

	if (Reaction_Montage.Succeeded())
	{
		ReactionMontage = Reaction_Montage.Object;
	}

	CurrentState = EMonsterState::Idle;
	CurrentAnimState = EMonsterAnimState::Wait;
	CurrentJumpState = EMonsterJumpState::Idle;
	JumpEndFlag = false;
	JumpRunCheckFlag = true;
	RunCheckFlag = true;
	ParryingFlag = false;
	IsParrying = false;

	MaxHP = 200.0f;
	CurrentHP = MaxHP;
	DeathMaterialsValue = 0;
}

// Called when the game starts or when spawned
void AMutantMonster::BeginPlay()
{
	Super::BeginPlay();
	
	if (PawnSensing)
	{
		PawnSensing->OnSeePawn.AddDynamic(this, &AMutantMonster::OnSeeCharacter);
	}

	GetMesh()->SetScalarParameterValueOnMaterials(TEXT("Boost"), 4.0f);
	GetMesh()->SetScalarParameterValueOnMaterials(TEXT("Width"), 0.1f);
}

// Called every frame
void AMutantMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AMutantAIController* AI = Cast<AMutantAIController>(GetController());

	GLog->Log(FString::Printf(TEXT("%f"), GetCharacterMovement()->Velocity.Size()));
	if (AI)
	{
		AI->BBComponent->SetValueAsEnum("CurrentState", (uint8)CurrentState);
		AI->BBComponent->SetValueAsEnum("CurrentAnimState", (uint8)CurrentAnimState);
		AI->BBComponent->SetValueAsEnum("CurrentJumpState", (uint8)CurrentJumpState);
		LookAtRotator = AI->BBComponent->GetValueAsRotator("LookAtRotator");
		CurrentFalling = GetCharacterMovement()->IsFalling();
		AI->BBComponent->SetValueAsBool("CurrentFalling", CurrentFalling);
		AI->BBComponent->SetValueAsEnum("CurrentAttackState", (uint8)CurrentAttackState);
		//UE_LOG(LogClass, Warning, TEXT("%d"), JumpRunCheckFlag);
		//UE_LOG(LogClass, Warning, TEXT("HP : %0.1f"), CurrentHP);
		//UE_LOG(LogClass, Warning, TEXT("ParryingFlag : %d"), ParryingFlag);
		//UE_LOG(LogClass,Warning,TEXT("%f"), GetCharacterMovement()->Velocity.Size());
	}
}

// Called to bind functionality to input
void AMutantMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMutantMonster::OnSeeCharacter(APawn* Pawn)
{
	if (Pawn->ActorHasTag("Character"))
	{
		AMutantAIController* AI = Cast<AMutantAIController>(GetController());

		if (AI)
		{
			switch (CurrentState)
			{
			case EMonsterState::Idle:
				AI->BBComponent->SetValueAsObject("Player", Pawn);
				Target = Pawn;
				CurrentState = EMonsterState::Idle;
				CurrentAnimState = EMonsterAnimState::Roar;
				break;
			case EMonsterState::Chase:
				break;
			case EMonsterState::Battle:
				break;
			case EMonsterState::Patrol:
				break;
			case EMonsterState::Dead:
				break;
			}
		}
	}
}

float AMutantMonster::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	CurrentHP -= Damage;

	if (CurrentHP <= 0)
	{
		CurrentHP = 0;
		GetWorldTimerManager().SetTimer(DeathTimer, this, &AMutantMonster::Death, 0.1f, true);
		CurrentState = EMonsterState::Dead;
	}

	if (ParryingFlag)
	{
		UE_LOG(LogClass, Warning, TEXT("패링 조건 발동 !!"));
		IsParrying = true;
		CurrentAnimState = EMonsterAnimState::Parrying;
	}
	else
	{
		PlayAnimMontage(ReactionMontage);
	}
	return Damage;
}

void AMutantMonster::Death()
{
	DeathMaterialsValue += 0.01;

	if (DeathMaterialsValue >= 1)
	{
		GetWorldTimerManager().ClearTimer(DeathTimer);
	}

	GetMesh()->SetScalarParameterValueOnMaterials(TEXT("Amount"), DeathMaterialsValue);
}

