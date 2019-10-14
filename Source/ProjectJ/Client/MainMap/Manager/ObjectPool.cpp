// Fill out your copyright notice in the Description page of Project Settings.

#include "ObjectPool.h"
//클라 헤더
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "Client/MyCharacter/PC/MyCharacter.h"
#include "Client/Monster/StageThree/Bear/Bear.h"
#include "Client/Monster/StageThree/Dinosaur/Dinosaur.h"
#include "Client/Monster/StageTwo/Dog/Dog.h"
#include "Client/Monster/StageOne/Spider/Spider.h"
#include "Client/Monster/StageOne/SpiderBoss/SpiderBoss.h"
#include "Client/Monster/StageOne/Worm/Worm.h"
#include "Client/Monster/StageTwo/HammerBoss/Brute.h"
#include "Client/Monster/MonsterAIController.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h" // 경로 탐색 헤더
#include "Particles/ParticleSystem.h"  //파티클 관련 헤더 파일

//서버 헤더
#include "NetWork/StorageManager.h"
#include "NetWork/DataProtocol.h"

// Sets default values
AObjectPool::AObjectPool()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// create the Box Component the spawn volume
	ReadySpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("WhereToSpawn"));

	//Root -> Boxcomponent
	RootComponent = ReadySpawnArea;

	//sameMonster class Array 
	FMonsterstruct MonsterArray;

	//Set SpawnNum
	//SPIDER = 10001,
	//	WORM = 10002,
	//	BOSS_SPIDER = 10003,
	//	// 2스테이지
	//	DOG = 20001,
	//	ORCCANNONSOLDIER = 20002,
	//	KING_OF_THEAXE = 20003,
	//	//3스테이지
	//	BEAR = 30001,
	//	DINOSAUR = 30002,
	//	DRAGON = 30003
	Monsterinfo_Map.Emplace(MONSTER_CODE::SPIDER, MonsterArray);
	Monsterinfo_Map.Emplace(MONSTER_CODE::WORM, MonsterArray);
	Monsterinfo_Map.Emplace(MONSTER_CODE::BOSS_SPIDER, MonsterArray);
	Monsterinfo_Map.Emplace(MONSTER_CODE::DOG, MonsterArray);
	//DefaultSpawnArea_Map.Emplace(MONSTER_CODE::ORCCANNONSOLDIER, MonsterArray);
	Monsterinfo_Map.Emplace(MONSTER_CODE::BEAR, MonsterArray);
	Monsterinfo_Map.Emplace(MONSTER_CODE::DINOSAUR, MonsterArray);
	Monsterinfo_Map.Emplace(MONSTER_CODE::KING_OF_THEAXE, MonsterArray);

	////Test to Use this pool check
	//bis_Testpool_Set = false;

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
	PoolSetting(0);
}

