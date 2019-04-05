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
	//TSubclassOf<class AMonster> whatToSpawn;
	TArray <TSubclassOf<class AMonster>> whatToSpawn_Array;

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

	/** ObjectPool init function*/
	void PoolSetting();

	/** ObjectPool Pooling*/
	void Pooling(int);

	/** Send To Server Get Next Pooling Massage */

	/** Get To Server Start Pooling Massage */
private:
	/** Box Component to specify where pickups should be spawned*/
	UPROPERTY(VisibleAnywhere, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* whereToSpawn;

	UPROPERTY(VisibleAnywhere, Category = "Spawning")
	int FullPoolVolume;

	/** If you want to use this, check to attribute*/
	UPROPERTY(EditAnywhere, Category = "TestPool")
		bool isTestPoolStart;

	UPROPERTY(VisibleAnywhere, Category = "Spawning")
	TArray<class AMonster*> Spawn_Array;

	//Object Position
	FVector SpawnPos_Vector;

	/** SpawnObject Activate*/
	void SpawnObject_SetActive(AMonster*, bool);

	/** Monster Set useful*/
	void RecycleObject(AMonster*);

	/** Monster Class input whatToSpawn_Array*/
	void SetStaticMonsterClass();

	//Get Spawn Info
	void Recive_SpawnObject_Info(int[], int[],FVector[]);

	//Check Non-Active Monster
	void check_ReadyMonster();

	//SpawnPos Selecter
	void WhereToGate();
};
