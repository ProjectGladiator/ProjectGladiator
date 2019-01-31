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

// 현재 접속중인 유저리스트 받음
bool InGameManager::InGame_Recv_UserList(char * _buf)
{
	int count;
	char* ptr = _buf;

	memcpy(&count, ptr, sizeof(int));
	ptr += sizeof(int);

	StorageManager::GetInstance()->PushData(SERVER_CHARACTER_ENTER_RESULT, (void*)&count, sizeof(bool));
	StorageManager::GetInstance()->PushData(SERVER_CHARACTER_ENTER_RESULT, (void*)ptr, strlen(ptr));

	return true;
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

		break;
	case SEVER_INGAME_OTHERPLAYER_INFO:

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
