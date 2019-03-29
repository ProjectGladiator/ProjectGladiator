// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectPool.generated.h"

UCLASS()
class PROJECTJ_API AObjectPool : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObjectPool();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	/** The Pickup to spawn*/
	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<class AMonster> whatToSpawn;
	//	TArray < class TSubclassOf<class AMonster>> whatToSpawn;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	/** Find a random point with in the BoxComponent*/
	UFUNCTION(BlueprintPure, Category = "Spawning")
		FVector GetRandomPointInVolume();

	/** Set PoolVolume to Start*/
	UPROPERTY(EditAnywhere, Category = "Spawning")
	int initPoolVolume;

	/** Current Pool Scale*/
	//UPROPERTY(VisibleAnywhere, Category = "Spawning")
	//int currentPool_count;

	void PoolSetting();

	void Pooling(int);

private:
	/** Box Component to specify where pickups should be spawned*/
	UPROPERTY(VisibleAnywhere, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* whereToSpawn;

	UPROPERTY(VisibleAnywhere, Category = "Spawning")
	int FullPoolVolume;

	TArray<class AMonster*> Spawn_Array;

	/** SpawnObject_SetActive*/
	void SpawnObject_SetActive(AMonster*, bool);
};
