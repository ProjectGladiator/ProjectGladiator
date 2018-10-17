// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacter.h"
#include "GameFramework/SpringArmComponent.h" //스프링암 컴포넌트 헤더파일
#include "Camera/CameraComponent.h" //카메라 컴포넌트 헤더파일
#include "Inventory/Inventory.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimBlueprint.h"
#include "Particles/ParticleSystem.h"
#include "TimerManager.h"
#include "Monster/PatrolPoint.h"
#include "Engine/World.h"
#include "kismet/GameplayStatics.h"

#include "ChracterCreateSelect/ChracterCreateSelectPC.h"
#include "Title/TitlePlayerController.h"
#include "Warrior/Warrior.h"
#include "Tanker/Tanker.h"
#include "Wizard/Wizard.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationYaw = true;
		
	SpringArm=CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 800.0f;
	SpringArm->SetRelativeRotation(FRotator(-25.0f, 0, 0));

	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bInheritRoll = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	Inventory = CreateDefaultSubobject<UInventory>(TEXT("Inventory"));

	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	RightClickFlag = false;
	ToRunFlag = false;
	
	MaxHP = 100.0f;
	CurrentHP = MaxHP;
	Level = 0;

	Tags.Add(TEXT("Character"));
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	AttackPointSet();

	CharacterCreateSelectPC = Cast<AChracterCreateSelectPC>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AMyCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AMyCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AMyCharacter::Turn);

	PlayerInputComponent->BindAction(TEXT("ViewExpand"), IE_Pressed, this, &AMyCharacter::ViewExpand);
	PlayerInputComponent->BindAction(TEXT("ViewReduce"), IE_Pressed, this, &AMyCharacter::ViewReduce);

	PlayerInputComponent->BindAction(TEXT("ViewRightClick"), IE_Pressed, this, &AMyCharacter::ViewRightClickOn);
	PlayerInputComponent->BindAction(TEXT("ViewRightClick"), IE_Released, this, &AMyCharacter::ViewRightClickOff);

	PlayerInputComponent->BindAction(TEXT("Alt"), IE_Pressed, this, &AMyCharacter::SightOff);
	PlayerInputComponent->BindAction(TEXT("Alt"), IE_Released, this, &AMyCharacter::SightOn);

	PlayerInputComponent->BindAction(TEXT("ToRun"), IE_Pressed, this, &AMyCharacter::ToRun);

	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AMyCharacter::JumpStart);
	PlayerInputComponent->BindAction(TEXT("LeftClick"), IE_Pressed, this, &AMyCharacter::LeftClick);
}

