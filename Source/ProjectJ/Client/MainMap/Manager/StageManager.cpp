// Fill out your copyright notice in the Description page of Project Settings.

#include "StageManager.h"
//클라 헤더
#include "Engine/World.h" 
#include "Client/Monster/Monster.h" //몬스터 헤더
#include "TimerManager.h" //타이머 헤더
#include "UObject/ConstructorHelpers.h" // 경로 탐색 헤더
#include "Particles/ParticleSystem.h"  //파티클 관련 헤더 파일
//서버 헤더

// Sets default values for this component's properties
UStageManager::UStageManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<UParticleSystem>PT_SpawnEffect(TEXT("ParticleSystem'/Game/Assets/Monster/ParagonMinions/FX/Particles/Minions/Shared/P_MinionSpawn.P_MinionSpawn'"));

	if (PT_SpawnEffect.Succeeded())
	{
		SpawnEffect = PT_SpawnEffect.Object;
	}
}


// Called when the game starts
void UStageManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UStageManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UStageManager::SetSpawnMonsterInfo(AMonster * _Monster, int32 _Count)
{
	CurrentSpawnMonster = _Monster;
	CurrentSpawnMonsterCount = _Count;
}

void UStageManager::SpawnStart()
{
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &UStageManager::Spawn, 2.0f, true, 2.0f);
}

void UStageManager::Spawn()
{

}

