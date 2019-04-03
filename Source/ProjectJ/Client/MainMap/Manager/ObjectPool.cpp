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
	//FullPoolVolume = initPoolVolume;

	//Test to Use this pool check
	isTestPoolStart = false;

	//Set Spawn Monster
	SetStaticMonsterClass();

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
	ABear* Bear;
	ADinosaur* Dinosaur;
	//Get World
	UWorld* const world = GetWorld();

	FVector SpawnPos_Vector;
	
	//	//Set ths Spawn Paramaters
	//FActorSpawnParameters SpawnParams;
	//SpawnParams.Owner = this;
	//SpawnParams.Instigator = Instigator;

	if (isTestPoolStart == true)
	{
		SpawnPos_Vector = whereToSpawn->Bounds.Origin;
	}
	else if (isTestPoolStart == false)
	{
		SpawnPos_Vector = FVector::ZeroVector;
	}

	
	for (int i_spawnObject = 0; i_spawnObject < FullPoolVolume; i_spawnObject++)
	{
		AMonster* SpawnActor=nullptr;
		if (i_spawnObject % 2 == 0)
		{
			//어떤 Monster를 사용할 건지 정하는 부분을 만들어야함
			SpawnActor = GetWorld()->SpawnActor<ABear>(Bear->StaticClass(), SpawnPos_Vector, FRotator::ZeroRotator);
			
			if (SpawnActor)
			{
				GLog->Log(FString::Printf(TEXT("스폰 액터 있음")));

				//Pawn->Auto Possess AI
				//SpawnActor->AutoPossessAI = EAutoPossessAI::Spawned;
				Spawn_Array.Emplace(SpawnActor);
				UE_LOG(LogTemp, Warning, TEXT("SpawnActor Create"));

				SpawnObject_SetActive(Spawn_Array[i_spawnObject], true);
				//Spawn_Array[i_spawnObject]->bisActive = false;
			}
			else
			{
				GLog->Log(FString::Printf(TEXT("스폰 액터 NULL")));
			}
		}
		else
		{
			//어떤 Monster를 사용할 건지 정하는 부분을 만들어야함
			SpawnActor = GetWorld()->SpawnActor<ADinosaur>(Dinosaur->StaticClass(), SpawnPos_Vector, FRotator::ZeroRotator);

			if (SpawnActor)
			{
				GLog->Log(FString::Printf(TEXT("스폰 액터 있음")));

				//Pawn->Auto Possess AI
				//SpawnActor->AutoPossessAI = EAutoPossessAI::Spawned;
				Spawn_Array.Emplace(SpawnActor);
				UE_LOG(LogTemp, Warning, TEXT("SpawnActor Create"));

				SpawnObject_SetActive(Spawn_Array[i_spawnObject], true);
				//Spawn_Array[i_spawnObject]->bisActive = false;
			}
			else
			{
				GLog->Log(FString::Printf(TEXT("스폰 액터 NULL")));
			}
		}
	}
}

void AObjectPool::Pooling(int _counter)
{
	// 요기에는 Pooling을 할 내용을 적어주면됩미다.
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
	else
	{
		// Pooling Enter
		UE_LOG(LogTemp, Warning, TEXT("Pooling Enter"));
	}
}

void AObjectPool::SpawnObject_SetActive(AMonster* SpawnObject, bool _bActive)
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

void AObjectPool::ResetObject()
{
}

void AObjectPool::SetStaticMonsterClass()
{
	UClass* bear = ABear::StaticClass();
	UClass* Dinosaur = ADinosaur::StaticClass();

	if (bear)
	{
		GLog->Log(FString::Printf(TEXT("bear 있음")));
	}
	else
	{
		GLog->Log(FString::Printf(TEXT("bear 있음")));
	}

	if (Dinosaur)
	{
		GLog->Log(FString::Printf(TEXT("Dinosaur 있음")));
	}
	else
	{
		GLog->Log(FString::Printf(TEXT("Dinosaur 있음")));
	}

	whatToSpawn_Array.Add(bear);
	whatToSpawn_Array.Add(Dinosaur);
}

