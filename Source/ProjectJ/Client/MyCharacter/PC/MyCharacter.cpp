// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacter.h"
//클라 헤더
#include "GameFramework/SpringArmComponent.h" //스프링암 컴포넌트 헤더파일
#include "Camera/CameraComponent.h" //카메라 컴포넌트 헤더파일
#include "GameFramework/CharacterMovementComponent.h" //캐릭터 속력 관련 헤더파일
#include "Animation/AnimBlueprint.h" //애니메이션블루프린트 헤더파일
#include "Engine/World.h"
#include "kismet/GameplayStatics.h" //각종 유틸 관련 헤더
#include "kismet/KismetMathLibrary.h" //수학 관련 헤더
#include "Warrior/Warrior.h" // 전사 헤더
#include "Tanker/Tanker.h" //탱커 헤더
#include "Gunner/Gunner.h" //총잡이 헤더
#include "MyAnimInstance.h" //애님인스턴스 헤더
#include "UObject/ConstructorHelpers.h" // 경로 탐색
#include "TimerManager.h" //타이머 헤더
#include "client/MainMap/MainMapGameMode.h" //메인맵 게임모드 헤더
#include "Client/MainMap/MainMapPlayerController.h" //메인맵 플레이어 컨트롤러 헤더
#include "Client/MainMap/MainMapOtherPlayerController.h" //메인맵 다른 유저 플레이어 컨트롤러 헤더
#include "Client/MyCharacter/PC/Widget/MyCharacterUI.h" //내캐릭터 UI헤더
#include "Client/MyCharacter/PC/Widget/Party/Party.h" //파티 헤더
#include "Client/MyCharacter/PC/Widget/CharacterInteraction/ClickCharacterInteraction.h"//클릭 상호작용 헤더
#include "Client/MyCharacter/PC/Widget/Info/MyCharacterWidget.h" //내캐릭터 정보 위젯 헤더
#include "Client/MyCharacter/PC/Widget/MainWidget.h" //메인 위젯 헤더
#include "Client/State/ClientState/ClientState.h" //클라 상태 클래스 헤더
#include "Components/WidgetComponent.h"
#include "Client/MyCharacter/PC/Widget/Info/MyCharacterNickNameWidget.h"
#include "Client/MyCharacter/PC/Widget/MainWidget.h"
#include "Client/Menu/MenuWidget.h"
#include "Client/MyCharacter/PC/Widget/Chatting/ChattingWidget.h"
#include "Particles/ParticleSystem.h"  //파티클 관련 헤더 파일
#include "Client/MainMap/Manager/StageManager.h"
//#include "Client/State/ClientState/Character/ClientCharacterInGameState.h"

//서버 헤더
#include "NetWork/JobInfo.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
	SpringArm->bDoCollisionTest = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	CharacterNickWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("CharacterNickWidget"));
	CharacterNickWidget->SetupAttachment(RootComponent);
	CharacterNickWidget->SetWidgetSpace(EWidgetSpace::Screen);
	CharacterNickWidget->SetRelativeLocation(FVector(0, 0, 120.0f));

	GetCharacterMovement()->MaxWalkSpeed = 500.0f;

	IsRightClick = false;
	IsAttack = false;
	IsClick = false;

	MaxHP = 100.0f;
	CurrentHP = MaxHP;
	MaxMP = 100.0f;
	CurrentMP = MaxHP;

	Level = 0;

	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);

	OtherCharacterController = nullptr;

	MyCharacterUI = CreateDefaultSubobject<UMyCharacterUI>(TEXT("MyCharacterUI"));

	IsPartyLeader = false;

	static ConstructorHelpers::FObjectFinder<UParticleSystem>PT_GameStageStartEffect(TEXT("ParticleSystem'/Game/Assets/Paragon/ParagonProps/FX/Particles/Core/P_Core_CharacterRecall.P_Core_CharacterRecall'"));

	if (PT_GameStageStartEffect.Succeeded())
	{
		GameStageStartEffect = PT_GameStageStartEffect.Object;
	}

	Tags.Add(TEXT("Character"));
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	MyAnimInstance = Cast<UMyAnimInstance>(GetMesh()->GetAnimInstance());
	MainMapPlayerController = Cast<AMainMapPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

void AMyCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	//ClientCharacterState->EndPlay(EndPlayReason);

	if (ClientCharacterState)
	{
		delete ClientCharacterState;
		ClientCharacterState = nullptr;
	}
}

