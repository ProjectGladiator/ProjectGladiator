// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacter.h"
//클라 헤더
#include "GameFramework/SpringArmComponent.h" //스프링암 컴포넌트 헤더파일
#include "Camera/CameraComponent.h" //카메라 컴포넌트 헤더파일
#include "Client/Inventory/Inventory.h" //인벤토리 헤더파일
#include "GameFramework/CharacterMovementComponent.h" //캐릭터 속력 관련 헤더파일
#include "Animation/AnimBlueprint.h" //애니메이션블루프린트 헤더파일
#include "Engine/World.h"
#include "kismet/GameplayStatics.h"
#include "Warrior/Warrior.h"
#include "Tanker/Tanker.h"
#include "Gunner/Gunner.h"
#include "MyAnimInstance.h"
#include "UObject/ConstructorHelpers.h" // 경로 탐색
#include "Client/MainMap/MainMapPlayerController.h"
#include "TimerManager.h"


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
	IsRightClick = false;
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

	if (MainMapPlayerController)
	{
		MainMapPlayerController->ControlOtherCharacterMove.AddDynamic(this, &AMyCharacter::ControlOtherCharacterMove);
	}

	MyAnimInstance = Cast<UMyAnimInstance>(GetMesh()->GetAnimInstance());

	ForwardBackWardMoveFlag = false;
	LeftRightMoveFlag = false;
}

void AMyCharacter::ClickedReactionMontagePlay()
{

}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//GLog->Log(FString::Printf(TEXT("%d %d"), ForwardBackWardMoveFlag, LeftRightMoveFlag)); 
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
	ForwadBackwardCurrentValue = Value;

	if (ForwadBackwardCurrentValue == 1 || ForwadBackwardCurrentValue == -1)
	{
		if (ForwadBackwardPreviousValue == 0)
		{
			ForwardBackWardMoveFlag = true;

			bool C2SMoveTimerActive = GetWorld()->GetTimerManager().IsTimerActive(C2SMoveUpdateTimer);

			if (!C2SMoveTimerActive)
			{
				GetWorld()->GetTimerManager().SetTimer(C2SMoveUpdateTimer, this, &AMyCharacter::C2S_MoveConfirm, 0.3f, true, 0);
			}
			//GLog->Log(FString::Printf(TEXT("앞 뒤 움직임 시작")));
		}
	}

	if (ForwadBackwardCurrentValue == 0)
	{
		if (ForwadBackwardPreviousValue == 1 || ForwadBackwardPreviousValue == -1)
		{
			bool C2SMoveTimerActive = GetWorld()->GetTimerManager().IsTimerActive(C2SMoveUpdateTimer);

			if (C2SMoveTimerActive)
			{
				if (!LeftRightMoveFlag)
				{
					GetWorld()->GetTimerManager().ClearTimer(C2SMoveUpdateTimer);
				}
				else
				{
					//GLog->Log(FString::Printf(TEXT("좌우로 움직이는 중임")));
				}
			}
			ForwardBackWardMoveFlag = false;
			//GLog->Log(FString::Printf(TEXT("앞 뒤 움직임 멈춤")));
		}
	}

	if (Value != 0)
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}

	ForwadBackwardPreviousValue = ForwadBackwardCurrentValue;
}

