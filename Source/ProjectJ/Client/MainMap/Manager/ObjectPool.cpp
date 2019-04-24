// Fill out your copyright notice in the Description page of Project Settings.

#include "ObjectPool.h"
//클라 헤더
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "NetWork/DataProtocol.h"
#include "Client/Monster/StageOne/Bear/Bear.h"
#include "Client/Monster/StageOne/Dinosaur/Dinosaur.h"
#include "Client/Monster/StageTwo/Dog/Dog.h"
#include "Client/Monster/MonsterAIController.h"
#include "Components/BoxComponent.h"
#include "UObject/ConstructorHelpers.h" // 경로 탐색 헤더
#include "Particles/ParticleSystem.h"  //파티클 관련 헤더 파일

//서버 헤더
#include "NetWork/StorageManager.h"

// Sets default values
AObjectPool::AObjectPool()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// create the Box Component the spawn volume
	DefaultSpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("WhereToSpawn"));

	//Root -> Boxcomponent
	RootComponent = DefaultSpawnArea;

	FMonsterstruct MonsterArray;
	//Set SpawnNum
	DefaultSpawnArea_Map.Emplace(MONSTER_CODE::SPIDER, MonsterArray);
	DefaultSpawnArea_Map.Emplace(MONSTER_CODE::WORM, MonsterArray);
	DefaultSpawnArea_Map.Emplace(MONSTER_CODE::BOSS_SPIDER, MonsterArray);

	////Test to Use this pool check
	//isTestPoolStart = false;

	static ConstructorHelpers::FObjectFinder<UParticleSystem>PT_SpawnEffect(TEXT("ParticleSystem'/Game/Assets/Monster/ParagonMinions/FX/Particles/Minions/Shared/P_MinionSpawn.P_MinionSpawn'"));

	if (PT_SpawnEffect.Succeeded())
	{
		SpawnEffect = PT_SpawnEffect.Object;
	}
}

// Called when the game starts or when spawned
void AObjectPool::BeginPlay()
{
	Super::BeginPlay();


	GLog->Log(FString::Printf(TEXT("AObjectPool BeginPlay")));
	//Set Pool volume to BeginPlay
	PoolSetting();
}

// Called every frame
void AObjectPool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	PacketData* Data;
	if (StorageManager::GetInstance()->GetFront(Data)) //창고매니저 큐에 들어있는 데이터를 가져와서 Data에 담는다.
	{
		switch (Data->protocol) //담아온 Data의 프로토콜을 확인한다.
		{
		case PGAMEDATA_STAGE_MONSTER_TPYES_COUNT: // 스테이지 몬스터 종류가 몇개인지 - (종류 숫자)
			//StorageManager::GetInstance()->ChangeData(SpawnMonster_Num);
			StorageManager::GetInstance()->PopData();
			break;
		case PGAMEDATA_STAGE_MONSTER_INFO: // 스테이지 몬스터 정보 - (몬스터코드,몬스터숫자,좌표)

			int KindMonster;
			int SpawnMonster_Num;
			FVector SpawnPos;

			StorageManager::GetInstance()->ChangeData(Data->data, KindMonster, SpawnMonster_Num, SpawnPos.X, SpawnPos.Y, SpawnPos.Z);
			StorageManager::GetInstance()->PopData();

			Recive_SpawnObject_Info(SpawnMonster_Num, static_cast<MONSTER_CODE>(KindMonster), SpawnPos);
			break;

		}
	}
	//종류 int 갯수
	/*ReadyMonster(enumMonsterType::Bear);*/
}

FVector AObjectPool::GetRandomPointInVolume()
{
	//Origin Spawn Area
	FVector SpawnOrigin = DefaultSpawnArea->Bounds.Origin;
	//Extent Spawn Area
	FVector SpawnExtent = DefaultSpawnArea->Bounds.BoxExtent;

	return UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrigin, SpawnExtent);
}

void AObjectPool::PoolSetting()
{
	//Set To PoolObject
	try
	{
		//throw Error FullPoolVolume
		if (bis_Testpool_Set == true)
		{
			throw bis_Testpool_Set;
		}

		////kind of Monster AND Monster's Maximum size
		Set_MonsterVolume_With_Array(DefaultSpawnArea_Map[MONSTER_CODE::SPIDER].Monster_Volum_Array, MONSTER_CODE::SPIDER, 5, ABear::StaticClass());
		Set_MonsterVolume_With_Array(DefaultSpawnArea_Map[MONSTER_CODE::WORM].Monster_Volum_Array, MONSTER_CODE::WORM, 5, ADinosaur::StaticClass());
		//Set_MonsterVolume_With_Array(DefaultSpawnArea_Map[enumMonsterType::Dog].Monster_Volum_Array, 5, ADog::StaticClass());
	
	}
	catch (bool) {
		if (bis_Testpool_Set == true)
		{
			UE_LOG(LogTemp, Warning, TEXT("Pool DisActive"));
		}
	}
	catch (AMonster*)
	{
		GLog->Log(FString::Printf(TEXT("SpawnActor Error")));
	}
}

void AObjectPool::Pooling(int _counter)
{
	try {

		//throw Error _counter
	/*	if (_counter > FullPoolVolume)
		{
			throw _counter;
		}
		else */if (_counter < -1)
		{
			throw _counter;
		}

		// Pooling Enter
		UE_LOG(LogTemp, Warning, TEXT("Pooling Enter"));

	}
	catch (int) {
		//if (_counter > FullPoolVolume)
		//{
		//	//Error or FullPoolVolume Use
		//	UE_LOG(LogTemp, Warning, TEXT("_counter is over PoolVolume"));
		//}
		//else
		if (_counter < -1)
		{
			//Error not to use ObjectPool
			UE_LOG(LogTemp, Warning, TEXT("_counter is (-)value"));
		}
	}
}

