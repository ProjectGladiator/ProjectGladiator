// Fill out your copyright notice in the Description page of Project Settings.

#include "ClientPCInGameState.h"
//클라 헤더
#include "Client/MainMap/MainMapGameMode.h"
#include "Client/MyCharacter/PC/MyCharacter.h"
#include "Client/MainMap/MainMapPlayerController.h"

//서버 헤더
#include "NetWork/StorageManager.h"
#include "NetWork/StorageDataType.h"

ClientPCInGameState::ClientPCInGameState(AMainMapGameMode* _MainMapGameMode)
{
	GLog->Log(FString::Printf(TEXT("클라이언트 플레이어 컨트롤러 인게임 상태 생성자 출력")));
	MainMapGameMode = _MainMapGameMode;
}

ClientPCInGameState::~ClientPCInGameState()
{
	GLog->Log(FString::Printf(TEXT("클라이언트 플레이어 컨트롤러 인게임 상태 소멸자 출력")));
}

void ClientPCInGameState::Tick(float _DeltaTime)
{
	OtherCharacterInfo otherinfo;
	PacketData* Data;
	FVector OtherCharacterLocation; //서버로부터 받은 다른 캐릭터 위치 정보 저장용 벡터
	FRotator OtherCharacterRotation;
	AMyCharacter* OtherCharacter = nullptr; //맵에 접속해 있는 다른 캐릭터
	AMyCharacter* MyCharacter = nullptr; //내가 조종하는 캐릭터
	char TempJumpStartCharacterCode[30];
	char* JumpStartCharacterCode = TempJumpStartCharacterCode;
	char TempAttackStartCharacterCode[30];
	char* AttackStartCharacterCode = TempAttackStartCharacterCode;
	char TempMonsterAttackedUserCharacterCode[30];
	char * MonsterAttackedUsercharacter = TempMonsterAttackedUserCharacterCode;

	bool IsAttackSuccess;
	int ResultDamage;
	bool IsLive;

	if (StorageManager::GetInstance()->GetFront(Data)) //창고매니저 큐에 들어있는 데이터를 가져와서 Data에 담는다.
	{
		switch (Data->protocol) //담아온 Data의 프로토콜을 확인한다.
		{
		case PGAMEDATA_PLAYER_OTHERMOVEINFO:
			//GLog->Log(FString::Printf(TEXT("다른 캐릭터 이동 정보 들어옴")));

			memset(&otherinfo, 0, sizeof(otherinfo));
			StorageManager::GetInstance()->ChangeData(Data->data, otherinfo);
			StorageManager::GetInstance()->PopData();

			//GLog->Log(ANSI_TO_TCHAR(otherinfo.code));

			//GLog->Log(FString::Printf(TEXT("\nOtherCharacter Location X : %f Y : %f Z : %f\n"), otherinfo.xyz[0], otherinfo.xyz[1], otherinfo.xyz[2]));
			if (MainMapGameMode)
			{
				OtherCharacter = MainMapGameMode->GetLoginUser(otherinfo.code);

				if (OtherCharacter)
				{
					OtherCharacterLocation.X = otherinfo.xyz[0];
					OtherCharacterLocation.Y = otherinfo.xyz[1];
					OtherCharacterLocation.Z = otherinfo.xyz[2];

					OtherCharacter->S2C_ControlOtherCharacterMove(OtherCharacterLocation);
				}
				else
				{
					GLog->Log(FString::Printf(TEXT("움직이고 있는 다른 캐릭터를 못 찾음")));
				}
			}
			else
			{
				GLog->Log(FString::Printf(TEXT("메인맵 게임모드가 null")));
			}

			OtherCharacter = nullptr;
			break;
		case PGAMEDATA_PLAYER_OTHERROTATION:
			//GLog->Log(FString::Printf(TEXT("다른 캐릭터 회전 정보 들어옴")));

			memset(&otherinfo, 0, sizeof(otherinfo));

			StorageManager::GetInstance()->ChangeData(Data->data, otherinfo);
			StorageManager::GetInstance()->PopData();

			//GLog->Log(FString::Printf(TEXT("\nOther Character Rotation : Roll : %f Pitch : %f Yaw : %f\n"), otherinfo.xyz[0], otherinfo.xyz[1], otherinfo.xyz[2]));

			if (MainMapGameMode)
			{
				OtherCharacter = MainMapGameMode->GetLoginUser(otherinfo.code);

				if (OtherCharacter)
				{
					OtherCharacterRotation.Roll = otherinfo.xyz[0];
					OtherCharacterRotation.Pitch = otherinfo.xyz[1];
					OtherCharacterRotation.Yaw = otherinfo.xyz[2];

					OtherCharacter->S2C_ControlOtherCharacterRotate(OtherCharacterRotation);
				}
				else
				{
					GLog->Log(FString::Printf(TEXT("회전하고 있는 다른 캐릭터를 못 찾음")));
				}
			}
			else
			{
				GLog->Log(FString::Printf(TEXT("메인맵 게임모드가 null")));
			}

			OtherCharacter = nullptr;
			break;
		case PGAMEDATA_PLAYER_OTHER_START_JUMP: //다른 유저 점프
			memset(TempJumpStartCharacterCode, 0, sizeof(TempJumpStartCharacterCode));

			StorageManager::GetInstance()->ChangeData(Data->data, JumpStartCharacterCode);
			StorageManager::GetInstance()->PopData();

			if (MainMapGameMode)
			{
				OtherCharacter = MainMapGameMode->GetLoginUser(JumpStartCharacterCode);

				if (OtherCharacter)
				{
					OtherCharacter->Jump();
				}
			}
			break;
		case PGAMEDATA_PLAYER_ATTACK:
			memset(TempAttackStartCharacterCode, 0, sizeof(TempAttackStartCharacterCode));

			StorageManager::GetInstance()->ChangeData(Data->data, AttackStartCharacterCode);
			StorageManager::GetInstance()->PopData();

			if (MainMapGameMode)
			{
				OtherCharacter = MainMapGameMode->GetLoginUser(AttackStartCharacterCode);

				if (OtherCharacter)
				{
					OtherCharacter->LeftClickOn();
				}
			}
			break;
		case PGAMEDATA_MONSTER_ATTACKED_THE_USER_RESULT:
			StorageManager::GetInstance()->ChangeData(Data->data, IsAttackSuccess, ResultDamage, IsLive);
			StorageManager::GetInstance()->PopData();

			if (IsAttackSuccess)
			{
				MyCharacter = Cast<AMyCharacter>(MainMapGameMode->GetMainMapPlayerController()->GetPawn());

				if (MyCharacter)
				{
					MyCharacter->MyTakeDamage(ResultDamage);
				}
			}
			break;
		case PGAMEDATA_MONSTER_ATTACKED_THE_OTHERUSER:
			memset(TempMonsterAttackedUserCharacterCode, 0, sizeof(TempMonsterAttackedUserCharacterCode));

			StorageManager::GetInstance()->ChangeData(Data->data, MonsterAttackedUsercharacter, ResultDamage, IsLive);
			StorageManager::GetInstance()->PopData();

			OtherCharacter = MainMapGameMode->GetLoginUser(MonsterAttackedUsercharacter);

			if (OtherCharacter)
			{
				if (IsLive)
				{
					OtherCharacter->MyTakeDamage(ResultDamage);
				}
				else
				{
					OtherCharacter->MyTakeDamage(ResultDamage, false);
				}
			}

			break;
		}
	}
}
