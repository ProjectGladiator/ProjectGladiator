﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacter.h"
//클라 헤더
#include "GameFramework/SpringArmComponent.h" //스프링암 컴포넌트 헤더파일
#include "Camera/CameraComponent.h" //카메라 컴포넌트 헤더파일
#include "Client/Inventory/Inventory.h" //인벤토리 헤더파일
#include "GameFramework/CharacterMovementComponent.h" //캐릭터 속력 관련 헤더파일
#include "Animation/AnimBlueprint.h" //애니메이션블루프린트 헤더파일
#include "Engine/World.h"
#include "kismet/GameplayStatics.h"
#include "Client/ChracterCreateSelect/ChracterCreateSelectPC.h"
#include "Client/Title/TitlePlayerController.h"
#include "Warrior/Warrior.h"
#include "Tanker/Tanker.h"
#include "Gunner/Gunner.h"
#include "MyAnimInstance.h"
#include "UObject/ConstructorHelpers.h" // 경로 탐색
#include "Client/MainMap/MainMapPlayerController.h"
//서버 헤더
#include "NetWork/JobInfo.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	bUseControllerRotationYaw = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 800.0f;
	SpringArm->SetRelativeRotation(FRotator(-25.0f, 0, 0));

	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bInheritRoll = false;
	SpringArm->bDoCollisionTest = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	Inventory = CreateDefaultSubobject<UInventory>(TEXT("Inventory"));

	GetCharacterMovement()->MaxWalkSpeed = 500.0f;
	RightClickFlag = false;
	IsAttack = false;

	MaxHP = 100.0f;
	CurrentHP = MaxHP;
	Level = 0;

	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);

	Tags.Add(TEXT("Character"));
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	IsClick = false;

	MainMapPlayerController = Cast<AMainMapPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	MyAnimInstance = Cast<UMyAnimInstance>(GetMesh()->GetAnimInstance());
}

void AMyCharacter::ClickedReactionMontagePlay()
{

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

	PlayerInputComponent->BindAction(TEXT("RightClick"), IE_Pressed, this, &AMyCharacter::RightClickOn);
	PlayerInputComponent->BindAction(TEXT("RightClick"), IE_Released, this, &AMyCharacter::RightClickOff);

	PlayerInputComponent->BindAction(TEXT("Alt"), IE_Pressed, this, &AMyCharacter::SightOff);
	PlayerInputComponent->BindAction(TEXT("Alt"), IE_Released, this, &AMyCharacter::SightOn);

	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AMyCharacter::JumpStart);
	PlayerInputComponent->BindAction(TEXT("Attack"), IE_Pressed, this, &AMyCharacter::LeftClick);
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
	/*if (RightClickFlag && Value != 0)
	{
		AddControllerPitchInput(Value);
	}*/
	if (Value != 0)
	{
		AddControllerPitchInput(Value);
	}
}

void AMyCharacter::Turn(float Value)
{
	/*if (RightClickFlag && Value != 0)
	{
		AddControllerYawInput(Value);
	}*/
	if (Value != 0)
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

void AMyCharacter::RightClickOn()
{
	RightClickFlag = true;
}

void AMyCharacter::RightClickOff()
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

void AMyCharacter::JumpStart()
{
	Jump();
}

void AMyCharacter::LeftClick()
{
	GLog->Log(FString::Printf(TEXT("캐릭터 부모 상태에서 클릭")));
	if (MainMapPlayerController)
	{
		if (IsClick)
		{
			CharacterSelect();
		}
		else
		{
			GLog->Log(FString::Printf(TEXT("IsClick가 false")));
		}
	}
}

void AMyCharacter::CharacterSelect()
{
	GLog->Log(FString::Printf(TEXT("캐릭터 클릭 true")));
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	FHitResult HitResult;
	ObjectTypes.Add(EObjectTypeQuery::ObjectTypeQuery3); //Pawn타입으로 결정

	if (MainMapPlayerController->GetHitResultUnderCursorForObjects(ObjectTypes, true, HitResult))
	{
		auto Character = Cast<AWarrior>(HitResult.Actor);

		if (Character)
		{
			Character->ClickedReactionMontagePlay();
			GLog->Log(FString::Printf(TEXT("전사 클릭")));
			MainMapPlayerController->SelectCharacter(CHARACTER_JOB::WARRIOR);
		}
		else
		{
			auto Character = Cast<ATanker>(HitResult.Actor);

			if (Character)
			{
				Character->ClickedReactionMontagePlay();
				GLog->Log(FString::Printf(TEXT("탱커 클릭")));
				MainMapPlayerController->SelectCharacter(CHARACTER_JOB::TANKER);
			}
			else
			{
				auto Character = Cast<AGunner>(HitResult.Actor);

				if (Character)
				{
					Character->ClickedReactionMontagePlay();
					GLog->Log(FString::Printf(TEXT("총잡이 클릭")));
					MainMapPlayerController->SelectCharacter(CHARACTER_JOB::GUNNER);
				}
			}
		}
	}
}

void AMyCharacter::OnAttackMontageEnded()
{
	GLog->Log(FString::Printf(TEXT("IsAttack 초기화")));
	IsAttack = false; //false로 초기화
	IsCombo = false;
	CurrentCombo = 0; //콤보수 0으로 초기화
}

bool AMyCharacter::GetRightClickFlag()
{
	return RightClickFlag;
}

void AMyCharacter::OnComboMontageSave()
{
	//자식들에서 따로 구현
}

void AMyCharacter::OnAttackHit()
{
	//자식들에서 따로 구현
}

UMyAnimInstance* AMyCharacter::GetMyAnimInstance()
{
	return MyAnimInstance;
}

bool AMyCharacter::GetIsClick()
{
	return IsClick;
}

void AMyCharacter::SetIsClick(bool _IsClick)
{
	IsClick = _IsClick;
}