void AMyCharacter::MoveForward(float Value)
{
	if (Value != 0)
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AMyCharacter::MoveRight(float Value)
{
	if (Value != 0)
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AMyCharacter::LookUp(float Value)
{
	if (RightClickFlag && Value != 0)
	{
		AddControllerPitchInput(Value);
	}
}

void AMyCharacter::Turn(float Value)
{
	if (RightClickFlag && Value != 0)
	{
		AddControllerYawInput(Value);
	}
}

void AMyCharacter::ViewExpand()
{
	if (SpringArm->TargetArmLength == 1200)
	{
		return;
	}
	SpringArm->TargetArmLength += 20;
}

void AMyCharacter::ViewReduce()
{
	if (SpringArm->TargetArmLength == 260)
	{
		return;
	}
	SpringArm->TargetArmLength -= 20;
}

void AMyCharacter::ViewRightClickOn()
{
	RightClickFlag = true;
}

void AMyCharacter::ViewRightClickOff()
{
	RightClickFlag = false;
}

void AMyCharacter::SightOff()
{
	bUseControllerRotationYaw = false;
}

void AMyCharacter::SightOn()
{
	bUseControllerRotationYaw = true;
}	

void AMyCharacter::ToRun()
{	
	if (ToRunFlag)
	{
		ToRunFlag = false;
		GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	}
	else
	{
		ToRunFlag = true;
		GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	}
}

void AMyCharacter::JumpStart()
{
	Jump();
}

void AMyCharacter::LeftClick()
{
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	FHitResult HitResult;
	ObjectTypes.Add(EObjectTypeQuery::ObjectTypeQuery3); //Pawn타입으로 결정

	if (CharacterCreateSelectPC)
	{
		if (CharacterCreateSelectPC->GetHitResultUnderCursorForObjects(ObjectTypes, true, HitResult))
		{
			AWarrior* Character = Cast<AWarrior>(HitResult.Actor);
			if (Character)
			{
				CharacterCreateSelectPC->SelectCharacter(2000);
			}
			else
			{
				ATanker* Character = Cast<ATanker>(HitResult.Actor);

				if (Character)
				{
					CharacterCreateSelectPC->SelectCharacter(1000);
				}
				else
				{
					AWizard* Character = Cast<AWizard>(HitResult.Actor);

					if (Character)
					{
						CharacterCreateSelectPC->SelectCharacter(3000);
					}
				}
			}
		}	
	}	
}

void AMyCharacter::AttackPointSet()
{
	APatrolPoint* AttackPoint;
	FAttachmentTransformRules AttachRules(EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, false);
	FVector CalculatePoint;
	FVector InitPoint = GetActorLocation();
	FVector Point;
	
	CalculatePoint = InitPoint;
	CalculatePoint.X = InitPoint.X + 200.0f;
	Point = CalculatePoint;

	AttackPoint = GetWorld()->SpawnActor<APatrolPoint>(AttackPoint->StaticClass(), Point, this->GetActorRotation());
	AttackPoints.Add(AttackPoint);
	AttackPoint->AttachToComponent(RootComponent, AttachRules);

	CalculatePoint.X = InitPoint.X - 200.0f;
	Point = CalculatePoint;
	AttackPoint = GetWorld()->SpawnActor<APatrolPoint>(AttackPoint->StaticClass(), Point, this->GetActorRotation());
	AttackPoints.Add(AttackPoint);
	AttackPoint->AttachToComponent(RootComponent, AttachRules);

	CalculatePoint = InitPoint;
	CalculatePoint.Y = InitPoint.Y - 200.0f;
	Point = CalculatePoint;
	AttackPoint = GetWorld()->SpawnActor<APatrolPoint>(AttackPoint->StaticClass(), Point, this->GetActorRotation());
	AttackPoints.Add(AttackPoint);
	AttackPoint->AttachToComponent(RootComponent, AttachRules);

	CalculatePoint.Y = InitPoint.Y + 200.0f;
	Point = CalculatePoint;
	AttackPoint = GetWorld()->SpawnActor<APatrolPoint>(AttackPoint->StaticClass(), Point, this->GetActorRotation());
	AttackPoints.Add(AttackPoint);
	AttackPoint->AttachToComponent(RootComponent, AttachRules);

	CalculatePoint = InitPoint;
	CalculatePoint.X = InitPoint.X + 200.0f;
	CalculatePoint.Y = InitPoint.Y - 200.0f;
	Point = CalculatePoint;
	AttackPoint = GetWorld()->SpawnActor<APatrolPoint>(AttackPoint->StaticClass(), Point, this->GetActorRotation());
	AttackPoints.Add(AttackPoint);
	AttackPoint->AttachToComponent(RootComponent, AttachRules);

	CalculatePoint = InitPoint;
	CalculatePoint.X = InitPoint.X + 200.0f;
	CalculatePoint.Y = InitPoint.Y + 200.0f;
	Point = CalculatePoint;
	AttackPoint = GetWorld()->SpawnActor<APatrolPoint>(AttackPoint->StaticClass(), Point, this->GetActorRotation());
	AttackPoints.Add(AttackPoint);
	AttackPoint->AttachToComponent(RootComponent, AttachRules);

	CalculatePoint = InitPoint;
	CalculatePoint.X = InitPoint.X - 200.0f;
	CalculatePoint.Y = InitPoint.Y - 200.0f;
	Point = CalculatePoint;
	AttackPoint = GetWorld()->SpawnActor<APatrolPoint>(AttackPoint->StaticClass(), Point, this->GetActorRotation());
	AttackPoints.Add(AttackPoint);
	AttackPoint->AttachToComponent(RootComponent, AttachRules);

	CalculatePoint = InitPoint;
	CalculatePoint.X = InitPoint.X - 200.0f;
	CalculatePoint.Y = InitPoint.Y + 200.0f;
	Point = CalculatePoint;
	AttackPoint = GetWorld()->SpawnActor<APatrolPoint>(AttackPoint->StaticClass(), Point, this->GetActorRotation());
	AttackPoints.Add(AttackPoint);
	AttackPoint->AttachToComponent(RootComponent, AttachRules);

} 