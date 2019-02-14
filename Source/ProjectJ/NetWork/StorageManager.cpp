#include "StorageManager.h"

StorageManager* StorageManager::Instance = nullptr;

StorageManager::StorageManager()
{
}


StorageManager::~StorageManager()
{
}

int StorageManager::NProtocoltoDProtocol(int _networkprotocol)
{
	switch (_networkprotocol)
	{
	case SERVER_JOIN:
	case SERVER_LOGIN:
	case SERVER_LOGOUT:
		return CONFIRM;
	case SERVER_ID_OVERLAP_CHECK:
		return PLOGIN_IDOVERLAP_RESULT;
	case SERVER_JOIN_SUCCESS:
		return PLOGIN_JOIN_RESULT;
	case SERVER_LOGIN_SUCCESS:
		return PLOGIN_LOGIN_RESULT;

	case SERVER_CHARACTER_SLOT_RESULT:
		return PCHARACTERDATA_SLOT_INFO;
	case SERVER_CHARACTER_RESULT:
		return PCHARACTERDATA_CREATE_RESULT;
	case SERVER_CHARACTER_ENTER_RESULT:
		return PCHARACTERDATA_ENTER_RESULT;
	case SERVER_CHARACTER_ENTER_INFO:
		return PCHARACTERDATA_ENTER_INFO;
	case SERVER_CHARACTER_DELETE_RESULT:
		return PCHARACTERDATA_DELETE_RESULT;
	}

	return -1;
}

void StorageManager::CreateInstance()
{
	if (Instance == nullptr)
	{
		Instance = new StorageManager();
	}
}

StorageManager* StorageManager::GetInstance()
{
	return Instance;
}

void StorageManager::DestroyInstance()
{
	if (Instance != nullptr)
	{
		delete Instance;
		Instance = nullptr;
	}
}

bool StorageManager::InitializeManager()
{
	return true;
}

void StorageManager::EndManager()
{
}

// 데이터 큐에 넣음
void StorageManager::PushData(PROTOCOL p, void * data, int data_size)
{
	PacketData* temppacket = new PacketData();
	char* store_data = new char[data_size];
	memcpy(store_data, data, data_size);
	temppacket->data = store_data;
	temppacket->protocol = NProtocoltoDProtocol(p);
	temppacket->datasize = data_size;
	DataStorage.push(temppacket);
}

// 큐의 앞부분 반환
bool StorageManager::GetFront(PacketData *& data)
{
	if (DataStorage.empty())
	{
		return false;
	}

	data = DataStorage.front();
	return true;
}

// void 형 데이터 실제 데이터로 변환
void StorageManager::ChangeData(void* data, bool& type)
{
	char* ptr = (char*)data;
	memcpy(&type, ptr, sizeof(bool));
}

void StorageManager::ChangeData(void * data, int &_count)
{
	char* ptr = (char*)data;
	memcpy(&_count, ptr, sizeof(int));
}

// 수정중
void StorageManager::ChangeData(void* data, bool& _type, int& _count, CharacterSlot*& _slot)
{
 	char* ptr = (char*)data;
	
	bool check;
	int count;
	int joblen;
	char jobname[255];
	int level;
	int nicklen;
	char nick[255];
	int charactercode;

	memcpy(&check, ptr, sizeof(bool));
	ptr += sizeof(bool);
	_type = check;

	if (check == false)
	{
		return;
	}

	memcpy(&count, ptr, sizeof(int));
	ptr += sizeof(int);
	_count = count;
	

	for (int i = 0; i < count; i++)
	{
		memcpy(&joblen, ptr, sizeof(int));
		ptr += sizeof(int);

		memcpy(jobname, ptr, joblen);
		ptr += joblen;

		memcpy(&level, ptr, sizeof(int));
		ptr += sizeof(int);

		memcpy(&nicklen, ptr, sizeof(int));
		ptr += sizeof(int);

		memcpy(nick, ptr, nicklen);
		ptr += nicklen;

		memcpy(&charactercode, ptr, sizeof(int));
		ptr += sizeof(int);

		memcpy(_slot[i].name, jobname, joblen);
		memcpy(_slot[i].nick, nick, nicklen);
		_slot[i].level = level;
		_slot[i].charavercode = charactercode;

		// 지역 초기화
		memset(&joblen, 0, sizeof(int));
		memset(jobname, 0, sizeof(jobname));
		memset(&level, 0, sizeof(int));
		memset(&nicklen, 0, sizeof(int));
		memset(nick, 0, sizeof(nick));
		memset(&charactercode, 0, sizeof(int));
		//
	}
}

void StorageManager::ChangeData(void * data, int _count, CharacterInfo *& _charinfo)
{
	char* ptr = (char*)data;
	
	int nicksize = 0;
		
	for (int i = 0; i < _count; i++)
	{
		memcpy(&_charinfo[i].character_code, ptr, sizeof(int));
		ptr += sizeof(int);

		memcpy(&nicksize, ptr, sizeof(int));
		ptr += sizeof(int);

		memcpy(_charinfo[i].nick, ptr, nicksize);
		ptr += nicksize;

		memcpy(&_charinfo[i].x, ptr, sizeof(float));
		ptr += sizeof(float);
		memcpy(&_charinfo[i].y, ptr, sizeof(float));
		ptr += sizeof(float);
		memcpy(&_charinfo[i].z, ptr, sizeof(float));
		ptr += sizeof(float);
	}
}

// Front 삭제
bool StorageManager::PopData()
{
	if (DataStorage.empty())
	{
		return false;
	}

	delete DataStorage.front();
	DataStorage.pop();
	return true;
}
