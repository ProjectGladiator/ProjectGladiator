// Fill out your copyright notice in the Description page of Project Settings.

#include "ObjectPool.h"

#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "Client/Monster/Monster.h"
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
	FullPoolVolume = initPoolVolume;

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
	//Get World
	UWorld* const world = GetWorld();

	//Set ths Spawn Paramaters
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = Instigator;

	
	for (int i_spawnObject = 0; i_spawnObject < FullPoolVolume; i_spawnObject++)
	{
		//어떤 Monster를 사용할 건지 정하는 부분을 만들어야함

		AMonster* SpawnActor = world->SpawnActor<AMonster>(whatToSpawn[0], FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
		Spawn_Array.Add(SpawnActor);

		UE_LOG(LogTemp, Warning, TEXT("SpawnActor Create"));

		SpawnObject_SetActive(Spawn_Array[i_spawnObject], false);
		Spawn_Array[i_spawnObject]->bisActive = false;
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
		//SpawnObject->SetActorEnableCollision(true);
		SpawnObject->SetActorTickEnabled(true);
	}
	else
	{
		// Hides visible components
		SpawnObject->SetActorHiddenInGame(true);
		// Disables collision components
		///SpawnObject->SetActorEnableCollision(false);
		// Stops the Actor from ticking
		SpawnObject->SetActorTickEnabled(false);
	}
}

void AObjectPool::ResetObject()
{
}