// Called every frame
void AObjectPool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PacketData* Data;

	int Monster_Code = 0;
	int Monster_Num = 0;
	int Take_Damage = 0;
	bool isAttack_Result = false;
	bool isAlive_Monster = false;

	char TempPartyReqCharacterCode[30];
	char* PartyReqCharacterCode = TempPartyReqCharacterCode;

	if (StorageManager::GetInstance()->GetFront(Data)) //창고매니저 큐에 들어있는 데이터를 가져와서 Data에 담는다.
	{
		switch (Data->protocol) //담아온 Data의 프로토콜을 확인한다.
		{
		case PGAMEDATA_MONSTER_TARGET_INFO:// 몬스터의 타겟(캐릭터)정보 - ([int] 몬스터코드, [int] 몬스터번호, [char] 유저캐릭터코드)

			memset(TempPartyReqCharacterCode, 0, sizeof(TempPartyReqCharacterCode));

			StorageManager::GetInstance()->ChangeData(Data->data,Monster_Code,Monster_Num, PartyReqCharacterCode);
			StorageManager::GetInstance()->PopData();
			//몬스터 배열 사용
			for (int i_Num = 0; i_Num < ActiveMonster_Array.Num(); i_Num++)
			{
				//몬스터 코드와 번호 가 일치하는 원소를 찾음
				if (ActiveMonster_Array[i_Num].MonsterCode == Monster_Code && ActiveMonster_Array[i_Num].MonsterNum == Monster_Num)
				{
					//Target(MyCharacter) 의 케릭터 코드를 설정
					ActiveMonster_Array[i_Num].Monster->Targeting(PartyReqCharacterCode);
				}
			}
			break;
		case PGAMEDATA_STAGE_MONSTER_TPYES_COUNT: // 스테이지 몬스터 종류가 몇개인지 - (종류 숫자)
			//StorageManager::GetInstance()->ChangeData(SpawnMonster_Num);
			StorageManager::GetInstance()->PopData();
			break;
		case PGAMEDATA_STAGE_MONSTER_INFO: // 스테이지 몬스터 정보 - (몬스터코드,몬스터숫자,좌표)
			StorageManager::GetInstance()->ChangeData(Data->data, KindMonster, SpawnMonster_Num, SpawnPos.X, SpawnPos.Y, SpawnPos.Z);
			StorageManager::GetInstance()->PopData();

			ReadyMonster(static_cast<MONSTER_CODE>(KindMonster), SpawnPos);

			break;
		case PGAMEDATA_STAGE_MONSTER_SPAWN_TIME: // 스테이지 몬스터 스폰 시간 - ([float] 몬스터 스폰시간)
			StorageManager::GetInstance()->ChangeData(Data->data, SpawnTime);
			StorageManager::GetInstance()->PopData();
			break;
		case PGAMEDATA_USER_ATTACKED_THE_MONSTER_RESULT:// 유저가 몬스터를 공격한 결과 - ([bool] 성공실패결과, [int] 몬스터 코드, [int] 몬스터 번호, [int] 데미지, [bool] 죽었는지살았는지)	
			StorageManager::GetInstance()->ChangeData(Data->data, isAttack_Result, Monster_Code, Monster_Num, Take_Damage, isAlive_Monster);
			StorageManager::GetInstance()->PopData();
			//공격결과가 True이면
			if (isAttack_Result)
			{
				GLog->Log(FString::Printf(TEXT("공격 성공 메소드 실행.")));
				if (isAlive_Monster)
				{
					//몬스터 배열 사용
					for (int i_Num = 0; i_Num < ActiveMonster_Array.Num(); i_Num++)
					{
						//몬스터 코드와 번호 가 일치하는 원소를 찾음
						if (ActiveMonster_Array[i_Num].MonsterCode == Monster_Code && ActiveMonster_Array[i_Num].MonsterNum == Monster_Num)
						{
							GLog->Log(FString::Printf(TEXT("나에게 맞아 데미지를 받기 시작합니다.")));
							GLog->Log(FString::Printf(TEXT("데미지 받기 전 %f, 받은 데미지 %f"), ActiveMonster_Array[i_Num].Monster->GetHP(), Take_Damage));

							ActiveMonster_Array[i_Num].Monster->SetHP(ActiveMonster_Array[i_Num].Monster->GetHP() - Take_Damage);

							GLog->Log(FString::Printf(TEXT("데미지 받은 후 %d"), ActiveMonster_Array[i_Num].Monster->GetHP()));
						}
					}
				}
				else if (isAlive_Monster == false)
				{
					for (int i_Num = 0; i_Num < ActiveMonster_Array.Num(); i_Num++)
					{
						//몬스터 코드와 번호 가 일치하는 원소를 찾음
						if (ActiveMonster_Array[i_Num].MonsterCode == Monster_Code && ActiveMonster_Array[i_Num].MonsterNum == Monster_Num)
						{
							//Deat()안에서 CurrentHP 강제로 0으로 만들어줌
							ActiveMonster_Array[i_Num].Monster->Death();
							Remove_ActiveMonsterArry(Monster_Code, Monster_Num);
							break;
						}
					}
				}
			}//END of if (isAttack_Result)
			else
			{
				GLog->Log(FString::Printf(TEXT("공격 결과가 실패로 들어왔습니다.")));
			}
			break;		
		case PGAMEDATA_OTHERUSER_ATTACKED_THE_MONSTER:// 다른 유저가 몬스터를 공격한 결과 - ([int] 몬스터 코드, [int] 몬스터 번호, [int] 데미지, [bool] 죽었는지살았는지)
			StorageManager::GetInstance()->ChangeData(Data->data, Monster_Code, Monster_Num, Take_Damage, isAlive_Monster);
			StorageManager::GetInstance()->PopData();
			GLog->Log(FString::Printf(TEXT("공격 성공 메소드 실행.")));
			if (isAlive_Monster)
			{
				//몬스터 배열 사용
				for (int i_Num = 0; i_Num < ActiveMonster_Array.Num(); i_Num++)
				{
					//몬스터 코드와 번호 가 일치하는 원소를 찾음
					if (ActiveMonster_Array[i_Num].MonsterCode == Monster_Code && ActiveMonster_Array[i_Num].MonsterNum == Monster_Num)
					{
						GLog->Log(FString::Printf(TEXT("아군에게 맞아 데미지를 받기 시작합니다.")));
						GLog->Log(FString::Printf(TEXT("데미지 받기 전 %f, 받은 데미지 %f"), ActiveMonster_Array[i_Num].Monster->GetHP(), Take_Damage));

						ActiveMonster_Array[i_Num].Monster->SetHP(ActiveMonster_Array[i_Num].Monster->GetHP() - Take_Damage);

						GLog->Log(FString::Printf(TEXT("데미지 받은 후 %d"), ActiveMonster_Array[i_Num].Monster->GetHP()));
					}
				}
			}
			else if (isAlive_Monster == false)
			{
				for (int i_Num = 0; i_Num < ActiveMonster_Array.Num(); i_Num++)
				{
					//몬스터 코드와 번호 가 일치하는 원소를 찾음
					if (ActiveMonster_Array[i_Num].MonsterCode == Monster_Code && ActiveMonster_Array[i_Num].MonsterNum == Monster_Num)
					{
						//Death()안에서 CurrentHP 강제로 0으로 만들어줌
						ActiveMonster_Array[i_Num].Monster->Death();
						Remove_ActiveMonsterArry(Monster_Code, Monster_Num);
						break;
					}
				}
			}
			break;
		}
	}
}

