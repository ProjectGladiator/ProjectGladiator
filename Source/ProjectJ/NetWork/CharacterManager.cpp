#include"CharacterManager.h"
#include "NetworkManager.h"
#include "LogManager.h"

CharacterManager* CharacterManager::Instance = nullptr;

CharacterManager::CharacterManager()
{

}

CharacterManager::~CharacterManager()
{

}

void CharacterManager::CreateInstance()
{
	if (Instance == nullptr)
	{
		Instance = new CharacterManager();
	}
}

CharacterManager* CharacterManager::GetInstance()
{
	return Instance;
}

void CharacterManager::DestroyInstance()
{
	if (Instance != nullptr)
	{
		delete Instance;
		Instance = nullptr;
	}
}

bool CharacterManager::InitializeManager()
{
	return true;
}

void CharacterManager::EndManager()
{

}

void CharacterManager::Character_Req_Slot()
{
	char buf[BUFSIZE];
	memset(buf, 0, sizeof(buf));

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->pack(CLIENT_REQ_CHARACTER_SLOT, buf, 0);

}

bool CharacterManager::Character_Slot(char* _buf)
{
	bool check;

	memcpy(&check, _buf, sizeof(bool));

	if (check)
	{
		// 캐릭터 슬롯이 있음
		return true;
	}
	else
	{
		// 캐릭터 슬롯이 없음
		return false;
	}
}

void CharacterManager::Character_Recv_Slot(char * _buf)
{
	char data[BUFSIZE];

	memset(data, 0, sizeof(data));

	int count;
	int joblen;
	char* jobname = nullptr;
	int nicklen;
	char* nick = nullptr;
	int level;

	memset(jobname, 0, sizeof(jobname));
	memset(nick, 0, sizeof(nick));

	int size;

	bool check = true;

	char* ptr = data;

	memcpy(&count, _buf, sizeof(int));
	_buf += sizeof(int);

	memcpy(ptr, &check, sizeof(bool));
	ptr += sizeof(bool);

	memcpy(ptr, &count, sizeof(int));
	ptr += sizeof(int);

	size = sizeof(bool) + sizeof(int);

	for (int i = 0; i < count; i++)
	{
		memcpy(&joblen, _buf, sizeof(int));
		_buf += sizeof(int);

		memcpy(jobname, _buf, joblen);
		_buf += joblen;

		memcpy(&level, _buf, sizeof(int));
		_buf += sizeof(int);

		memcpy(&nicklen, _buf, sizeof(int));
		_buf += sizeof(int);

		memcpy(nick, _buf, nicklen);
		_buf += nicklen;

		// data에 넣는 작업

		memcpy(ptr, &joblen, sizeof(int));
		ptr += sizeof(int);
		size += sizeof(int);

		memcpy(ptr, jobname, joblen);
		ptr += joblen;
		size += joblen;

		memcpy(ptr, &level, sizeof(int));
		ptr += sizeof(int);
		size += sizeof(int);

		memcpy(ptr, &nicklen, sizeof(int));
		ptr += sizeof(int);
		size += sizeof(int);

		memcpy(ptr, nick, nicklen);
		ptr += nicklen;
		size += nicklen;

	}
	StorageManager::GetInstance()->PushData(SERVER_CHARACTER_SLOT_RESULT, (void*)data, size);

}

void CharacterManager::Character_Req_New_Character()
{
	char buf[BUFSIZE];
	memset(buf, 0, sizeof(buf));

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->pack(CLIENT_NEW_CHARACTER_MENU, buf, 0);

}

void CharacterManager::Character_Req_Character(char * _nick, int _code)
{
	char buf[BUFSIZE];
	memset(buf, 0, sizeof(buf));

	int nicklen = strlen(_nick) + 1;
	char* ptr = buf;

	int size = sizeof(int) + nicklen + sizeof(int);

	memcpy(ptr, &nicklen, sizeof(int));
	ptr += sizeof(int);

	memcpy(ptr, _nick, nicklen);
	ptr += nicklen;

	memcpy(ptr, &_code, sizeof(int));

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->pack(CLIENT_REQ_CHARACTER, buf, size);
}

//void CharacterManager::Character_Choice(int _select)
//{
//
//}

void CharacterManager::Character_Exit()
{
	char buf[BUFSIZE];
	memset(buf, 0, sizeof(buf));

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->pack(CLIENT_CHARACTER_EXIT, buf, 0);

}

bool CharacterManager::Character_Recv_Create(char * _buf)
{
	bool check;

	memcpy(&check, _buf, sizeof(bool));

	if (check)
	{
		// 캐릭터 생성 성공
		return true;
	}
	else
	{
		// 캐릭터 생성 실패
		return false;
	}
}

bool CharacterManager::Character_Recv_Enter(char * _buf)
{
	bool check;

	memcpy(&check, _buf, sizeof(bool));

	if (check)
	{
		// 캐릭터 접속 성공
		return true;
	}
	else
	{
		// 캐릭터 접속 실패
		return false;
	}
}

RESULT CharacterManager::CharacterInirRecvResult()
{
	PROTOCOL protocol;
	char buf[BUFSIZE];

	RESULT result;
	bool check;

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->unPack(&protocol, buf);

	switch (protocol)
	{
	case SERVER_CHARACTER_SLOT_RESULT:
		check = Character_Slot(buf);
		if (check)
		{
			Character_Recv_Slot(buf);
			result = RT_CHARACTER_SLOTRESULT;
		}
		else
		{
			StorageManager::GetInstance()->PushData(protocol, (void*)check, sizeof(bool));
			result = RT_CHARACTER_SLOTRESULT;
		}
		
		break;
	case SERVER_CHARACTER_ENTER_RESULT:
		check = Character_Recv_Enter(buf);
		if (check)
		{
			result = RT_CHARACTER_ENTERGAME_SUCCESS;
		}
		else
		{
			result = RT_CHARACTER_ENTERGAME_FAIL;
		}
		break;
	case SERVER_CHARACTER_DELETE_RESULT:
		// 캐릭터 삭제
		result = RT_CHARACTER_DELETE;
		break;
	case SERVER_CHARACTER_MENU:
		result = RT_CHARACTER_ENTERCREATE;
		break;
	default:
		break;
	}

	return result;
}

RESULT CharacterManager::CharacterNewRecvResult()
{
	PROTOCOL protocol;
	char buf[BUFSIZE];

	RESULT result;
	bool check;

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->unPack(&protocol, buf);

	switch (protocol)
	{
	case SERVER_CHARACTER_RESULT:
		check = Character_Recv_Create(buf);
		StorageManager::GetInstance()->PushData(protocol, (void*)check, sizeof(bool));
		if (check == true)
		{
			result = RT_CHARACTER_CREATE_SUCCESS;
		}
		else
		{
			result = RT_CHARACTER_CREATE_FAIL;
		}
		break;
	case SERVER_CHARACTER_EXIT_RESULT:
		result = RT_CHARACTER_EXIT;
		break;
	default:
		break;
	}

	return result;
}
