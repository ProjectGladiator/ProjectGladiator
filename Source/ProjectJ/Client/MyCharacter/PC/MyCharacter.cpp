// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacter.h"
//클라 헤더
#include "GameFramework/SpringArmComponent.h" //스프링암 컴포넌트 헤더파일
#include "Camera/CameraComponent.h" //카메라 컴포넌트 헤더파일
#include "GameFramework/CharacterMovementComponent.h" //캐릭터 속력 관련 헤더파일
#include "Animation/AnimBlueprint.h" //애니메이션블루프린트 헤더파일
#include "Engine/World.h"
#include "kismet/GameplayStatics.h"
#include "kismet/KismetMathLibrary.h"
#include "Warrior/Warrior.h"
#include "Tanker/Tanker.h"
#include "Gunner/Gunner.h"
#include "MyAnimInstance.h"
#include "UObject/ConstructorHelpers.h" // 경로 탐색
#include "Client/MainMap/MainMapPlayerController.h"
#include "TimerManager.h"
#include "Client/MainMap/MainMapOtherPlayerController.h"
#include "Client/MyCharacter/Widget/MyCharacterUI.h"
#include "Client/MyCharacter/Widget/Inventory/Inventory.h"
#include "Client/MyCharacter/Widget/Party/Party.h"
#include "Client/State/ClientState/ClientCharacterSelectState.h"

//서버 헤더
#include "NetWork/JobInfo.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ClientCharacterSelectState CharacterSelectState;
	ClientCharacterState = new ClientCharacterSelectState();

	bUseControllerRotationYaw = true;

	memset(nick, 0, sizeof(nick));

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

	GetCharacterMovement()->MaxWalkSpeed = 500.0f;

	IsRightClick = false;
	IsAttack = false;

	MaxHP = 100.0f;
	CurrentHP = MaxHP;
	Level = 0;

	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);

	MainMapPlayerController = Cast<AMainMapPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	MyCharacterUI = CreateDefaultSubobject<UMyCharacterUI>(TEXT("MyCharacterUI"));

	Tags.Add(TEXT("Character"));
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	IsClick = false;

	if (MainMapPlayerController)
	{
		GLog->Log(FString::Printf(TEXT("메인맵 플레이어 컨트롤러 존재")));
		MainMapPlayerController->ControlOtherCharacterMove.BindDynamic(this, &AMyCharacter::S2C_ControlOtherCharacterMove);
		MainMapPlayerController->ControlOtherCharacerRotate.BindDynamic(this, &AMyCharacter::S2C_ControlOtherCharacterRotate);
	}

	MyAnimInstance = Cast<UMyAnimInstance>(GetMesh()->GetAnimInstance());
}

void AMyCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	switch (EndPlayReason)
	{
	case EEndPlayReason::RemovedFromWorld:
		if (ClientCharacterState)
		{
			delete ClientCharacterState;
			ClientCharacterState = nullptr;
		}
		break;
	}
}

void AMyCharacter::ClickedReactionMontagePlay()
{

}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (OtherCharacterController)
	{
		FRotator CompleteRotator = FMath::RInterpTo(GetActorRotation(), GoalRotator, DeltaTime, 10.0f);

		SetActorRotation(CompleteRotator);

		if (GetActorLocation().Equals(GoalLocation, 40.0f))
		{
			GLog->Log(FString::Printf(TEXT("목표 위치에 도착")));
			GetWorld()->GetTimerManager().ClearTimer(S2C_MoveTimer);
		}
	}

	ClientCharacterState->Tick(DeltaTime);
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

	PlayerInputComponent->BindAction(TEXT("Alt"), IE_Pressed, this, &AMyCharacter::MouseToggle);

	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AMyCharacter::JumpStart);
	PlayerInputComponent->BindAction(TEXT("Attack"), IE_Pressed, this, &AMyCharacter::LeftClick);

	PlayerInputComponent->BindAction(TEXT("Inventory"), IE_Pressed, this, &AMyCharacter::InventoryToggle);

	PlayerInputComponent->BindAction(TEXT("Party"), IE_Pressed, this, &AMyCharacter::PartyToggle);
}

