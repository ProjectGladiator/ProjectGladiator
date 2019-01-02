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

bool CharacterManager::Character_Recv_Slot(char * _buf)
{
	//char* ptrdata = nullptr;
	char ptrdata[BUFSIZE];
	char* ptrbuf = _buf;

	struct SlotTemp
	{
		int temp_joblen;
		char temp_jobname[255];
		int temp_nicklen;
		char temp_nick[255];
		int temp_level;
		int temp_job_code;
	}slottemp[3];

	memset(slottemp, 0, sizeof(slottemp));

	// _buf 길이
	int datasize = 0;

	bool check = true;
	int count = 0;

	memcpy(&check, ptrbuf, sizeof(bool));
	ptrbuf += sizeof(bool);
	datasize += sizeof(bool);

	if (check == false)
	{
		return false;
	}

	memcpy(&count, ptrbuf, sizeof(int));
	ptrbuf += sizeof(int);
	datasize += sizeof(int);

	for (int i = 0; i < count; i++)
	{
		memcpy(&slottemp[i].temp_joblen, ptrbuf, sizeof(int));
		ptrbuf += sizeof(int);
		datasize += sizeof(int);

		memcpy(slottemp[i].temp_jobname, ptrbuf, slottemp[i].temp_joblen);
		ptrbuf += slottemp[i].temp_joblen;
		datasize += slottemp[i].temp_joblen;;

		memcpy(&slottemp[i].temp_level, ptrbuf, sizeof(int));
		ptrbuf += sizeof(int);
		datasize += sizeof(int);

		memcpy(&slottemp[i].temp_nicklen, ptrbuf, sizeof(int));
		ptrbuf += sizeof(int);
		datasize += sizeof(int);

		memcpy(slottemp[i].temp_nick, ptrbuf, slottemp[i].temp_nicklen);
		ptrbuf += slottemp[i].temp_nicklen;
		datasize += slottemp[i].temp_nicklen;

		memcpy(&slottemp[i].temp_job_code, ptrbuf, sizeof(int));
		ptrbuf += sizeof(int);
		datasize += sizeof(int);
	}

	//ptrdata = new char[datasize];
	memset(ptrdata, 0,sizeof(ptrdata));
	char* ptr_packetdata = ptrdata;

	memcpy(ptr_packetdata, &check, sizeof(bool));
	ptr_packetdata += sizeof(bool);

	memcpy(ptr_packetdata, &count, sizeof(int));
	ptr_packetdata += sizeof(int);

	for (int i = 0; i < count; i++)
	{
		// data에 넣는 작업
		memcpy(ptr_packetdata, &slottemp[i].temp_joblen, sizeof(int));
		ptr_packetdata += sizeof(int);

		memcpy(ptr_packetdata, slottemp[i].temp_jobname, slottemp[i].temp_joblen);
		ptr_packetdata += slottemp[i].temp_joblen;

		memcpy(ptr_packetdata, &slottemp[i].temp_level, sizeof(int));
		ptr_packetdata += sizeof(int);

		memcpy(ptr_packetdata, &slottemp[i].temp_nicklen, sizeof(int));
		ptr_packetdata += sizeof(int);

		memcpy(ptr_packetdata, slottemp[i].temp_nick, slottemp[i].temp_nicklen);
		ptr_packetdata += slottemp[i].temp_nicklen;

		memcpy(ptr_packetdata, &slottemp[i].temp_job_code, sizeof(int));
		ptr_packetdata += sizeof(int);
	}

	StorageManager::GetInstance()->PushData(SERVER_CHARACTER_SLOT_RESULT, (void*)&ptrdata, datasize);

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

void CharacterManager::Character_Slot_Empty(bool _check)
{
	char buf[BUFSIZE];
	memset(buf, 0, sizeof(buf));
	char* ptr = buf;

	int size = sizeof(bool);

	bool check = _check;

	memcpy(ptr, &check, sizeof(bool));
	StorageManager::GetInstance()->PushData(SERVER_CHARACTER_SLOT_RESULT, (void*)&buf, size);

	LogManager::GetInstance()->SetTime();
	LogManager::GetInstance()->LogWrite(buf);
	
}

void CharacterManager::Character_Req_Enter(int _index)
{
	char buf[BUFSIZE];
	memset(buf, 0, sizeof(buf));

	char* ptr = buf;

	int size = sizeof(int) + sizeof(int);

	memcpy(ptr, &_index, sizeof(int));

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->pack(CLIENT_REQ_CHARACTER, buf, size);
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
	char* ptr = _buf;

	memcpy(&check, ptr, sizeof(bool));
	ptr += sizeof(bool);

	if (check)
	{
		StorageManager::GetInstance()->PushData(SERVER_CHARACTER_ENTER_RESULT, (void*)&check, sizeof(bool));
		StorageManager::GetInstance()->PushData(SERVER_CHARACTER_ENTER_INFO, (void*)ptr, strlen(ptr));
		return true;
	}
	else
	{
		return false;
	}
}

RESULT CharacterManager::CharacterInitRecvResult()
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
			check = Character_Recv_Slot(buf);
			result = RT_CHARACTER_SLOTRESULT;
		}
		else
		{
			Character_Slot_Empty(check);
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
