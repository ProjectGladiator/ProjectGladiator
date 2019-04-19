// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NetWork/MonsterInfo.h"
#include "ObjectPool.generated.h"
USTRUCT()
struct FMonsterstruct
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditAnywhere, Category = "Spawning")
	TArray<class AMonster*> Monster_Volum_Array;
};
/** Monster Type Enum*/
UENUM()
enum class enumMonsterType : uint8
{
	//Stage 1
	Bear, Dinosaur, Spider, SpiderBoss, Worm,
	//Stage 2
	Dog, Grount
};
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
	
	//enumMonsterType MonsterType_Enum;

	/** This Data Structure is Monster's Type and list of Array*/
	//UPROPERTY(EditAnywhere, Category = "Spawning")
	TMap<MONSTER_CODE,FMonsterstruct> DefaultSpawnArea_Map;
		
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
	class UBoxComponent* DefaultSpawnArea;


	/** if you want to use this, check to attribute*/
	UPROPERTY(EditAnywhere, Category = "Spawning")
		bool bis_Testpool_Set;

	//UPROPERTY(VisibleAnywhere, Category = "Spawning")
	//TArray<class AMonster*> Spawn_Array;

	//Object Position
	FVector SpawnPos_Vector;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, Meta = (AllowPrivateAccess = true))
		class UParticleSystem* SpawnEffect;

	/** SpawnObject Activate*/
	void SpawnObject_SetActive(AMonster*, bool);

	/** Monster Set useful*/
	bool check_RecycleObject(AMonster*);

	/** Monster Class input whatToSpawn_Array*/
	void SetStaticMonsterClass();

	//Get Spawn Info
	void Recive_SpawnObject_Info(int, MONSTER_CODE, FVector);

	//Check Non-Active Monster
	void ReadyMonster(MONSTER_CODE,int,FVector);

	//SpawnPos Selecter
	void WhereToGate();

	/**Create Maximum Monster Setting */
	void Set_MonsterVolume_With_Array(TArray<class AMonster*>&, int, TSubclassOf<class AMonster>);
};
