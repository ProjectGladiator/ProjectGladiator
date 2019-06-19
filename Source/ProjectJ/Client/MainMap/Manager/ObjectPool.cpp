// Fill out your copyright notice in the Description page of Project Settings.

#include "ObjectPool.h"
//클라 헤더
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "NetWork/DataProtocol.h"
#include "Client/Monster/StageOne/Bear/Bear.h"
#include "Client/Monster/StageOne/Dinosaur/Dinosaur.h"
#include "Client/Monster/StageTwo/Dog/Dog.h"
#include "Client/Monster/StageOne/Spider/Spider.h"
#include "Client/Monster/MonsterAIController.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h" // 경로 탐색 헤더
#include "Particles/ParticleSystem.h"  //파티클 관련 헤더 파일

//서버 헤더
#include "NetWork/StorageManager.h"

// Sets default values
AObjectPool::AObjectPool()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// create the Box Component the spawn volume
	DefaultSpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("WhereToSpawn"));

	//Root -> Boxcomponent
	RootComponent = DefaultSpawnArea;

	//sameMonster class Array 
	FMonsterstruct MonsterArray;
	//Set SpawnNum
	DefaultSpawnArea_Map.Emplace(MONSTER_CODE::SPIDER, MonsterArray);
	DefaultSpawnArea_Map.Emplace(MONSTER_CODE::WORM, MonsterArray);
	DefaultSpawnArea_Map.Emplace(MONSTER_CODE::BOSS_SPIDER, MonsterArray);

	////Test to Use this pool check
	bis_Testpool_Set = false;
	//Set Ready SpawnMonsterCounter Zero
	SpawnMonsterCounter = 0;
	static ConstructorHelpers::FObjectFinder<UParticleSystem>PT_SpawnEffect(TEXT("ParticleSystem'/Game/Assets/Monster/ParagonMinions/FX/Particles/Minions/Shared/P_MinionSpawn.P_MinionSpawn'"));

	if (PT_SpawnEffect.Succeeded())
	{
		SpawnEffect = PT_SpawnEffect.Object;
	}
}

// Called when the game starts or when spawned
void AObjectPool::BeginPlay()
{
	Super::BeginPlay();


	GLog->Log(FString::Printf(TEXT("AObjectPool BeginPlay")));
	//Set Pool volume to BeginPlay
	PoolSetting();
}

