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
		// ĳ���� ������ ����
		return true;
	}
	else
	{
		// ĳ���� ������ ����
		return false;
	}
}

bool CharacterManager::Character_Recv_Slot(char * _buf)
{
	char* ptrdata = nullptr;
	char* ptrbuf = _buf;

	// _buf ����
	int datasize = strlen(_buf);

	bool check = true;
	memcpy(&check, ptrbuf, sizeof(bool));
	ptrbuf += sizeof(bool);

	if (check == false)
	{
		return false;
	}

	ptrdata = new char[datasize];
	char* ptr_packetdata = ptrdata;

	int count = 0;
	int joblen = 0;
	char jobname[255];
	int nicklen = 0;
	char nick[255];
	int level;

	memcpy(&count, ptrbuf, sizeof(int));
	ptrbuf += sizeof(int);

	memcpy(ptr_packetdata, &check, sizeof(bool));
	ptr_packetdata += sizeof(bool);

	memcpy(ptr_packetdata, &count, sizeof(int));
	ptr_packetdata += sizeof(int);

	for (int i = 0; i < count; i++)
	{
		memcpy(&joblen, ptrbuf, sizeof(int));
		ptrbuf += sizeof(int);

		memcpy(jobname, ptrbuf, joblen);
		ptrbuf += joblen;

		memcpy(&level, ptrbuf, sizeof(int));
		ptrbuf += sizeof(int);

		memcpy(&nicklen, ptrbuf, sizeof(int));
		ptrbuf += sizeof(int);

		memcpy(nick, ptrbuf, nicklen);
		ptrbuf += nicklen;

		// data�� �ִ� �۾�
		memcpy(ptr_packetdata, &joblen, sizeof(int));
		ptr_packetdata += sizeof(int);

		memcpy(ptr_packetdata, jobname, joblen);
		ptr_packetdata += joblen;

		memcpy(ptr_packetdata, &level, sizeof(int));
		ptr_packetdata += sizeof(int);

		memcpy(ptr_packetdata, &nicklen, sizeof(int));
		ptr_packetdata += sizeof(int);

		memcpy(ptr_packetdata, nick, nicklen);
		ptr_packetdata += nicklen;
	}

	StorageManager::GetInstance()->PushData(SERVER_CHARACTER_SLOT_RESULT, (void*)&ptr_packetdata, datasize);

	return true;
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

void CharacterManager::Character_Choice(int _select)
{
	char buf[BUFSIZE];
	memset(buf, 0, sizeof(buf));
	char* ptr = buf;

	int size = sizeof(int);

	memcpy(ptr, &_select, sizeof(int));

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->pack(CLIENT_CHARACTER_ENTER, buf, 0);

}

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
		// ĳ���� ���� ����
		return true;
	}
	else
	{
		// ĳ���� ���� ����
		return false;
	}
}

bool CharacterManager::Character_Recv_Enter(char * _buf)
{
	bool check;

	memcpy(&check, _buf, sizeof(bool));

	if (check)
	{
		// ĳ���� ���� ����
		return true;
	}
	else
	{
		// ĳ���� ���� ����
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
		if (check == true)
		{
			int size = strlen(buf);
			check = Character_Recv_Slot(buf);
			result = RT_CHARACTER_SLOTRESULT;
		}
		else
		{
			check = false;
			StorageManager::GetInstance()->PushData(protocol, (void*)&check, sizeof(bool));
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
		// ĳ���� ����
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
		StorageManager::GetInstance()->PushData(protocol, (void*)&check, sizeof(bool));
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