void AMyCharacter::ClickedReactionMontagePlay()
{

}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	if (MainMapPlayerController)
	{
		if (ClientCharacterState)
		{
			ClientCharacterState->Tick(DeltaTime);
		}
	}

	Super::Tick(DeltaTime);

	if (OtherCharacterController)
	{
		FRotator CompleteRotator = FMath::RInterpTo(GetActorRotation(), GoalRotator, DeltaTime, 10.0f);

		SetActorRotation(CompleteRotator);

		if (GetActorLocation().Equals(GoalLocation, 40.0f))
		{
			//GLog->Log(FString::Printf(TEXT("목표 위치에 도착")));
			if (GetWorld()->GetTimerManager().IsTimerActive(S2C_MoveTimer))
			{
				GetWorld()->GetTimerManager().ClearTimer(S2C_MoveTimer);
			}
		}
	}

	
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

	PlayerInputComponent->BindAction(TEXT("Menu"), IE_Pressed, this, &AMyCharacter::MenuToggle);

	PlayerInputComponent->BindAction(TEXT("ChattingInput"), IE_Pressed, this, &AMyCharacter::ChattingInputStart);
}

void AMyCharacter::MoveForward(float Value)
{
	if (ClientCharacterState)
	{
		ClientCharacterState->MoveForward(Value);
	}
}

void AMyCharacter::MoveRight(float Value)
{
	if (ClientCharacterState)
	{
		ClientCharacterState->MoveRight(Value);
	}
}

bool AMyCharacter::MoveTimerActive()
{
	bool MoveTimerActive = GetWorld()->GetTimerManager().IsTimerActive(C2S_MoveUpdateTimer);

	return MoveTimerActive;
}

void AMyCharacter::MoveImplementation()
{
	bool C2SMoveTimerActive = MoveTimerActive();

	if (!C2SMoveTimerActive)
	{
		GetWorld()->GetTimerManager().SetTimer(C2S_MoveUpdateTimer, this, &AMyCharacter::C2S_MoveConfirm, 0.1f, true, 0);
	}
}

void AMyCharacter::MoveUpdateTimerKill()
{
	//GLog->Log(FString::Printf(TEXT("C2S_MoveConfirm 킬")));
	GetWorld()->GetTimerManager().ClearTimer(C2S_MoveUpdateTimer);
}

void AMyCharacter::LookUp(float Value)
{
	if (ClientCharacterState)
	{
		ClientCharacterState->LookUp(Value);
	}
}

void AMyCharacter::Turn(float Value)
{
	if (ClientCharacterState)
	{
		ClientCharacterState->Turn(Value);
	}
}

bool AMyCharacter::RotateTimerActive()
{
	bool RotateTimerActive = GetWorld()->GetTimerManager().IsTimerActive(C2S_RotateUpdateTimer);

	return RotateTimerActive;
}

void AMyCharacter::RotateImplementation()
{
	bool C2SMoveTimerActive = RotateTimerActive();

	if (!C2SMoveTimerActive)
	{
		GetWorld()->GetTimerManager().SetTimer(C2S_RotateUpdateTimer, this, &AMyCharacter::C2S_RotateConfirm, 0.1f, true, 0);
	}
}

