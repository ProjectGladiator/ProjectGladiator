// Fill out your copyright notice in the Description page of Project Settings.

#include "ObjectPool.h"

#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "Client/Monster/Monster.h"
#include "Client/Monster/StageOne/Bear/Bear.h"
#include "Client/Monster/StageOne/Dinosaur/Dinosaur.h"
#include "Client/Monster/StageTwo/Dog/Dog.h"
#include "Client/Monster/MonsterAIController.h"
#include "Components/BoxComponent.h"


// Sets default values
AObjectPool::AObjectPool()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

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

		/*UClass* Static_bear = ABear::StaticClass();
		UClass* Static_Dinosaur = ADinosaur::StaticClass();
		UClass* Static_Dog = ADog::StaticClass();*/

		////kind of Monster
		Set_MonsterVolume_With_Array(DefaultSpawnArea_Map[enumMonsterType::Bear].Monster_Volum_Array, 15, ABear::StaticClass());
		Set_MonsterVolume_With_Array(DefaultSpawnArea_Map[enumMonsterType::Dinosaur].Monster_Volum_Array, 10, ADinosaur::StaticClass());
		Set_MonsterVolume_With_Array(DefaultSpawnArea_Map[enumMonsterType::Dog].Monster_Volum_Array, 5, ADog::StaticClass());
		//
		//Monster's Maximum size
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

void AObjectPool::RecycleObject(AMonster* _spawnMonster)
{
	//Get Monster's init
	_spawnMonster->init();
	_spawnMonster->GetActorLocation()= SpawnPos_Vector;
	SpawnObject_SetActive(_spawnMonster, false);
}

void AObjectPool::SetStaticMonsterClass()
{
	/*UClass* Static_bear = ABear::StaticClass();
	UClass* Static_Dinosaur = ADinosaur::StaticClass();
	UClass* Static_Dog = ADog::StaticClass();


	DefaultSpawnArea_Map.Emplace((enumMonsterType)Bear, MonsterArray);
	DefaultSpawnArea_Map.Emplace((enumMonsterType)Dinosaur, MonsterArray);
	DefaultSpawnArea_Map.Emplace((enumMonsterType)Dog, MonsterArray);*/

	//bool bisTypeIn
	//DefaultSpawnArea_Array[0].Monster_Volum_Array

	/*DefaultSpawnArea_Array.Add(bear, MonsterArray);
	DefaultSpawnArea_Array.Add(Dinosaur, MonsterArray);
	DefaultSpawnArea_Array.Add(Dog, MonsterArray);*/

}

void AObjectPool::Recive_SpawnObject_Info(int _MonsterNum[], int _MonsterCode[], FVector _SpawnGatePosition[])
{
	//SpawnMonster's type Array
	//The Array's Num get
	//SpawnPosition Get
	//Last, Non_Active's Monster Find
	//N-A_M's Recycle 
}

void AObjectPool::check_ReadyMonster()
{
	//int Non_ActiveMonster = 0;
	//for (int i_Monster = 0; i_Monster < Spawn_Array.Num(); i_Monster++)
	//{
	//	if (Spawn_Array[i_Monster]->bisActive == false)
	//	{
	//		//This Set Non-Active Monster's info
	//		Non_ActiveMonster++;
	//	}
	//}
}

void AObjectPool::WhereToGate()
{
	//Set Effect to Spawn
}

void AObjectPool::Set_MonsterVolume_With_Array(TArray<TSubclassOf<class AMonster>> _MonsterTypeArray, int _MaximumSize, TSubclassOf<class AMonster> _MonsterClass)
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
		/*UClass* Static_bear = ABear::StaticClass();
		UClass* Static_Dinosaur = ADinosaur::StaticClass();
		UClass* Static_Dog = ADog::StaticClass();*/
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
			//_MonsterTypeArray[i_spawnObject]->bisActive = false;

			//SpawnActor's ActiveMode Setting
			SpawnObject_SetActive(SpawnActor, false);

			//input Array to SpawnActor
			_MonsterTypeArray.Add(SpawnActor->StaticClass());
			
		}
		else if (SpawnActor == nullptr)
		{
			//GLog->Log(FString::Printf(TEXT("SpawnActor Error")));
			UE_LOG(LogTemp, Warning, TEXT("SpawnActor Error"));
		}
	}
}

