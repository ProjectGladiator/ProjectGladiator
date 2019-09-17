// Fill out your copyright notice in the Description page of Project Settings.

#include "Monster.h"
//클라 헤더
#include "MonsterAIController.h"
#include "Client/State/MonsterState/MonsterState.h"
#include "Client/MainMap/Manager/ObjectPool.h"
#include "Client/Monster/Manager/AIManager.h"
#include "Components/SkeletalMeshComponent.h" //스켈레탈 메쉬 헤더
#include "GameFrameWork/CharacterMovementComponent.h" //캐릭터 속도 관련 헤더
#include "UObject/ConstructorHelpers.h" // 경로 탐색 헤더
#include "Particles/ParticleSystem.h"  //파티클 관련 헤더 파일
#include "Kismet/GameplayStatics.h"
#include "Client/MyCharacter/PC/MyCharacter.h"
#include "Client/MyCharacter/PC/Widget/MyCharacterUI.h"
#include "Client/MyCharacter/PC/Widget/MainWidget.h"
#include "Client/MyCharacter/PC/Widget/Party/Widget/PartyWidget.h"

//서버 헤더
#include "NetWork/StorageManager.h"

// Sets default values
AMonster::AMonster()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	AIControllerClass = AMonsterAIController::StaticClass();

	AIManager = CreateDefaultSubobject<UAIManager>(TEXT("AIManager"));

	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);

	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true; //몬스터가 가속하는 방향으로 회전 시킨다.
	GetCharacterMovement()->bUseRVOAvoidance = true;

	AutoPossessAI = EAutoPossessAI::Spawned;

	Tags.Add(TEXT("Monster"));

	static ConstructorHelpers::FObjectFinder<UParticleSystem>PT_SpawnEffect(TEXT("ParticleSystem'/Game/Assets/Monster/ParagonMinions/FX/Particles/Minions/Shared/P_MinionSpawn.P_MinionSpawn'"));

	if (PT_SpawnEffect.Succeeded())
	{
		SpawnEffect = PT_SpawnEffect.Object;
	}

	m_MonsterAttackCode = MONSTER_ATTACK_CODE::DEFAULT_ATTACK_CODE;

	//활성화 확인용 bool은 처음엔 true로 설정 
	bisActive = true;
}

void AMonster::AttackHit()
{

}

void AMonster::OnMonsterAttackEnded()
{
	GLog->Log(FString::Printf(TEXT("IsAttack 초기화")));
	IsAttack = false; //false로 초기화
	IsCombo = false;
	CurrentCombo = 0; //콤보수 0으로 초기화
}

void AMonster::OnComboSave()
{

}

void AMonster::OnMonsterAttackChanged()
{

}

void AMonster::Death()
{
	//사망표식
	DeathFlag = true;
	CurrentHP = 0;
}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();

	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel3);
}

// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	//PGAMEDATA_MONSTER_ATTACK_SUCCESS,				// 몬스터 공격받음(공격성공 살아있음) - ([int] 몬스터코드, [int] 몬스터번호, [int] 입힌데미지)
	
	//	PGAMEDATA_MONSTER_ATTACK_FAIL,					// 몬스터 공격받음(공격실패) - (프로토콜만)
	//	PGAMEDATA_MONSTER_ATTACK_DIE,					// 몬스터 공격받음(죽어버림) - ([int] 몬스터코드, [int] 몬스터번호, [int] 입힌데미지)

	FVector UpdateLocation = FMath::VInterpTo(GetActorLocation(), CurrentLocation, DeltaTime, 1.0f);

	/*GLog->Log(FString::Printf(TEXT("AMonster Tick GetActorLocation X : %f Y : %f Z : %f\n"), GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z));
	GLog->Log(FString::Printf(TEXT("AMonster Tick ServerLocation   X : %f Y : %f Z : %f\n"), CurrentLocation.X, CurrentLocation.Y, CurrentLocation.Z));
	GLog->Log(FString::Printf(TEXT("AMonster Tick UpdateLocation   X : %f Y : %f Z : %f\n"), UpdateLocation.X, UpdateLocation.Y, UpdateLocation.Z));*/

	SetActorLocation(UpdateLocation);
}