FVector AObjectPool::GetRandomPointInVolume()
{
	//Origin Spawn Area
	FVector SpawnOrigin = ReadySpawnArea->Bounds.Origin;
	//Extent Spawn Area
	FVector SpawnExtent = ReadySpawnArea->Bounds.BoxExtent;

	return UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrigin, SpawnExtent);
}

void AObjectPool::PoolSetting(int _EStage)
{
	switch ((EMonsterStage)_EStage)
	{
	case EMonsterStage::STAGE1:
		////kind of Monster AND Monster's Maximum size (예비로 최대량을 정해놓고 만들어둠)
		Set_MonsterVolume_With_Array(Monsterinfo_Map[MONSTER_CODE::SPIDER].Monster_Volum_Array, MONSTER_CODE::SPIDER, 15, ASpider::StaticClass());
		Set_MonsterVolume_With_Array(Monsterinfo_Map[MONSTER_CODE::WORM].Monster_Volum_Array, MONSTER_CODE::WORM, 20, AWorm::StaticClass());
		Set_MonsterVolume_With_Array(Monsterinfo_Map[MONSTER_CODE::BOSS_SPIDER].Monster_Volum_Array, MONSTER_CODE::BOSS_SPIDER, 1, ASpiderBoss::StaticClass());
		break;
	case EMonsterStage::STAGE2:
		Set_MonsterVolume_With_Array(Monsterinfo_Map[MONSTER_CODE::DOG].Monster_Volum_Array, MONSTER_CODE::DOG, 10, ADog::StaticClass());
		Set_MonsterVolume_With_Array(Monsterinfo_Map[MONSTER_CODE::BEAR].Monster_Volum_Array, MONSTER_CODE::BEAR, 10, ABear::StaticClass());
		Set_MonsterVolume_With_Array(Monsterinfo_Map[MONSTER_CODE::DINOSAUR].Monster_Volum_Array, MONSTER_CODE::DINOSAUR, 10, ADinosaur::StaticClass());

		break;
	case EMonsterStage::STAGE3:
		break;
	case EMonsterStage::DEFAULT:
		Set_MonsterVolume_With_Array(Monsterinfo_Map[MONSTER_CODE::SPIDER].Monster_Volum_Array, MONSTER_CODE::SPIDER, 15, ASpider::StaticClass());
		Set_MonsterVolume_With_Array(Monsterinfo_Map[MONSTER_CODE::WORM].Monster_Volum_Array, MONSTER_CODE::WORM, 20, AWorm::StaticClass());
		Set_MonsterVolume_With_Array(Monsterinfo_Map[MONSTER_CODE::BOSS_SPIDER].Monster_Volum_Array, MONSTER_CODE::BOSS_SPIDER, 1, ASpiderBoss::StaticClass());
		Set_MonsterVolume_With_Array(Monsterinfo_Map[MONSTER_CODE::DOG].Monster_Volum_Array, MONSTER_CODE::DOG, 10, ADog::StaticClass());
		Set_MonsterVolume_With_Array(Monsterinfo_Map[MONSTER_CODE::BEAR].Monster_Volum_Array, MONSTER_CODE::BEAR, 10, ABear::StaticClass());
		Set_MonsterVolume_With_Array(Monsterinfo_Map[MONSTER_CODE::DINOSAUR].Monster_Volum_Array, MONSTER_CODE::DINOSAUR, 10, ADinosaur::StaticClass());
		Set_MonsterVolume_With_Array(Monsterinfo_Map[MONSTER_CODE::KING_OF_THEAXE].Monster_Volum_Array, MONSTER_CODE::KING_OF_THEAXE, 1, ABrute::StaticClass());
		break;
	default:
		UE_LOG(LogTemp, Warning, TEXT("(스테이지 정보 누락)준비된 몬스터가 없다!"));
		break;
	}
	//////kind of Monster AND Monster's Maximum size (예비로 최대량을 정해놓고 만들어둠)
	//Set_MonsterVolume_With_Array(Monsterinfo_Map[MONSTER_CODE::SPIDER].Monster_Volum_Array, MONSTER_CODE::SPIDER, 15, ASpider::StaticClass());
	//Set_MonsterVolume_With_Array(Monsterinfo_Map[MONSTER_CODE::WORM].Monster_Volum_Array, MONSTER_CODE::WORM,20, AWorm::StaticClass());
	//Set_MonsterVolume_With_Array(Monsterinfo_Map[MONSTER_CODE::BOSS_SPIDER].Monster_Volum_Array, MONSTER_CODE::BOSS_SPIDER, 1, ASpiderBoss::StaticClass());
	//Set_MonsterVolume_With_Array(Monsterinfo_Map[MONSTER_CODE::DOG].Monster_Volum_Array, MONSTER_CODE::DOG, 10, ADog::StaticClass());
	//Set_MonsterVolume_With_Array(Monsterinfo_Map[MONSTER_CODE::BEAR].Monster_Volum_Array, MONSTER_CODE::BEAR, 10, ABear::StaticClass());
	//Set_MonsterVolume_With_Array(Monsterinfo_Map[MONSTER_CODE::DINOSAUR].Monster_Volum_Array, MONSTER_CODE::DINOSAUR, 10, ADinosaur::StaticClass());
	//Set_MonsterVolume_With_Array(Monsterinfo_Map[MONSTER_CODE::KING_OF_THEAXE].Monster_Volum_Array, MONSTER_CODE::KING_OF_THEAXE, 1, ABrute::StaticClass());
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
	return Monsterinfo_Map;
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


void AObjectPool::ReadyMonster(MONSTER_CODE _MonsterCode, FVector _MonsterPostion)
{
	for (int i_Monster = 0; i_Monster < Monsterinfo_Map[(MONSTER_CODE)_MonsterCode].Monster_Volum_Array.Num(); i_Monster++)
	{
		//bisActive가 false인지 판별 후 넘어감
		if (check_RecycleObject(Monsterinfo_Map[(MONSTER_CODE)_MonsterCode].Monster_Volum_Array[i_Monster]))
		{
			UE_LOG(LogTemp, Warning, TEXT("Monster Recycle"));

			//Active Actor to bisActive make true;
			Monsterinfo_Map[(MONSTER_CODE)_MonsterCode].Monster_Volum_Array[i_Monster]->bisActive = true;

			//Get Monster's init
			//DefaultSpawnArea_Map[(MONSTER_CODE)_MonsterCode].Monster_Volum_Array[i_Monster]->CurrentState는 Init에서 Idle로 만들어줌!
			Monsterinfo_Map[(MONSTER_CODE)_MonsterCode].Monster_Volum_Array[i_Monster]->Init(_MonsterCode, i_Monster);
			Monsterinfo_Map[(MONSTER_CODE)_MonsterCode].Monster_Volum_Array[i_Monster]->SetActorLocation(_MonsterPostion);
			Monsterinfo_Map[(MONSTER_CODE)_MonsterCode].Monster_Volum_Array[i_Monster]->S2C_LocationUpdate(_MonsterPostion);

			//Monster
			SpawnObject_SetActive(Monsterinfo_Map[(MONSTER_CODE)_MonsterCode].Monster_Volum_Array[i_Monster], true);

			//Setting Target
			//DefaultSpawnArea_Map[(MONSTER_CODE)_MonsterCode].Monster_Volum_Array[i_Monster]->FirstTarget();

			//Temporary Struct to Put in ActvieMonster_Array
			FActiveMonsterInfo TempActiveMonsterInfo;
			TempActiveMonsterInfo.MonsterCode = _MonsterCode;
			TempActiveMonsterInfo.MonsterNum = i_Monster;
			TempActiveMonsterInfo.Monster = Monsterinfo_Map[(MONSTER_CODE)_MonsterCode].Monster_Volum_Array[i_Monster];

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

	//Object Position Default SpawnVector Pos
	SpawnPos_Vector = ReadySpawnArea->Bounds.Origin;

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

//사용안함!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void AObjectPool::Timer()
{
	//Timer에 Handle, 사용하는객체(클래스), 반복할 메소드, 반복시간
	//GetWorld()->GetTimerManager().SetTimer(SpawnUpdateTimer, this, &AObjectPool::Recive_SpawnObject_Info, SpawnTime, true, 0);

}

void AObjectPool::Remove_ActiveMonsterArry(int _MonsterCode, int _MonsterNum)
{
	//사망처리 몬스터 배열에서 찾아 빼주는 작업
	for (int i_Num = 0; i_Num < ActiveMonster_Array.Num(); i_Num++)
	{
		if (ActiveMonster_Array[i_Num].MonsterCode == _MonsterCode && ActiveMonster_Array[i_Num].MonsterNum == _MonsterNum)
		{
			ActiveMonster_Array.RemoveAt(i_Num);
		}
	}
}

