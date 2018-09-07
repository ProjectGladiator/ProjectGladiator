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
	int count;
	int joblen;
	char* jobname;
	int nicklen;
	char* nick;
	int level;
	bool result;

	memcpy(&count, _buf, sizeof(int));
	_buf += sizeof(int);

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
	}
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

//void CharacterManager::CharacterMenuChoice(int _select)
//{
//
//}

void CharacterManager::Character_Exit()
{
	char buf[BUFSIZE];
	memset(buf, 0, sizeof(buf));

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->pack(CLIENT_CHARACTER_EXIT, buf, 0);

}