void AMyCharacter::MoveRight(float Value)
{
	LeftRightCurrentValue = Value;

	if (LeftRightCurrentValue == 1 || LeftRightCurrentValue == -1)
	{
		if (LeftRightPreviousValue == 0)
		{
			LeftRightMoveFlag = true;

			bool C2SMoveTimerActive = GetWorld()->GetTimerManager().IsTimerActive(C2SMoveUpdateTimer);

			if (!C2SMoveTimerActive)
			{
				GetWorld()->GetTimerManager().SetTimer(C2SMoveUpdateTimer, this, &AMyCharacter::C2S_MoveConfirm, 0.3f, true, 0);
			}
			//GLog->Log(FString::Printf(TEXT("좌 우 움직임 시작")));
		}
	}

	if (LeftRightCurrentValue == 0)
	{
		if (LeftRightPreviousValue == 1 || LeftRightPreviousValue == -1)
		{
			bool C2SMoveTimerActive = GetWorld()->GetTimerManager().IsTimerActive(C2SMoveUpdateTimer);

			if (C2SMoveTimerActive)
			{
				if (!ForwardBackWardMoveFlag)
				{
					GetWorld()->GetTimerManager().ClearTimer(C2SMoveUpdateTimer);
				}
				else
				{
					//GLog->Log(FString::Printf(TEXT("앞뒤로 움직이는 중임")));
				}
			}

			LeftRightMoveFlag = false;
			//GLog->Log(FString::Printf(TEXT("좌 우 움직임 멈춤")));
		}
	}

	if (Value != 0)
	{
		AddMovementInput(GetActorRightVector(), Value);
	}

	LeftRightPreviousValue = LeftRightCurrentValue;
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
	GLog->Log(FString::Printf(TEXT("오른쪽 마우스 클리익")));
	IsRightClick = true;
}

void AMyCharacter::RightClickOff()
{
	IsRightClick = false;
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
			MainMapPlayerController->SelectCharacter(CHARACTER_JOB::Warrior);
		}
		else
		{
			auto Character = Cast<ATanker>(HitResult.Actor);

			if (Character)
			{
				Character->ClickedReactionMontagePlay();
				GLog->Log(FString::Printf(TEXT("탱커 클릭")));
				MainMapPlayerController->SelectCharacter(CHARACTER_JOB::Tanker);
			}
			else
			{
				auto Character = Cast<AGunner>(HitResult.Actor);

				if (Character)
				{
					Character->ClickedReactionMontagePlay();
					GLog->Log(FString::Printf(TEXT("총잡이 클릭")));
					MainMapPlayerController->SelectCharacter(CHARACTER_JOB::Gunner);
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

bool AMyCharacter::GetIsRightClick()
{
	return IsRightClick;
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

void AMyCharacter::C2S_MoveConfirm()
{
	FVector Location = GetActorLocation();
	FRotator Rotation = GetActorRotation();

	GLog->Log(FString::Printf(TEXT("C2S_MoveConfirm 함수 호출 0.3s")));
	
	MainMapPlayerController->C2SMoveConfirm(Location, Rotation);
}

void AMyCharacter::S2C_MoveUpdate()
{
	//GLog->Log(FString::Printf(TEXT("GoalLocation X :%f Y : %f Z : %f"),GoalLocation.X,GoalLocation.Y,GoalLocation.Z));
	
	if (GetActorLocation().Equals(GoalLocation, 30.0f))
	{
		GLog->Log(FString::Printf(TEXT("목표 위치에 도착")));
		GetWorld()->GetTimerManager().ClearTimer(S2CMoveTimer);
	}

	SetActorRotation(GoalRotator);

	AddMovementInput(GoalDirection, 1.0f);
}

char * AMyCharacter::GetCharacterCode()
{
	return CharacterCode;
}

void AMyCharacter::SetCharacterCode(char * _NewCharacterCode)
{
	memcpy(CharacterCode, _NewCharacterCode, sizeof(CharacterCode));
}

void AMyCharacter::ControlOtherCharacterMove(FVector& _GoalLocation, FRotator& _GoalRotator)
{
	GoalRotator = _GoalRotator;
		
	GoalLocation = _GoalLocation;

	GoalDirection = GoalLocation - GetActorLocation();

	bool GoalDirectionNormalizeSuccess = GoalDirection.Normalize();

	if (GoalDirectionNormalizeSuccess)
	{
		if (!GetWorld()->GetTimerManager().IsTimerActive(S2CMoveTimer))
		{
			GetWorld()->GetTimerManager().SetTimer(S2CMoveTimer, this, &AMyCharacter::S2C_MoveUpdate, 0.01f, true, 0);
		}
	}
}
