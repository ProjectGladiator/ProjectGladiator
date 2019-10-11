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

// �������� ��û
void CharacterManager::Character_Req_Slot()
{
	UINT64 protocol = 0;
	char buf[BUFSIZE];
	memset(buf, 0, sizeof(buf));
	protocol = NetworkClient_main::NetworkManager::GetInstance()->GetUser()->BitPackProtocol(protocol, PROTOCOL_CHRACTER, PROTOCOL_CHARACER_MENU, PROTOCOL_REQ_CHARACTER_SLOT);

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->pack(protocol, buf, 0);
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

	memset(slottemp, 0, sizeof(SlotTemp) * 3);

	// _buf ����
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
		// data�� �ִ� �۾�
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

	StorageManager::GetInstance()->PushData(PCHARACTERDATA_SLOT_INFO, (void*)&ptrdata, datasize);

	return true;
}

// ĳ���� ������û(�г���,�����ڵ�)
void CharacterManager::Character_Req_Character(char * _nick, int _code)
{
	UINT64 protocol = 0;
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
	
	protocol = NetworkClient_main::NetworkManager::GetInstance()->GetUser()->BitPackProtocol(protocol, PROTOCOL_CHRACTER, PROTOCOL_CHARACER_MENU, PROTOCOL_REQ_CHARACTER_CREATE);

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->pack(protocol, buf, size);
}

// ĳ���� ������û
void CharacterManager::Character_Req_Delete(int _index)
{
	UINT64 protocol = 0;
	char buf[BUFSIZE];
	memset(buf, 0, sizeof(buf));

	char* ptr = buf;

	int size = sizeof(int);

	memcpy(ptr, &_index, sizeof(int));

	
	protocol = NetworkClient_main::NetworkManager::GetInstance()->GetUser()->BitPackProtocol(protocol, PROTOCOL_CHRACTER, PROTOCOL_CHARACER_MENU, PROTOCOL_CHARACTER_DELETE);

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->pack(protocol, buf, size);
}

void CharacterManager::Character_Slot_Empty(bool _check)
{
	char buf[BUFSIZE];
	memset(buf, 0, sizeof(buf));
	char* ptr = buf;

	int size = sizeof(bool);

	bool check = _check;

	memcpy(ptr, &check, sizeof(bool));
	StorageManager::GetInstance()->PushData(PCHARACTERDATA_SLOT_INFO, (void*)&buf, size);
}

