#include "InGameManager.h"
#include "NetworkManager.h"
#include "LogManager.h"

InGameManager* InGameManager::Instance = nullptr;

InGameManager::InGameManager()
{

}

InGameManager::~InGameManager()
{

}

void InGameManager::CreateInstance()
{
	if (Instance == nullptr)
	{
		Instance = new InGameManager();
	}
}

InGameManager * InGameManager::GetInstance()
{
	return Instance;
}

void InGameManager::DestroyInstance()
{
	if (Instance != nullptr)
	{
		delete Instance;
		Instance = nullptr;
	}
}

bool InGameManager::MangerInitialize()
{
	return true;
}

void InGameManager::EndManager()
{

}

// 현재 접속중인 유저리스트 요청
void InGameManager::InGame_Req_UserList()
{
	char buf[BUFSIZE];
	memset(buf, 0, sizeof(buf));

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->pack(CLIENT_INGAME_OTHERPLAYERLIST, buf, 0);

}
// 이동요청
void InGameManager::InGame_Req_Move(float _px, float _py, float _pz, float _rx, float _ry, float _rz)
{
	char buf[BUFSIZE];
	char* ptr = buf;
	int datasize = 0;
	memset(buf, 0, sizeof(buf));

	memcpy(ptr, &_px, sizeof(float));
	datasize += sizeof(float);
	ptr += sizeof(float);

	memcpy(ptr, &_py, sizeof(float));
	datasize += sizeof(float);
	ptr += sizeof(float);

	memcpy(ptr, &_pz, sizeof(float));
	datasize += sizeof(float);

	memcpy(ptr, &_rx, sizeof(float));
	datasize += sizeof(float);

	memcpy(ptr, &_ry, sizeof(float));
	datasize += sizeof(float);

	memcpy(ptr, &_rz, sizeof(float));
	datasize += sizeof(float);
	ptr += sizeof(float);

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->pack(CLIENT_INGAME_MOVE, buf, datasize);
}

// 현재 접속중인 유저리스트 받음
bool InGameManager::InGame_Recv_UserList(char * _buf)
{
	int count;
	char* ptr_buf = _buf;
   
	char data[BUFSIZE];
	char* ptr_data = data;
	int size = 0;
	int jobcode;
	int len;
	char nick[20];
	float xyz[3];
	float rot_xyz[3];

	memcpy(&count, ptr_buf, sizeof(int));
	ptr_buf += sizeof(int);

	StorageManager::GetInstance()->PushData(PGAMEDATA_USERLIST_COUNT, (void*)&count, sizeof(int));



	for (int i = 0; i < count; i++)
	{
		memset(data, 0, sizeof(data));
		memset(nick, 0, sizeof(nick));
		ptr_data = data;
		size = 0;
		len = 0;
		jobcode = 0;

		// 캐릭터 직업코드
		memcpy(&jobcode, ptr_buf, sizeof(int));
		ptr_buf += sizeof(int);
		size += sizeof(int);
		memcpy(ptr_data, &jobcode, sizeof(int));
		ptr_data += sizeof(int);

		// 닉네임 사이즈
		memcpy(&len, ptr_buf, sizeof(int));
		ptr_buf += sizeof(int);
		size += sizeof(int);
		memcpy(ptr_data, &len, sizeof(int));
		ptr_data += sizeof(int);

		// 닉네임
		memcpy(nick, ptr_buf, len);
		ptr_buf += len;
		size += len;
		memcpy(ptr_data, nick, len);
		ptr_data += len;

		// position x, y, z
		memcpy(xyz, ptr_buf, sizeof(float) * 3);
		ptr_buf += sizeof(float) * 3;
		size += sizeof(float) * 3;
		memcpy(ptr_data, xyz, sizeof(float) * 3);
		ptr_data += sizeof(float) * 3;

		// rotation x, y, z
		memcpy(rot_xyz, ptr_buf, sizeof(float) * 3);
		ptr_buf += sizeof(float) * 3;
		size += sizeof(float) * 3;
		memcpy(ptr_data, rot_xyz, sizeof(float) * 3);
		ptr_data += sizeof(float) * 3;

		StorageManager::GetInstance()->PushData(PGAMEDATA_USERLIST_USER, data, size);
	}

	return true;
}