void AMyCharacter::MoveForward(float Value)
{
	ForwadBackwardCurrentValue = Value;

	if (ForwadBackwardCurrentValue == 1 || ForwadBackwardCurrentValue == -1)
	{
		if (ForwadBackwardPreviousValue == 0)
		{
			bool C2SMoveTimerActive = GetWorld()->GetTimerManager().IsTimerActive(C2S_MoveUpdateTimer);

			if (!C2SMoveTimerActive)
			{
				GetWorld()->GetTimerManager().SetTimer(C2S_MoveUpdateTimer, this, &AMyCharacter::C2S_MoveConfirm, 0.1f, true, 0);
			}
			//GLog->Log(FString::Printf(TEXT("앞 뒤 움직임 시작")));
		}
	}

	if (ForwadBackwardCurrentValue == 0)
	{
		if (ForwadBackwardPreviousValue == 1 || ForwadBackwardPreviousValue == -1)
		{
			bool C2SMoveTimerActive = GetWorld()->GetTimerManager().IsTimerActive(C2S_MoveUpdateTimer);

			if (C2SMoveTimerActive)
			{
				if (LeftRightCurrentValue == 0)
				{
					GetWorld()->GetTimerManager().ClearTimer(C2S_MoveUpdateTimer);
				}
				else
				{
					//GLog->Log(FString::Printf(TEXT("좌우로 움직이는 중임")));
				}
			}
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
			bool C2SMoveTimerActive = GetWorld()->GetTimerManager().IsTimerActive(C2S_MoveUpdateTimer);

			if (!C2SMoveTimerActive)
			{
				GetWorld()->GetTimerManager().SetTimer(C2S_MoveUpdateTimer, this, &AMyCharacter::C2S_MoveConfirm, 0.1f, true, 0);
			}
			//GLog->Log(FString::Printf(TEXT("좌 우 움직임 시작")));
		}
	}

	if (LeftRightCurrentValue == 0)
	{
		if (LeftRightPreviousValue == 1 || LeftRightPreviousValue == -1)
		{
			bool C2SMoveTimerActive = GetWorld()->GetTimerManager().IsTimerActive(C2S_MoveUpdateTimer);

			if (C2SMoveTimerActive)
			{
				if (ForwadBackwardCurrentValue == 0)
				{
					GetWorld()->GetTimerManager().ClearTimer(C2S_MoveUpdateTimer);
				}
				else
				{
					//GLog->Log(FString::Printf(TEXT("앞뒤로 움직이는 중임")));
				}
			}
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
	LookUpCurrentValue = Value;

	if (Value != 0)
	{
		bool C2SRotateTimerActive = GetWorld()->GetTimerManager().IsTimerActive(C2S_RotateUpdateTimer);

		if (!C2SRotateTimerActive)
		{
			GetWorld()->GetTimerManager().SetTimer(C2S_RotateUpdateTimer, this, &AMyCharacter::C2S_RotateConfirm, 0.1f, true, 0);
		}

		AddControllerPitchInput(Value);
	}
	else
	{
		if (TurnCurrentValue == 0)
		{
			GetWorld()->GetTimerManager().ClearTimer(C2S_RotateUpdateTimer);
		}
	}
}

void AMyCharacter::Turn(float Value)
{
	TurnCurrentValue = Value;

	if (Value != 0)
	{
		bool C2SRotateTimerActive = GetWorld()->GetTimerManager().IsTimerActive(C2S_RotateUpdateTimer);

		if (!C2SRotateTimerActive)
		{
			GetWorld()->GetTimerManager().SetTimer(C2S_RotateUpdateTimer, this, &AMyCharacter::C2S_RotateConfirm, 0.1f, true, 0);
		}

		AddControllerYawInput(Value);
	}
	else
	{
		if (LookUpCurrentValue == 0)
		{
			GetWorld()->GetTimerManager().ClearTimer(C2S_RotateUpdateTimer);
		}
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
	IsRightClick = true;
}

void AMyCharacter::RightClickOff()
{
	IsRightClick = false;
}

void AMyCharacter::MouseToggle()
{
	if (MainMapPlayerController)
	{
		if (!MainMapPlayerController->bShowMouseCursor)
		{
			MainMapPlayerController->bShowMouseCursor = true;
			MainMapPlayerController->bEnableClickEvents = true;
			MainMapPlayerController->SetInputMode(FInputModeGameAndUI());
		}
		else
		{
			MainMapPlayerController->bShowMouseCursor = false;
			MainMapPlayerController->bEnableClickEvents = false;
			MainMapPlayerController->SetInputMode(FInputModeGameOnly());
		}
	}
	//bUseControllerRotationYaw = false;
}

void AMyCharacter::JumpStart()
{
	Jump();
}

float AMyCharacter::GetCurrentHP()
{
	return CurrentHP;
}

float AMyCharacter::GetMaxHP()
{
	return MaxHP;
}

void AMyCharacter::LeftClick()
{
	if (MainMapPlayerController)
	{
		if (IsClick)
		{
			ClientCharacterState->Click(MainMapPlayerController);
		}
		else
		{
			GLog->Log(FString::Printf(TEXT("IsClick가 false")));
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

char * AMyCharacter::GetCharacterCode()
{
	return CharacterCode;
}

void AMyCharacter::SetCharacterCode(char * _NewCharacterCode, char* _NewNickName)
{
	memcpy(CharacterCode, _NewCharacterCode, sizeof(CharacterCode));
	memcpy(nick, _NewNickName, sizeof(nick));
}

//클라이언트에서 서버로 위치와 회전값을 보내주는 함수
void AMyCharacter::C2S_MoveConfirm()
{
	FVector Location = GetActorLocation();

	//GLog->Log(FString::Printf(TEXT("C2S_MoveConfirm 함수 호출 0.3s")));

	MainMapPlayerController->C2S_MoveConfirm(Location);
}

//서버에서 받은 위치와 회전값으로 내가 아닌 다른 캐릭터들의 위치 회전값을 업데이트 해주는 함수
void AMyCharacter::S2C_MoveUpdate()
{
	//GLog->Log(FString::Printf(TEXT("GoalLocation X :%f Y : %f Z : %f"),GoalLocation.X,GoalLocation.Y,GoalLocation.Z));

	if (GetActorLocation().Equals(GoalLocation, 20.0f))
	{
		//GLog->Log(FString::Printf(TEXT("목표 위치에 도착")));
		GetWorld()->GetTimerManager().ClearTimer(S2C_MoveTimer);
	}

	AddMovementInput(GoalDirection, 1.0f);
}

//서버에서 받아온 위치와 회전값을 클라이언트에 필요한 내용으로 바꿔주는 함수
void AMyCharacter::S2C_ControlOtherCharacterMove(FVector& _GoalLocation)
{
	GoalLocation = _GoalLocation;

	GoalDirection = GoalLocation - GetActorLocation();

	bool GoalDirectionNormalizeSuccess = GoalDirection.Normalize();

	if (GoalDirectionNormalizeSuccess)
	{
		if (!GetWorld()->GetTimerManager().IsTimerActive(S2C_MoveTimer))
		{
			GetWorld()->GetTimerManager().SetTimer(S2C_MoveTimer, this, &AMyCharacter::S2C_MoveUpdate, 0.01f, true, 0);
		}
	}
}

void AMyCharacter::C2S_RotateConfirm()
{
	FRotator Rotation = GetActorRotation();

	//GLog->Log(FString::Printf(TEXT("C2S_RotateConfirm 함수 호출 0.1s")));

	MainMapPlayerController->C2S_RotationcConfirm(Rotation);
}

//void AMyCharacter::S2C_RotateUpdate()
//{
//	if (GetActorRotation().Equals(GoalRotator,1.0f))
//	{
//		GLog->Log(FString::Printf(TEXT("회전 끝")));
//		GetWorld()->GetTimerManager().ClearTimer(S2C_RotateTimer);
//	}	
//}

void AMyCharacter::S2C_ControlOtherCharacterRotate(FRotator & _GoalRotator)
{
	GoalRotator = _GoalRotator;

	//SetActorRotation(GoalRotator);

	//GLog->Log(FString::Printf(TEXT("서버에서 온 회전 값 저장")));
	/*if (!GetWorld()->GetTimerManager().IsTimerActive(S2C_RotateTimer))
	{
		GetWorld()->GetTimerManager().SetTimer(S2C_RotateTimer, this, &AMyCharacter::S2C_RotateUpdate, 0.01f, true, 0);
	}*/
}

void AMyCharacter::SetOtherCharacterController(AMainMapOtherPlayerController * _OtherCharacterController)
{
	OtherCharacterController = _OtherCharacterController;
}

void AMyCharacter::InventoryToggle()
{
	if (MyCharacterUI)
	{
		MyCharacterUI->GetInventoryComponent()->InventoryWidgetToggle();
	}
}

void AMyCharacter::PartyToggle()
{
	if (MyCharacterUI)
	{
		MyCharacterUI->GetPartyComponent()->PartyWidgetToggle();
	}
}

void AMyCharacter::SetClientCharacterState(ClientState * _NewClientCharacterState)
{
	if (!ClientCharacterState)
	{
		delete ClientCharacterState;
		ClientCharacterState = nullptr;
	}

	ClientCharacterState = _NewClientCharacterState;
}

void AMyCharacter::SetDefaultCharacter()
{
	if (MyCharacterUI)
	{
		MyCharacterUI->SetMyCharacterUI();
		MyCharacterUI->GetPartyComponent()->PartyJoin(this);
	}
}

char * AMyCharacter::GetCharacterNickName()
{
	return nick;
}