// Called every frame
void AObjectPool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PacketData* Data;

	int Monster_Code;
	int Monster_Num;
	int Take_Damage;


	if (StorageManager::GetInstance()->GetFront(Data)) //창고매니저 큐에 들어있는 데이터를 가져와서 Data에 담는다.
	{
		switch (Data->protocol) //담아온 Data의 프로토콜을 확인한다.
		{
		case PGAMEDATA_STAGE_MONSTER_TPYES_COUNT: // 스테이지 몬스터 종류가 몇개인지 - (종류 숫자)
			//StorageManager::GetInstance()->ChangeData(SpawnMonster_Num);
			StorageManager::GetInstance()->PopData();
			break;
		case PGAMEDATA_STAGE_MONSTER_INFO: // 스테이지 몬스터 정보 - (몬스터코드,몬스터숫자,좌표)
			StorageManager::GetInstance()->ChangeData(Data->data, KindMonster, SpawnMonster_Num, SpawnPos.X, SpawnPos.Y, SpawnPos.Z);
			StorageManager::GetInstance()->PopData();
			Timer();
			break;
		case PGAMEDATA_STAGE_MONSTER_SPAWN_TIME: // 스테이지 몬스터 스폰 시간 - ([float] 몬스터 스폰시간)
			StorageManager::GetInstance()->ChangeData(Data->data, SpawnTime);
			StorageManager::GetInstance()->PopData();
			break;
		case PGAMEDATA_MONSTER_ATTACK_SUCCESS: // 몬스터 공격받음(공격성공 살아있음) - ([int] 몬스터코드, [int] 몬스터번호, [int] 입힌데미지)
			StorageManager::GetInstance()->ChangeData(Data->data, Monster_Code, Monster_Num, Take_Damage);
			StorageManager::GetInstance()->PopData();
			for (int i_Num = 0; i_Num < ActiveMonster_Array.Num(); i_Num++)
			{
				if (ActiveMonster_Array[i_Num].MonsterCode == Monster_Code && ActiveMonster_Array[i_Num].MonsterNum == Monster_Num)
				{
					//GLog->Log(FString::Printf(TEXT("AMonster Tick GetActorLocation X : %f Y : %f Z : %f\n"), GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z));
					GLog->Log(FString::Printf(TEXT("나에게 맞아 데미지를 받기 시작합니다.")));
					GLog->Log(FString::Printf(TEXT("데미지 받기 전 %f, 받은 데미지 %f"), ActiveMonster_Array[i_Num].Monster->GetHP(), Take_Damage));
					
					ActiveMonster_Array[i_Num].Monster->SetHP(ActiveMonster_Array[i_Num].Monster->GetHP() - Take_Damage);

					GLog->Log(FString::Printf(TEXT("데미지 받은 후 %d"), ActiveMonster_Array[i_Num].Monster->GetHP()));
				}
			}
			break;
		case PGAMEDATA_MONSTER_ATTACK_FAIL:					// 몬스터 공격받음(공격실패) - (프로토콜만)
			StorageManager::GetInstance()->PopData();
			break;
		case PGAMEDATA_MONSTER_ATTACK_DIE:					// 몬스터 공격받음(죽어버림) - ([int] 몬스터코드, [int] 몬스터번호, [int] 입힌데미지)
			StorageManager::GetInstance()->ChangeData(Data->data, Monster_Code, Monster_Num, Take_Damage);
			StorageManager::GetInstance()->PopData();
			for (int i_Num = 0; i_Num < ActiveMonster_Array.Num(); i_Num++)
			{
				if (ActiveMonster_Array[i_Num].MonsterCode == Monster_Code && ActiveMonster_Array[i_Num].MonsterNum == Monster_Num)
				{
					GLog->Log(FString::Printf(TEXT("나 에게 맞아 사형선고를 받기 시작합니다.")));
					GLog->Log(FString::Printf(TEXT("데미지 받기 전 %d, 받은 데미지 %d"), ActiveMonster_Array[i_Num].Monster->GetHP(), Take_Damage));

					ActiveMonster_Array[i_Num].Monster->SetHP(ActiveMonster_Array[i_Num].Monster->GetHP() - Take_Damage);
					

					GLog->Log(FString::Printf(TEXT("데미지 받은 후 %d"), ActiveMonster_Array[i_Num].Monster->GetHP()));

					//Monster의 Death Function 호출
					ActiveMonster_Array[i_Num].Monster->Death();
					Remove_ActiveMonsterArry(Monster_Code, Monster_Num);
				}
			}
			break;

		case PGAMEDATA_MONSTER_OTHERPLAYER_ATTACK:			// 다른 유저가 몬스터 공격함(살아있음) - ([int] 몬스터코드, [int] 몬스터번호, [int] 입힌데미지)
			StorageManager::GetInstance()->ChangeData(Data->data, Monster_Code, Monster_Num, Take_Damage);
			StorageManager::GetInstance()->PopData();
			for (int i_Num = 0; i_Num < ActiveMonster_Array.Num(); i_Num++)
			{
				if (ActiveMonster_Array[i_Num].MonsterCode == Monster_Code && ActiveMonster_Array[i_Num].MonsterNum == Monster_Num)
				{
					GLog->Log(FString::Printf(TEXT("타 유저에게 맞아 데미지를 받기 시작합니다.")));
					GLog->Log(FString::Printf(TEXT("데미지 받기 전 %d, 받은 데미지 %d"), ActiveMonster_Array[i_Num].Monster->GetHP(), Take_Damage));

					ActiveMonster_Array[i_Num].Monster->SetHP(ActiveMonster_Array[i_Num].Monster->GetHP() - Take_Damage);

					GLog->Log(FString::Printf(TEXT("데미지 받은 후 %d"), ActiveMonster_Array[i_Num].Monster->GetHP()));
				}
			}
			break;			
		case PGAMEDATA_MONSTER_OTHERPLAYER_ATTACK_DIE:		// 다른 유저가 몬스터 공격함(죽어버림) - ([int] 몬스터코드, [int] 몬스터번호, [int] 입힌데미지)
			StorageManager::GetInstance()->ChangeData(Data->data, Monster_Code, Monster_Num, Take_Damage);
			StorageManager::GetInstance()->PopData();
			for (int i_Num = 0; i_Num < ActiveMonster_Array.Num(); i_Num++)
			{
				if (ActiveMonster_Array[i_Num].MonsterCode == Monster_Code && ActiveMonster_Array[i_Num].MonsterNum == Monster_Num)
				{
					GLog->Log(FString::Printf(TEXT("타 유저에게 맞아 사형선고를 받기 시작합니다.")));
					GLog->Log(FString::Printf(TEXT("데미지 받기 전 %d, 받은 데미지 %d"), ActiveMonster_Array[i_Num].Monster->GetHP(), Take_Damage));

					ActiveMonster_Array[i_Num].Monster->SetHP(ActiveMonster_Array[i_Num].Monster->GetHP() - Take_Damage);

					GLog->Log(FString::Printf(TEXT("데미지 받은 후 %d"), ActiveMonster_Array[i_Num].Monster->GetHP()));
					ActiveMonster_Array[i_Num].Monster->Death();
					Remove_ActiveMonsterArry(Monster_Code, Monster_Num);
				}
			}
			break;
		}
	}
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
		if (bis_Testpool_Set == true)
		{
			throw bis_Testpool_Set;
		}

		////kind of Monster AND Monster's Maximum size (예비로 최대량을 정해놓고 만들어둠)
		Set_MonsterVolume_With_Array(DefaultSpawnArea_Map[MONSTER_CODE::SPIDER].Monster_Volum_Array, MONSTER_CODE::SPIDER, 10, ABear::StaticClass());
		Set_MonsterVolume_With_Array(DefaultSpawnArea_Map[MONSTER_CODE::WORM].Monster_Volum_Array, MONSTER_CODE::WORM,10, ADinosaur::StaticClass());
		Set_MonsterVolume_With_Array(DefaultSpawnArea_Map[MONSTER_CODE::BOSS_SPIDER].Monster_Volum_Array, MONSTER_CODE::BOSS_SPIDER, 10, ADog::StaticClass());
	
	}
	catch (bool) {
		if (bis_Testpool_Set == true)
		{
			UE_LOG(LogTemp, Warning, TEXT("Pool DisActive"));
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
		if (_counter < -1)
		{
			throw _counter;
		}

		// Pooling Enter
		UE_LOG(LogTemp, Warning, TEXT("Pooling Enter"));

	}
	catch (int) {
		
		if (_counter < -1)
		{
			//Error not to use ObjectPool
			UE_LOG(LogTemp, Warning, TEXT("_counter is (-)value"));
		}
	}
}