void AMyCharacter::RotateUpdateTimerKill()
{
	//GLog->Log(FString::Printf(TEXT("C2S_RotateConfirm 킬")));
	GetWorld()->GetTimerManager().ClearTimer(C2S_RotateUpdateTimer);
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

float AMyCharacter::GetCurrentMP()
{
	return CurrentMP;
}

float AMyCharacter::GetMaxMP()
{
	return MaxMP;
}

void AMyCharacter::LeftClick()
{
	if (MainMapPlayerController)
	{
		if (IsClick)
		{

			if (ClientCharacterState)
			{
				ClientCharacterState->Click(MainMapPlayerController);
			}
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

	//GLog->Log(FString::Printf(TEXT("C2S_MoveConfirm 함수 호출 0.1s")));

	MainMapPlayerController->C2S_MoveConfirm(Location);
}

//서버에서 받은 위치와 회전값으로 내가 아닌 다른 캐릭터들의 위치 회전값을 업데이트 해주는 함수
void AMyCharacter::S2C_MoveUpdate()
{
	//GLog->Log(FString::Printf(TEXT("GoalLocation X :%f Y : %f Z : %f"),GoalLocation.X,GoalLocation.Y,GoalLocation.Z));

	//float GoalDistance = FVector::Distance(GetActorLocation(), GoalLocation);

	//GLog->Log(FString::Printf(TEXT("%d"), GoalDistance));

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
		MyCharacterUI->GetMainWidget()->InventoryWidgetToggle();
	}
}

void AMyCharacter::PartyToggle()
{
	/*if (MyCharacterUI)
	{
		MyCharacterUI->GetPartyComponent()->PartyWidgetVisible();
	}*/
}

void AMyCharacter::MenuToggle()
{
	if (MyCharacterUI)
	{
		MyCharacterUI->GetMainWidget()->MenuWidgetToggle();
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

void AMyCharacter::SetDefaultMyCharacter()
{
	if (MyCharacterUI)
	{
		auto MyCharacterController = Cast<AMainMapPlayerController>(GetController());

		if (MyCharacterController)
		{
			MyCharacterUI->GetMainWidget()->InventoryCreate(20);
			MyCharacterUI->GetMyCharacterInteraction()->GetMyCharacterWidget()->SetInit(this, MyCharacterController);
			MyCharacterUI->GetMyCharacterInteraction()->MyCharacterWidgetVisible();
			MyCharacterUI->GetMyCharacterInteraction()->SetMyCharacterNickNameWidget(CharacterNickWidget, nick);
			MyCharacterUI->GetMainWidget()->GetMenuWidget()->MenuInit(this);
			MyCharacterUI->MainWidgetVisible();
		}
		else
		{
			GLog->Log(FString::Printf(TEXT("SetDefaultMyCharacter함수 MyCharacterController이 존재 하지 않음")));
		}
	}
}

void AMyCharacter::SetDefaultOtherCharacter()
{
	if (MyCharacterUI)
	{
		if (OtherCharacterController)
		{
			MyCharacterUI->GetMyCharacterInteraction()->GetMyCharacterWidget()->SetInit(this, OtherCharacterController);
			MyCharacterUI->GetMyCharacterInteraction()->SetMyCharacterNickNameWidget(CharacterNickWidget, nick);
		}
		else
		{
			GLog->Log(FString::Printf(TEXT("SetDefaultOtherCharacter함수 OtherCharacterController이 존재 하지 않음")));
		}
	}
}

char * AMyCharacter::GetCharacterNickName()
{
	return nick;
}

AMainMapOtherPlayerController * AMyCharacter::GetOtherPlayerController()
{
	return OtherCharacterController;
}

UMyCharacterUI * AMyCharacter::GetMyCharacterUI()
{
	if (MyCharacterUI)
	{
		return MyCharacterUI;
	}
	else
	{
		return nullptr;
	}
}

void AMyCharacter::SetClickCharacter(AMyCharacter* _ClickCharacter)
{
	if (_ClickCharacter)
	{
		ClickCharacter = _ClickCharacter;
	}
	else
	{
		ClickCharacter = nullptr;
	}
}

AMyCharacter * AMyCharacter::GetClickCharacter()
{
	if (ClickCharacter)
	{
		return ClickCharacter;
	}
	else
	{
		return nullptr;
	}
}

bool AMyCharacter::GetPartyLeader()
{
	return IsPartyLeader;
}

void AMyCharacter::SetPartyLeader(bool _IsPartyLeader)
{
	IsPartyLeader = _IsPartyLeader;
}

void AMyCharacter::ChattingInputStart()
{
	if (MainMapPlayerController)
	{
		MainMapPlayerController->SetInputMode(FInputModeUIOnly());
		MyCharacterUI->GetMainWidget()->ChattingStart();
	}
}

int32 AMyCharacter::GetMoney()
{
	return Money;
}

void AMyCharacter::GetMoney(int32 _GetMoney)
{
	Money += _GetMoney;

	if (MyCharacterUI)
	{
		MyCharacterUI->GetMainWidget()->MoneyUpdate(Money);
	}
}

void AMyCharacter::LoseMoney(int32 _LoseMoney)
{
	Money -= _LoseMoney;

	if (MyCharacterUI)
	{
		MyCharacterUI->GetMainWidget()->MoneyUpdate(Money);
	}
}

bool AMyCharacter::IsBuyItem(int32 _LoseMoney)
{
	int32 SubMoney = Money - _LoseMoney;

	if (SubMoney > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void AMyCharacter::AllUIHidden()
{
	MyCharacterNickWidgetHidden();

	MyCharacterUI->AllUIHidden();
}

void AMyCharacter::AllUIVisible()
{
	MyCharacterNickWidgetVisible();

	MyCharacterUI->AllUIVisible();
}

void AMyCharacter::AllUIDestroy()
{
	CharacterNickWidget->SetWidgetClass(nullptr);

	MyCharacterUI->AllUIDestroy();
}

void AMyCharacter::MyCharacterNickWidgetHidden()
{
	CharacterNickWidget->SetVisibility(false);
}

void AMyCharacter::MyCharacterNickWidgetVisible()
{
	CharacterNickWidget->SetVisibility(true);
}

void AMyCharacter::SpawnGameStageStartEffect()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), GameStageStartEffect, GetActorLocation(), FRotator::ZeroRotator, true);
}

void AMyCharacter::MonsterInfoAssemble()
{
	auto MainMapGameMode = Cast<AMainMapGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	if (MainMapGameMode)
	{
		TArray<FActiveMonsterInfo> MonsterInfos = MainMapGameMode->GetStageManager()->GetObjectPool()->Get_ActiveMonster_Array();

		if (MainMapPlayerController)
		{
			for (int i = 0; i < MonsterInfos.Num(); i++)
			{
				if (MonsterInfos[i].Monster)
				{
					MainMapPlayerController->C2S_ReqMonsterInfo(MonsterInfos[i].MonsterCode, MonsterInfos[i].MonsterNum, MonsterInfos[i].Monster->GetActorLocation());
				}
			}
		}
	}
}
