// Fill out your copyright notice in the Description page of Project Settings.

#include "ObjectPool.h"
//클라 헤더
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "Client/Monster/Monster.h"
#include "Client/Monster/StageOne/Bear/Bear.h"
#include "Client/Monster/StageOne/Dinosaur/Dinosaur.h"
#include "Client/Monster/StageTwo/Dog/Dog.h"
#include "Client/Monster/MonsterAIController.h"
#include "Components/BoxComponent.h"
#include "UObject/ConstructorHelpers.h" // 경로 탐색 헤더
#include "Particles/ParticleSystem.h"  //파티클 관련 헤더 파일

//서버 헤더

// Sets default values
AObjectPool::AObjectPool()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// create the Box Component the spawn volume
	DefaultSpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("WhereToSpawn"));

	//Root -> Boxcomponent
	RootComponent = DefaultSpawnArea;

	//Set SpawnNum
	DefaultSpawnArea_Map.Emplace(enumMonsterType::Bear, MonsterArray);
	DefaultSpawnArea_Map.Emplace(enumMonsterType::Dinosaur, MonsterArray);
	DefaultSpawnArea_Map.Emplace(enumMonsterType::Dog, MonsterArray);

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
	FullPoolVolume = initPoolVolume;
	PoolSetting();
}

// Called every frame
void AObjectPool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Origin Spawn Area
	//FVector SpawnOrigin = DefaultSpawnArea->Bounds.Origin;
	//Recive_SpawnObject_Info(3, enumMonsterType::Dog, SpawnOrigin);
	ReadyMonster(enumMonsterType::Bear);
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
		if (FullPoolVolume <= 0)
		{
			throw FullPoolVolume;
		}

		////kind of Monster AND Monster's Maximum size
		Set_MonsterVolume_With_Array(DefaultSpawnArea_Map[enumMonsterType::Bear].Monster_Volum_Array, 5, ABear::StaticClass());
		Set_MonsterVolume_With_Array(DefaultSpawnArea_Map[enumMonsterType::Dinosaur].Monster_Volum_Array, 5, ADinosaur::StaticClass());
		//Set_MonsterVolume_With_Array(DefaultSpawnArea_Map[enumMonsterType::Dog].Monster_Volum_Array, 5, ADog::StaticClass());
		
		/*MonsterType_Enum = enumMonsterType::Bear;
		int temp = 2;*/

		/*Recive_SpawnObject_Info(3, MonsterType_Enum, FVector(4892, 15000, 6451));
		Recive_SpawnObject_Info(temp, enumMonsterType::Dinosaur, FVector(4844, 22780, 6451));*/
	}
	catch (int) {
		if (FullPoolVolume <= 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("ERROR!! : (FullPoolVolume is 'Zero' OR 'Negative Number')"));
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
		if (_counter > FullPoolVolume)
		{
			throw _counter;
		}
		else if (_counter < -1)
		{
			throw _counter;
		}

		// Pooling Enter
		UE_LOG(LogTemp, Warning, TEXT("Pooling Enter"));

	}
	catch (int) {
		if (_counter > FullPoolVolume)
		{
			//Error or FullPoolVolume Use
			UE_LOG(LogTemp, Warning, TEXT("_counter is over PoolVolume"));
		}
		else if (_counter < -1)
		{
			//Error not to use ObjectPool
			UE_LOG(LogTemp, Warning, TEXT("_counter is (-)value"));
		}
	}
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
		//Get Monster's init
		_spawnMonster->init();
		_spawnMonster->GetActorLocation()= SpawnPos_Vector;
		_spawnMonster->bisActive = true;
		SpawnObject_SetActive(_spawnMonster, true);
		return true;
	}
	else
		return false;
}

void AObjectPool::SetStaticMonsterClass()
{

}

void AObjectPool::Recive_SpawnObject_Info(int _MonsterNum, enumMonsterType _MonsterCode, FVector _SpawnGatePosition)
{

	//스폰좌표 3가지
	//4892, 15000, 6451 / 4844, 22780, 6451 / 8584, 18840, 6090

	//SpawnMonster's type Array
	//The Array's Num get

	//SpawnPosition Get
	//Last, Non_Active's Monster Find
	DefaultSpawnArea_Map[(enumMonsterType)_MonsterCode].Monster_Volum_Array[_MonsterNum]->SetActorLocation(_SpawnGatePosition);
	DefaultSpawnArea_Map[(enumMonsterType)_MonsterCode].Monster_Volum_Array[_MonsterNum]->bisActive = true;
	ReadyMonster(_MonsterCode);

}

void AObjectPool::ReadyMonster(enumMonsterType _MonsterCode)
{
	for (int i_Monster = 0; i_Monster < DefaultSpawnArea_Map[(enumMonsterType)_MonsterCode].Monster_Volum_Array.Num(); i_Monster++)
	{
		if (check_RecycleObject(DefaultSpawnArea_Map[(enumMonsterType)_MonsterCode].Monster_Volum_Array[i_Monster]) == true)
		{
			UE_LOG(LogTemp, Warning, TEXT("Monster Recycle"));
		}
		else
			UE_LOG(LogTemp, Warning, TEXT("Monster Recycle Fail"));
	}
}

void AObjectPool::WhereToGate()
{
	//Set Effect to Spawn
}

void AObjectPool::Set_MonsterVolume_With_Array(TArray<class AMonster*>& _MonsterTypeArray, int _MaximumSize, TSubclassOf<class AMonster> _MonsterClass)
{
	//SpawnParameter with CollisionHandling Set
	FActorSpawnParameters SpawnActorOption;
	SpawnActorOption.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

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
			SpawnActor->bisActive = true;

			//SpawnActor's ActiveMode Setting
			SpawnObject_SetActive(SpawnActor, true);

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

