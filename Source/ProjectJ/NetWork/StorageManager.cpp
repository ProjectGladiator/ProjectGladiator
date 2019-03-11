#include "StorageManager.h"

StorageManager* StorageManager::Instance = nullptr;

StorageManager::StorageManager()
{
}


StorageManager::~StorageManager()
{
}

//int StorageManager::NProtocoltoDProtocol(int _networkprotocol)
//{
//	switch (_networkprotocol)
//	{
//	case SERVER_JOIN:
//	case SERVER_LOGIN:
//	case SERVER_LOGOUT:
//		return CONFIRM;
//	case SERVER_ID_OVERLAP_CHECK:
//		return PLOGIN_IDOVERLAP_RESULT;
//	case SERVER_JOIN_SUCCESS:
//		return PLOGIN_JOIN_RESULT;
//	case SERVER_LOGIN_SUCCESS:
//		return PLOGIN_LOGIN_RESULT;
//
//	case SERVER_CHARACTER_SLOT_RESULT:
//		return PCHARACTERDATA_SLOT_INFO;
//	case SERVER_CHARACTER_RESULT:
//		return PCHARACTERDATA_CREATE_RESULT;
//	case SERVER_CHARACTER_ENTER_RESULT:
//		return PCHARACTERDATA_ENTER_RESULT;
//	case SERVER_CHARACTER_ENTER_INFO:
//		return PCHARACTERDATA_ENTER_INFO;
//	case SERVER_CHARACTER_DELETE_RESULT:
//		return PCHARACTERDATA_DELETE_RESULT;
//	}
//
//	return -1;
//}

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
	while (DataStorage.empty() != true)
	{
		delete DataStorage.front();
		DataStorage.pop();
	}
}

// 데이터 큐에 넣음
void StorageManager::PushData(int _protocol, void* _data, int _data_size)
{
	PacketData* temppacket = new PacketData();
	char* store_data = new char[_data_size];
	memset(store_data, 0, _data_size);
	memcpy(store_data, _data, _data_size);
	temppacket->data = store_data;
	temppacket->protocol = _protocol;
	temppacket->datasize = _data_size;
	DataStorage.push(temppacket);

	//char log[BUFSIZE];
	//memset(log, 0, sizeof(log));
	//sprintf(log, "Push DataSize : %d store_data size : %d", _data_size, 
	//	strlen(store_data));
	//LogManager::GetInstance()->LogWrite(log);
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

// 캐릭터슬롯정보
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

// 캐릭터 정보 + 채널번호
void StorageManager::ChangeData(void * data, CharacterInfo *& _charinfo, int& _channelnum)
{
	char* ptr = (char*)data;
	
	int len = 0;
	int channelnum = 0;

	memcpy(&len, ptr, sizeof(int));
	ptr += sizeof(int);

	memcpy(_charinfo->code, ptr, len);
	ptr += len;

	memcpy(&_charinfo->job_code, ptr, sizeof(int));
	ptr += sizeof(int);

	memcpy(&len, ptr, sizeof(int));
	ptr += sizeof(int);

	memcpy(_charinfo->nick, ptr, len);
	ptr += len;

	memcpy(_charinfo->xyz, ptr, sizeof(float) * 3);
	ptr += sizeof(float) * 3;

	memcpy(_charinfo->rot_xyz, ptr, sizeof(float) * 3);
	ptr += sizeof(float) * 3;

	memcpy(&channelnum, ptr, sizeof(int));
	ptr += sizeof(int);

	_channelnum = channelnum;
}

// 캐릭터 정보
void StorageManager::ChangeData(void * data, CharacterInfo *& _charinfo)
{
	char* ptr = (char*)data;

	int len = 0;

	memcpy(&len, ptr, sizeof(int));
	ptr += sizeof(int);

	memcpy(_charinfo->code, ptr, len);
	ptr += len;

	memcpy(&_charinfo->job_code, ptr, sizeof(int));
	ptr += sizeof(int);

	memcpy(&len, ptr, sizeof(int));
	ptr += sizeof(int);

	memcpy(_charinfo->nick, ptr, len);
	ptr += len;

	memcpy(_charinfo->xyz, ptr, sizeof(float) * 3);
	ptr += sizeof(float) * 3;

	memcpy(_charinfo->rot_xyz, ptr, sizeof(float) * 3);
	ptr += sizeof(float) * 3;
}

// 이동정보 결과용
void StorageManager::ChangeData(void * data, bool& _result, float*& _posxyz)
{
	char* ptr = (char*)data;

	memcpy(&_result, ptr, sizeof(bool));
	ptr += sizeof(float) * 3;

	memcpy(_posxyz, ptr, sizeof(float) * 3);
	ptr += sizeof(float) * 3;
}

// 플레이어 이동정보 결과용
void StorageManager::ChangeData(void * data, float *& _posxyz, float *& _rotxyz)
{
	char* ptr = (char*)data;

	memcpy(_posxyz, ptr, sizeof(float) * 3);
	ptr += sizeof(float) * 3;

	memcpy(_rotxyz, ptr, sizeof(float) * 3);
	ptr += sizeof(float) * 3;
}

// 다른 플레이어 이동정보 결과용
void StorageManager::ChangeData(void * data, char *& _code, float *& _pos_rot_xyz)
{
	int len = 0;
	char* ptr = (char*)data;

	memcpy(&len, ptr, sizeof(int));
	ptr += sizeof(int);

	memcpy(_code, ptr, len);
	ptr += len;

	memcpy(_pos_rot_xyz, ptr, sizeof(float) * 3);
	ptr += sizeof(float) * 3;
}

// 다른 플레이어 이동정보 결과용
void StorageManager::ChangeData(void * data, OtherCharacterInfo& _otherinfo)
{
	int len = 0;
	char* ptr = (char*)data;

	memcpy(&len, ptr, sizeof(int));
	ptr += sizeof(int);

	memcpy(_otherinfo.code, ptr, len);
	ptr += len;

	memcpy(_otherinfo.xyz, ptr, sizeof(float) * 3);
	ptr += sizeof(float) * 3;
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