// Called to bind functionality to input
void AMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMonster::Init(MONSTER_CODE _MyMonsterCode, int _MyMonsterNum)
{
	//Init For Monster's type
	//MaxHP = 100.0f;
	//CurrentHP = MaxHP;

	//init Code & Num
	m_MonsterCode = _MyMonsterCode;
	m_MonsterNum = _MyMonsterNum;

	if (SpawnEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SpawnEffect, GetActorLocation(), FRotator::ZeroRotator, true);
	}
	//bisActive = false;
}

//void AMonster::Firstinit(MONSTER_CODE _MyMonsterCode, int _MyMonsterNum)
//{
//	//init Code & Num
//	m_MonsterCode = _MyMonsterCode;
//	m_MonsterNum = _MyMonsterNum;
//	//init();
//}

float AMonster::GetHP()
{
	return CurrentHP;
}

void AMonster::SetHP(float _currentHP)
{
	CurrentHP = _currentHP;
}

MONSTER_CODE AMonster::SetMonsterCode(MONSTER_CODE _MonsterCode)
{
	return m_MonsterCode = _MonsterCode;
}

int AMonster::SetMonsterNum(int _MonsterNum)
{
	return m_MonsterNum = _MonsterNum;
}

void AMonster::Monster_SetActive(AMonster * SpawnObject, bool _bActive)
{
	if (SpawnObject)
	{
		if (_bActive == true)
		{
			SpawnObject->SetActorHiddenInGame(false);
			SpawnObject->SetActorEnableCollision(true);
			SpawnObject->SetActorTickEnabled(true);
		}
		else
		{
			// Hides visible components
			SpawnObject->SetActorHiddenInGame(true);
			// Disables collision components
			SpawnObject->SetActorEnableCollision(true);
			// Stops the Actor from ticking
			SpawnObject->SetActorTickEnabled(false);
		}
	}
	else
	{
		//GLog->Log(FString::Printf(TEXT("Monster Cannot Active")));
		UE_LOG(LogTemp, Error, TEXT("Monster Cannot Active \nSpawnActor is Gone"));
	}

}

void AMonster::FirstTarget()
{
	auto MyCharacter = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (MyCharacter)
	{
		for (int i = 0; i < MyCharacter->GetMyCharacterUI()->GetMainWidget()->GetPartySize(); i++)
		{
			FPartySlot PartySlot = MyCharacter->GetMyCharacterUI()->GetMainWidget()->GetPartySlot(i);
			
			if (PartySlot.PartyUser)
			{
				if (PartySlot.PartyUser->GetPartyLeader())
				{
					Target = PartySlot.PartyUser;
				}
			}
		}
	}
}

void AMonster::Targeting(char* _CharacterCode)
{
	auto MyCharacter = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (MyCharacter)
	{
		for (int i = 0; i < MyCharacter->GetMyCharacterUI()->GetMainWidget()->GetPartySize(); i++)
		{
			FPartySlot PartySlot = MyCharacter->GetMyCharacterUI()->GetMainWidget()->GetPartySlot(i);

			if (PartySlot.PartyUser)
			{
				
				if (strcmp(_CharacterCode, PartySlot.PartyUser->GetCharacterCode())==0)
				{
					Target = PartySlot.PartyUser;
				}
			}
		}
	}
}

void AMonster::S2C_LocationUpdate(const FVector& _NewLocation)
{
	CurrentLocation = _NewLocation;
}

MONSTER_ATTACK_CODE AMonster::GetMonsterAttackCode()
{
	return m_MonsterAttackCode;
}

MONSTER_CODE AMonster::GetMonsterCode()
{
	return m_MonsterCode;
}

int AMonster::GetMonsterNum()
{
	return m_MonsterNum;
}