// 플레이어 이동 결과 
bool InGameManager::InGame_Recv_MoveResult(char * _buf)
{
	bool result;
	char* ptr_buf = _buf;

	char data[BUFSIZE];
	char* ptr_data = data;
	int size = 0;
	int len;
	float xyz[3];
	float rot_xyz[3];

	// 이동결과
	memcpy(&result, ptr_buf, sizeof(bool));
	ptr_buf += sizeof(bool);
	size += sizeof(bool);
	memcpy(ptr_data, &result, sizeof(bool));
	ptr_data += sizeof(bool);

	if (result)
	{
		// 닉네임 사이즈
		memcpy(&len, ptr_buf, sizeof(int));
		ptr_buf += sizeof(int);

		// 닉네임
		ptr_buf += len;

		// position x, y, z
		memcpy(xyz, ptr_buf, sizeof(float) * 3);
		ptr_buf += sizeof(float) * 3;
		size += sizeof(float) * 3;
		memcpy(ptr_data, xyz, sizeof(float) * 3);
		ptr_data += sizeof(float) * 3;

		// rotation x, y, z
		memcpy(rot_xyz, ptr_buf, sizeof(float) * 3);
		ptr_buf += sizeof(float) * 3;
		size += sizeof(float) * 3;
		memcpy(ptr_data, rot_xyz, sizeof(float) * 3);
		ptr_data += sizeof(float) * 3;
	}
	else
	{
		// 닉네임 사이즈
		memcpy(&len, ptr_buf, sizeof(int));
		ptr_buf += sizeof(int);

		// 닉네임
		ptr_buf += len;

		// position x, y, z
		memcpy(xyz, ptr_buf, sizeof(float) * 3);
		ptr_buf += sizeof(float) * 3;
		size += sizeof(float) * 3;
		memcpy(ptr_data, xyz, sizeof(float) * 3);
		ptr_data += sizeof(float) * 3;

		// rotation x, y, z
		memcpy(rot_xyz, ptr_buf, sizeof(float) * 3);
		ptr_buf += sizeof(float) * 3;
		size += sizeof(float) * 3;
		memcpy(ptr_data, rot_xyz, sizeof(float) * 3);
		ptr_data += sizeof(float) * 3;
	}

	StorageManager::GetInstance()->PushData(PGAMEDATA_PLAYER_MOVE_RESULT, data, size);

	return result;
}

// 다른 유저 이동 정보
void InGameManager::InGame_Recv_OtherUserMoveInfo(char * _buf)
{
	//bool result;
	char* ptr_buf = _buf;

	char data[BUFSIZE];
	char nick[NICKNAMESIZE];
	char* ptr_data = data;
	int size = 0;
	int len;
	float xyz[3];
	float rot_xyz[3];

	// 닉네임 사이즈
	memcpy(&len, ptr_buf, sizeof(int));
	ptr_buf += sizeof(int);
	size += sizeof(int);
	memcpy(ptr_data, &len, sizeof(int));
	ptr_data += sizeof(int);

	// 닉네임
	memcpy(nick, ptr_buf, len);
	ptr_buf += len;
	size += len;
	memcpy(ptr_data, nick, len);
	ptr_data += len;

	// position x, y, z
	memcpy(xyz, ptr_buf, sizeof(float) * 3);
	ptr_buf += sizeof(float) * 3;
	size += sizeof(float) * 3;
	memcpy(ptr_data, xyz, sizeof(float) * 3);
	ptr_data += sizeof(float) * 3;

	// rotation x, y, z
	memcpy(rot_xyz, ptr_buf, sizeof(float) * 3);
	ptr_buf += sizeof(float) * 3;
	size += sizeof(float) * 3;
	memcpy(ptr_data, rot_xyz, sizeof(float) * 3);
	ptr_data += sizeof(float) * 3;

	StorageManager::GetInstance()->PushData(PGAMEDATA_PLAYER_OTHERMOVEINFO, data, size);
}

RESULT InGameManager::InGameInitRecvResult(User * _user)
{
	PROTOCOL protocol;
	char buf[BUFSIZE];

	RESULT result;
	bool check;

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->unPack(&protocol, buf);

	switch (protocol)
	{
	case SEVER_INGAME_MOVE_RESULT:
		check = InGame_Recv_MoveResult(buf);
		if (check)	// 이동 성공
		{

		}
		else		// 이동 실패
		{

		}
		break;
	case SEVER_INGAME_OTHERPLAYER_INFO:
		InGame_Recv_OtherUserMoveInfo(buf);
		break;
	case SEVER_INGAME_OTHERPLAYERLIST_RESULT:
		check = InGame_Recv_UserList(buf);
		if (check)
		{
			result = RT_INGAME_OTHERPLAYER_LIST;
		}
		break;
	default:
		break;
	}

	return result;
}