TMap<MONSTER_CODE, FMonsterstruct> AObjectPool::Get_SpawnMoster_Map()
{
	return DefaultSpawnArea_Map;
}

TArray<FActiveMonsterInfo> AObjectPool::Get_ActiveMonster_Array()
{
	return ActiveMonster_Array;
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

bool AObjectPool::check_RecycleObject(AMonster* _spawnMonster)
{
	if (_spawnMonster->bisActive == false)
	{
		//Make BisActive false -> true
		return true;
	}
	else
		return false;
}

void AObjectPool::Recive_SpawnObject_Info()
{

	//Get SpawnMonster's type Array
	//Get The Array's Num
	//Get SpawnPosition
	//Last,Find Non_Active Monster 

	//@@ 뭔가 잘못됨 마리수를 정해놓지도 않았고 최대 량만큼 돌고 다시 또 돌려고 하고있음 디버그하면서 찾아봐야함

	if (SpawnMonsterCounter == SpawnMonster_Num)
	{
		//SpawnCounter Reset
		SpawnMonsterCounter = 0;
		//Timer Kill
		GetWorld()->GetTimerManager().ClearTimer(SpawnUpdateTimer);
	}
	else
	{
		ReadyMonster(static_cast<MONSTER_CODE>(KindMonster), SpawnPos);
		//Counter Update
		++SpawnMonsterCounter;
	}
}

void AObjectPool::ReadyMonster(MONSTER_CODE _MonsterCode, FVector _MonsterPostion)
{
	for (int i_Monster = 0; i_Monster < DefaultSpawnArea_Map[(MONSTER_CODE)_MonsterCode].Monster_Volum_Array.Num(); i_Monster++)
	{
		if (check_RecycleObject(DefaultSpawnArea_Map[(MONSTER_CODE)_MonsterCode].Monster_Volum_Array[i_Monster]))
		{
			UE_LOG(LogTemp, Warning, TEXT("Monster Recycle"));

			//Active Actor to bisActive make true;
			DefaultSpawnArea_Map[(MONSTER_CODE)_MonsterCode].Monster_Volum_Array[i_Monster]->bisActive = true;

			//Get Monster's init
			DefaultSpawnArea_Map[(MONSTER_CODE)_MonsterCode].Monster_Volum_Array[i_Monster]->Firstinit(_MonsterCode, i_Monster);
			DefaultSpawnArea_Map[(MONSTER_CODE)_MonsterCode].Monster_Volum_Array[i_Monster]->SetActorLocation(_MonsterPostion);
			DefaultSpawnArea_Map[(MONSTER_CODE)_MonsterCode].Monster_Volum_Array[i_Monster]->S2C_LocationUpdate(_MonsterPostion);

			//Monster
			SpawnObject_SetActive(DefaultSpawnArea_Map[(MONSTER_CODE)_MonsterCode].Monster_Volum_Array[i_Monster], true);

			//Setting Target
			DefaultSpawnArea_Map[(MONSTER_CODE)_MonsterCode].Monster_Volum_Array[i_Monster]->FirstTarget();

			//Temporary Struct to Put in ActvieMonster_Array
			FActiveMonsterInfo TempActiveMonsterInfo;
			TempActiveMonsterInfo.MonsterCode = _MonsterCode;
			TempActiveMonsterInfo.MonsterNum = i_Monster;
			TempActiveMonsterInfo.Monster = DefaultSpawnArea_Map[(MONSTER_CODE)_MonsterCode].Monster_Volum_Array[i_Monster];

			//ActiveMonster's Array is Send To Server MonsterInfo
			ActiveMonster_Array.Emplace(TempActiveMonsterInfo);

			break;
		}
		/*else*/
		//UE_LOG(LogTemp, Warning, TEXT("Monster Recycle Fail"));
	}
	
}

void AObjectPool::Set_MonsterVolume_With_Array(TArray<class AMonster*>& _MonsterTypeArray, MONSTER_CODE _MonsterCode, int _MaximumSize, TSubclassOf<class AMonster> _MonsterClass)
{
	//SpawnParameter with CollisionHandling Set
	FActorSpawnParameters SpawnActorOption;

	//Use SpawnActorOption, ESpawnActorCollisionHandlingMethod::[ AlwaysSpawn OR AdjustIfPossibleButAlwaysSpawn ]
	SpawnActorOption.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	//Object Position
	FVector SpawnPos_Vector;
	//Default SpawnVector Pos
	SpawnPos_Vector = DefaultSpawnArea->Bounds.Origin;

	for (int i_spawnObject = 0; i_spawnObject < _MaximumSize; i_spawnObject++)
	{
		//Create Actor
		AMonster* SpawnActor = nullptr;

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

			//Set up Monster's Code and Num
			SpawnActor->SetMonsterCode(_MonsterCode);
			SpawnActor->SetMonsterNum(i_spawnObject);

			//SpawnActor's ActiveMode Setting False
			SpawnObject_SetActive(SpawnActor, false);

			//input Array to SpawnActor
			_MonsterTypeArray.Add(SpawnActor);
		}
		else if (SpawnActor == nullptr)
		{
			//GLog->Log(FString::Printf(TEXT("SpawnActor Error")));
			UE_LOG(LogTemp, Error, TEXT("SpawnActor Error is Nullptr"));
		}
	}
}

void AObjectPool::Timer()
{

	//Timer에 Handle, 사용하는객체(클래스), 반복할 메소드, 반복시간
	GetWorld()->GetTimerManager().SetTimer(SpawnUpdateTimer, this, &AObjectPool::Recive_SpawnObject_Info, SpawnTime, true, 0);

}

void AObjectPool::Remove_ActiveMonsterArry(int _MonsterCode, int _MonsterNum)
{
	////옵젝풀 선언
	//AObjectPool ObjectPool;
	////임시 활성화 몬스터 배열 생성
	//TArray<FActiveMonsterInfo> TempArray = ObjectPool.Get_ActiveMonster_Array();

	//사망처리 몬스터 배열에서 찾아 빼주는 작업
	for (int i_Num = 0; i_Num < ActiveMonster_Array.Num(); i_Num++)
	{
		if (ActiveMonster_Array[i_Num].MonsterCode == _MonsterCode && ActiveMonster_Array[i_Num].MonsterNum == _MonsterNum)
		{
			ActiveMonster_Array.RemoveAt(i_Num);
			//TempArray.Sort();
		}
	}
}