TMap<MONSTER_CODE, FMonsterstruct> AObjectPool::Get_SpawnMoster_Map()
{
	return DefaultSpawnArea_Map;
}

TArray<FActiveMonsterInfo> AObjectPool::Get_ActiveMonster_Array()
{
	return ActiveMonster_Array;
}

void AObjectPool::SpawnObject_SetActive(AMonster* SpawnObject, bool _bActive)
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
		GLog->Log(FString::Printf(TEXT("활성화 선택한 몬스터가 존재하지 않음")));
	}
}

bool AObjectPool::check_RecycleObject(AMonster* _spawnMonster)
{
	if (_spawnMonster->bisActive == false)
	{
		//Make BisActive false -> true
		return true;
	}
	else
		return false;
}

void AObjectPool::SetStaticMonsterClass()
{

}

void AObjectPool::Recive_SpawnObject_Info(int _MonsterNum, MONSTER_CODE _MonsterCode, FVector _SpawnGatePosition)
{

	//스폰좌표 3가지
	//4892, 15000, 6451 / 4844, 22780, 6451 / 8584, 18840, 6090

	//SpawnMonster's type Array
	//The Array's Num get

	//SpawnPosition Get
	//Last, Non_Active's Monster Find
	ReadyMonster(_MonsterCode, _MonsterNum, _SpawnGatePosition);

}

void AObjectPool::ReadyMonster(MONSTER_CODE _MonsterCode, int _MonsterNum, FVector _MonsterPostion)
{
	int Monster_Spawn_Counter=0;
	for (int i_Monster = 0; i_Monster < DefaultSpawnArea_Map[(MONSTER_CODE)_MonsterCode].Monster_Volum_Array.Num(); i_Monster++)
	{
		if (check_RecycleObject(DefaultSpawnArea_Map[(MONSTER_CODE)_MonsterCode].Monster_Volum_Array[i_Monster]) == true && Monster_Spawn_Counter != _MonsterNum)
		{
			UE_LOG(LogTemp, Warning, TEXT("Monster Recycle"));
			++Monster_Spawn_Counter;

			//Active Actor to bisActive make true;
			DefaultSpawnArea_Map[(MONSTER_CODE)_MonsterCode].Monster_Volum_Array[i_Monster]->bisActive = true;
			
			//Get Monster's init
			DefaultSpawnArea_Map[(MONSTER_CODE)_MonsterCode].Monster_Volum_Array[i_Monster]->init();
			DefaultSpawnArea_Map[(MONSTER_CODE)_MonsterCode].Monster_Volum_Array[i_Monster]->SetActorLocation(_MonsterPostion);
			SpawnObject_SetActive(DefaultSpawnArea_Map[(MONSTER_CODE)_MonsterCode].Monster_Volum_Array[i_Monster], true);

			//Temporary Struct to Put in ActvieMonster_Array
			FActiveMonsterInfo TempActiveMonsterInfo;
			TempActiveMonsterInfo.MonsterCode = _MonsterCode;
			TempActiveMonsterInfo.MonsterNum = _MonsterNum;
			TempActiveMonsterInfo.Monster = DefaultSpawnArea_Map[(MONSTER_CODE)_MonsterCode].Monster_Volum_Array[i_Monster];
			
			//ActiveMonster's Array is Send To Server MonsterInfo
			ActiveMonster_Array.Emplace(TempActiveMonsterInfo);
			
		}
		else if (Monster_Spawn_Counter == _MonsterNum)
		{
			break;
		}
		else
			UE_LOG(LogTemp, Warning, TEXT("Monster Recycle Fail"));
	}
}

void AObjectPool::WhereToGate()
{
	//Set Effect to Spawn
}

void AObjectPool::Set_MonsterVolume_With_Array(TArray<class AMonster*>& _MonsterTypeArray, MONSTER_CODE _MonsterCode, int _MaximumSize, TSubclassOf<class AMonster> _MonsterClass)
{
	//SpawnParameter with CollisionHandling Set
	FActorSpawnParameters SpawnActorOption;

	//Use SpawnActorOption, ESpawnActorCollisionHandlingMethod::[ AlwaysSpawn OR AdjustIfPossibleButAlwaysSpawn ]
	SpawnActorOption.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	//Default SpawnVector Pos
	SpawnPos_Vector = DefaultSpawnArea->Bounds.Origin;

	for (int i_spawnObject = 0; i_spawnObject < _MaximumSize; i_spawnObject++)
	{
		//Create Actor
		AMonster* SpawnActor = nullptr;

		//SpawnActorFuntion 
		SpawnActor = GetWorld()->SpawnActor<AMonster>(_MonsterClass, SpawnPos_Vector, FRotator::ZeroRotator, SpawnActorOption);
		
		//Is SpawnActor null or nomal
		if (SpawnActor)
		{
			UE_LOG(LogTemp, Warning, TEXT("SpawnActor Create"));
			//Pawn->Auto Possess AI
			//SpawnActor->AutoPossessAI = EAutoPossessAI::Spawned;

			////isActive Check bool Attribute make false
			SpawnActor->bisActive = false;

			SpawnActor->SetMonsterCode(_MonsterCode);
			SpawnActor->SetMonsterNum(i_spawnObject);

			//SpawnActor's ActiveMode Setting False
			SpawnObject_SetActive(SpawnActor, false);

			//input Array to SpawnActor
			_MonsterTypeArray.Add(SpawnActor);
		}
		else if (SpawnActor == nullptr)
		{
			//GLog->Log(FString::Printf(TEXT("SpawnActor Error")));
			UE_LOG(LogTemp, Warning, TEXT("SpawnActor Error"));
		}
	}
}

