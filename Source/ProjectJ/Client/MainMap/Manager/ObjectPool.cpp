// Fill out your copyright notice in the Description page of Project Settings.

#include "ObjectPool.h"

#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "Client/Monster/Monster.h"
#include "Client/Monster/StageOne/Bear/Bear.h"
#include "Client/Monster/StageOne/Dinosaur/Dinosaur.h"
#include "Client/Monster/MonsterAIController.h"
#include "Components/BoxComponent.h"


// Sets default values
AObjectPool::AObjectPool()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// create the Box Component the spawn volume
	whereToSpawn = CreateDefaultSubobject<UBoxComponent>(TEXT("WhereToSpawn"));

	//Root -> Boxcomponent
	RootComponent = whereToSpawn;

	//Set SpawnNum
	SetStaticMonsterClass();

	//Test to Use this pool check
	isTestPoolStart = false;

	//Current pool init is 0
	/*currentPool_count = 0;*/
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
	FVector SpawnOrigin = whereToSpawn->Bounds.Origin;
	//Extent Spawn Area
	FVector SpawnExtent = whereToSpawn->Bounds.BoxExtent;

	return UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrigin, SpawnExtent);
}

void AObjectPool::PoolSetting()
{
	try
	{
		//throw Error FullPoolVolume
		if (FullPoolVolume <= 0)
		{
			throw FullPoolVolume;
		}

		////Object Position
		//FVector SpawnPos_Vector;

		//SpawnParameter with CollisionHandling Set
		FActorSpawnParameters SpawnActorOption;
		SpawnActorOption.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		//Test with object Spawn bool
		if (isTestPoolStart == true)
		{
			SpawnPos_Vector = whereToSpawn->Bounds.Origin;
		}
		else if (isTestPoolStart == false)
		{
			SpawnPos_Vector = FVector::ZeroVector;
		}

		//Set To PoolObject
		for (int i_spawnObject = 0; i_spawnObject < FullPoolVolume; i_spawnObject++)
		{
			AMonster* SpawnActor = nullptr;

			if (i_spawnObject % 2 == 0)
			{
				SpawnActor = GetWorld()->SpawnActor<AMonster>(whatToSpawn_Array[0], SpawnPos_Vector, FRotator::ZeroRotator, SpawnActorOption);
			}
			else
			{
				SpawnActor = GetWorld()->SpawnActor<AMonster>(whatToSpawn_Array[1], SpawnPos_Vector, FRotator::ZeroRotator, SpawnActorOption);
			}

			if (SpawnActor)
			{
				UE_LOG(LogTemp, Warning, TEXT("SpawnActor Create"));
				//Pawn->Auto Possess AI
				//SpawnActor->AutoPossessAI = EAutoPossessAI::Spawned;
				Spawn_Array.Emplace(SpawnActor);
				SpawnObject_SetActive(Spawn_Array[i_spawnObject], false);
				Spawn_Array[i_spawnObject]->bisActive = false;
			}
			else if(SpawnActor == nullptr)
			{
				//GLog->Log(FString::Printf(TEXT("SpawnActor Error")));
				throw SpawnActor;
			}
		}
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
			SpawnObject->SetActorEnableCollision(false);
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
	UClass* bear = ABear::StaticClass();
	UClass* Dinosaur = ADinosaur::StaticClass();

	whatToSpawn_Array.Add(Dinosaur);
	whatToSpawn_Array.Add(bear);
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
	int Non_ActiveMonster = 0;
	for (int i_Monster = 0; i_Monster < Spawn_Array.Num(); i_Monster++)
	{
		if (Spawn_Array[i_Monster]->bisActive == false)
		{
			//This Set Non-Active Monster's info
			Non_ActiveMonster++;
		}
	}
}

void AObjectPool::WhereToGate()
{
}