void CharacterManager::Character_Req_Enter(int _index)
{
	UINT64 protocol = 0;
	char buf[BUFSIZE];
	memset(buf, 0, sizeof(buf));

	char* ptr = buf;

	int size = sizeof(int) + sizeof(int);

	memcpy(ptr, &_index, sizeof(int));

	protocol = NetworkClient_main::NetworkManager::GetInstance()->GetUser()->BitPackProtocol(protocol, PROTOCOL_CHRACTER, PROTOCOL_CHARACER_MENU, PROTOCOL_CHARACTER_ENTER);

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->pack(protocol, buf, size);
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

// ���ӽ� ĳ���� ���� �ޱ�
bool CharacterManager::Character_Recv_Enter(char * _buf)
{
	char ptrdata[BUFSIZE];
	char* ptr = _buf;
	int datasize = 0;

	CharacterInfo charterinfo;
	int nicklen = 0;
	int codelen = 0;
	int channelnum = 0;
	bool check;

	memcpy(&check, ptr, sizeof(bool));
	ptr += sizeof(bool);

	if (check)
	{
		StorageManager::GetInstance()->PushData(PCHARACTERDATA_ENTER_RESULT, (void*)&check, sizeof(bool));

		// ĳ���� �ڵ� ������
		memcpy(&codelen, ptr, sizeof(int));
		ptr += sizeof(int);
		datasize += sizeof(int);

		// ĳ���� �ڵ�
		memcpy(&charterinfo.code, ptr, codelen);
		ptr += codelen;
		datasize += codelen;

		// ���� �ڵ�
		memcpy(&charterinfo.job_code, ptr, sizeof(int));
		ptr += sizeof(int);
		datasize += sizeof(int);

		// �г��� ������
		memcpy(&nicklen, ptr, sizeof(int));
		ptr += sizeof(int);
		datasize += sizeof(int);

		// �г���
		memcpy(charterinfo.nick, ptr, nicklen);
		ptr += nicklen;
		datasize += nicklen;

		// position x, y, z
		memcpy(&charterinfo.xyz, ptr, sizeof(float) * 3);
		ptr += sizeof(float) * 3;
		datasize += sizeof(float) * 3;

		// rotatuin x, y, z
		memcpy(&charterinfo.rot_xyz, ptr, sizeof(float) * 3);
		ptr += sizeof(float) * 3;
		datasize += sizeof(float) * 3;

		memcpy(&channelnum, ptr, sizeof(int));
		ptr += sizeof(int);
		datasize += sizeof(int);

		// ptrdata �ʱ�ȭ
		memset(ptrdata, 0, sizeof(ptrdata));
		char* ptr_packetdata = ptrdata;

		// data�� �ִ� �۾�
		memcpy(ptr_packetdata, &codelen, sizeof(int));
		ptr_packetdata += sizeof(int);

		memcpy(ptr_packetdata, charterinfo.code, codelen);
		ptr_packetdata += codelen;

		memcpy(ptr_packetdata, &charterinfo.job_code, sizeof(int));
		ptr_packetdata += sizeof(int);

		memcpy(ptr_packetdata, &nicklen, sizeof(int));
		ptr_packetdata += sizeof(int);

		memcpy(ptr_packetdata, charterinfo.nick, nicklen);
		ptr_packetdata += nicklen;

		memcpy(ptr_packetdata, &charterinfo.xyz, sizeof(float) * 3);
		ptr_packetdata += sizeof(float) * 3;

		memcpy(ptr_packetdata, &charterinfo.rot_xyz, sizeof(float) * 3);
		ptr_packetdata += sizeof(float) * 3;

		memcpy(ptr_packetdata, &channelnum, sizeof(int));
		ptr_packetdata += sizeof(int);

		StorageManager::GetInstance()->PushData(PCHARACTERDATA_ENTER_INFO, (void*)&ptrdata, datasize);

		return true;
	}
	else
	{
		return false;
	}
}

bool CharacterManager::Character_Recv_Delete(char * _buf)
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

RESULT CharacterManager::CharacterInitRecvResult()
{
	UINT64 protocol = 0;
	UINT64 compartrprotocol = 0;
	UINT64 tempprotocol = 0;
	char buf[BUFSIZE];
	memset(buf, 0, sizeof(buf));
	RESULT result = RT_DEFAULT;
	bool check;

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->BitunPack(protocol, buf);

	compartrprotocol = PROTOCOL_CHARACER_MENU;

	tempprotocol = 0;

	tempprotocol = protocol & compartrprotocol;
	switch (tempprotocol)
	{
	case PROTOCOL_CHARACER_MENU: // �߰�Ʋ �α����̸�
		tempprotocol = protocol & PROTOCOL_SERVER_CHARACTER_MENU_COMPARE;
		switch (tempprotocol)
		{
		case PROTOCOL_CHARACTER_RESULT: // ĳ���� ������û ���
			check = Character_Recv_Create(buf);
			StorageManager::GetInstance()->PushData(PCHARACTERDATA_CREATE_RESULT, (void*)&check, sizeof(bool));
			if (check == true)
			{
				result = RT_CHARACTER_CREATE_SUCCESS;
			}
			else
			{
				result = RT_CHARACTER_CREATE_FAIL;
			}
			break;
		case PROTOCOL_CHARACTER_DELETE_RESULT: // ĳ���� ���� ��û ���
				// ĳ���� ����
			check = Character_Recv_Delete(buf);

			StorageManager::GetInstance()->PushData(PCHARACTERDATA_DELETE_RESULT, (void*)&check, sizeof(bool));

			result = RT_CHARACTER_DELETE;
			break;
		case PROTOCOL_CHARACTER_ENTER_RESULT: // ĳ���� ���� ���� ��û ���
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
		case PROTOCOL_CHARACTER_SLOT_INFO: // ���� ���� ��û ���
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
		default:
			break;
		}
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
		StorageManager::GetInstance()->PushData(PCHARACTERDATA_CREATE_RESULT, (void*)&check, sizeof(bool));
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
