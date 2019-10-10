// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Client/Monster/Monster.h"
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
//UENUM()
//enum class enumMonsterType : uint8
//{
//	//Stage 1
//	Bear, Dinosaur, Spider, SpiderBoss, Worm,
//	//Stage 2
//	Dog, Grount
//};

UENUM()
enum class EMonsterStage : uint8
{
	DEFAULT,STAGE1,STAGE2,STAGE3
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
public:	
	// Called every frame	
	virtual void Tick(float DeltaTime) override;
	
	/** Find a random point with in the BoxComponent*/
	UFUNCTION(BlueprintPure, Category = "Spawning")
	FVector GetRandomPointInVolume();

	/** ObjectPool init function*/
	void PoolSetting(int _EStage);

	/** ObjectPool Pooling*/
	void Pooling(int);

	/** Get SpawnMonster_Map*/
	TMap<MONSTER_CODE, FMonsterstruct> Get_SpawnMoster_Map();
	/** Get ActvieMonster_Array*/
	TArray<FActiveMonsterInfo> Get_ActiveMonster_Array();
	/** Pool Position*/
	FVector SpawnPos_Vector;

private:
	EMonsterStage EStage;

	/** This Data Structure is Monster's Type and list of Array*/
	TMap<MONSTER_CODE, FMonsterstruct> Monsterinfo_Map;

	/** This Array is Activing Monster's Struct*/
	TArray<FActiveMonsterInfo> ActiveMonster_Array;

	/** Box Component to specify where pickups should be spawned(First Spawn And ReadyArea)*/
	UPROPERTY(VisibleAnywhere, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* ReadySpawnArea;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, Meta = (AllowPrivateAccess = true))
		class UParticleSystem* SpawnEffect;

	UPROPERTY()
	FTimerHandle SpawnUpdateTimer;

	UPROPERTY()
	float SpawnTime;

	UPROPERTY()
	int SpawnMonsterCounter;
	UPROPERTY()
	int KindMonster;
	UPROPERTY()
	int SpawnMonster_Num;
	UPROPERTY()
	FVector SpawnPos;

	/** SpawnObject Activate*/
	void SpawnObject_SetActive(AMonster*, bool);

	/** Monster Set useful*/
	bool check_RecycleObject(AMonster*);

	//Check Non-Active Monster
	void ReadyMonster(MONSTER_CODE,FVector);

	/**Create Maximum Monster Setting */
	void Set_MonsterVolume_With_Array(TArray<class AMonster*>&, MONSTER_CODE,int, TSubclassOf<class AMonster>);

	/**Timer To Spawn*/
	void Timer();

	void Remove_ActiveMonsterArry(int _MonsterCode, int _MonsterNum);
};
