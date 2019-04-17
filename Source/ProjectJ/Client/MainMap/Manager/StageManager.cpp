// Fill out your copyright notice in the Description page of Project Settings.

#include "StageManager.h"
//클라 헤더
#include "Engine/World.h"
#include "Client/MainMap/Manager/ObjectPool.h"

//서버 헤더

// Sets default values for this component's properties
UStageManager::UStageManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

}

// Called when the game starts
void UStageManager::BeginPlay()
{
	Super::BeginPlay();

	FActorSpawnParameters SpawnActorOption;
	
	ObjectPool = GetWorld()->SpawnActor<AObjectPool>(ObjectPool->StaticClass(), FVector(4607.0f,18000.0f,4500.0f), FRotator::ZeroRotator, SpawnActorOption);

}


// Called every frame
void UStageManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

AObjectPool * UStageManager::GetObjectPool()
{
	if (ObjectPool)
	{
		return ObjectPool;
	}
	else
	{
		return nullptr;
	}
}

