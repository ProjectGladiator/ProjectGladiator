#include "StorageManager.h"

StorageManager* StorageManager::Instance = nullptr;

StorageManager::StorageManager()
{
}


StorageManager::~StorageManager()
{
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

// float형 변환
void StorageManager::ChangeData(void * data, float & _num)
{
	char* ptr = (char*)data;
	memcpy(&_num, ptr, sizeof(float));
}

// 파티방번호, 파티원숫자
void StorageManager::ChangeData(void * data, int & _partyroomnum, int & _partyusercount)
{
	char* ptr = (char*)data;

	memcpy(&_partyroomnum, ptr, sizeof(int));
	ptr += sizeof(int);

	memcpy(&_partyusercount, ptr, sizeof(int));
	ptr += sizeof(int);
}

// 채널 이동 결과
void StorageManager::ChangeData(void* data, bool& _type, int& _count)
{
	char* ptr = (char*)data;

	memcpy(&_type, ptr, sizeof(bool));
	ptr += sizeof(bool);

	if (_type == false)
	{
		return;
	}

	memcpy(&_count, ptr, sizeof(int));
	ptr += sizeof(int);
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

// 다른 플레이어 나간정보용
void StorageManager::ChangeData(void * data, char *& _code)
{
	int len = 0;
	char* ptr = (char*)data;

	memcpy(&len, ptr, sizeof(int));
	ptr += sizeof(int);

	memcpy(_code, ptr, len);
	ptr += len;
}

// 새로운 파티 리더 정보
void StorageManager::ChangeData(void * data, char *& _oldcode, char *& _newcode)
{
	int len = 0;
	char* ptr = (char*)data;

	memcpy(&len, ptr, sizeof(int));
	ptr += sizeof(int);

	memcpy(_oldcode, ptr, len);
	ptr += len;

	memcpy(&len, ptr, sizeof(int));
	ptr += sizeof(int);

	memcpy(_newcode, ptr, len);
	ptr += len;
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

// 채널 정보
void StorageManager::ChangeData(void * data, ChannelInfo*& _channelinfo)
{
	char* ptr = (char*)data;

	float channelnum = 0;
	float channelusercount = 0;

	for (int i = 0; i < 6; i++)
	{
		memcpy(&channelnum, ptr, sizeof(float));
		ptr += sizeof(float);

		memcpy(&channelusercount, ptr, sizeof(float));
		ptr += sizeof(float);

		_channelinfo[i].channelNum = channelnum;
		_channelinfo[i].channelUsercount = channelusercount;

		// 지역 초기화
		channelnum = 0;
		channelusercount = 0;
	}
}

// 파티 초대 정보
void StorageManager::ChangeData(void * data, int & _partyroomnum, char *& _code, char *& _nick)
{
	int codelen = 0;
	int nicklen = 0;
	int partyroomnum = 0;

	char* ptr = (char*)data;

	memcpy(&codelen, ptr, sizeof(int));
	ptr += sizeof(int);

	memcpy(_code, ptr, codelen);
	ptr += codelen;

	memcpy(&nicklen, ptr, sizeof(int));
	ptr += sizeof(int);

	memcpy(_nick, ptr, nicklen);
	ptr += nicklen;

	memcpy(&partyroomnum, ptr, sizeof(int));
	ptr += sizeof(int);

	_partyroomnum = partyroomnum;
}

// 파티 유저 정보
void StorageManager::ChangeData(void * data, PartyUserInfo *& _partyuserinfo)
{
	char* ptr = (char*)data;

	int len = 0;

	memcpy(&len, ptr, sizeof(int));
	ptr += sizeof(int);

	memcpy(_partyuserinfo->code, ptr, len);
	ptr += len;

	memcpy(&_partyuserinfo->job_code, ptr, sizeof(int));
	ptr += sizeof(int);

	memcpy(&len, ptr, sizeof(int));
	ptr += sizeof(int);

	memcpy(_partyuserinfo->nick, ptr, len);
	ptr += len;

	memcpy(&_partyuserinfo->hp, ptr, sizeof(float));
	ptr += sizeof(float);

	memcpy(&_partyuserinfo->mp, ptr, sizeof(float));
	ptr += sizeof(float);

	memcpy(&_partyuserinfo->leader, ptr, sizeof(bool));
	ptr += sizeof(bool);

}

// 강퇴 결과 정보(성공이면 코드있고,실패하면 뒤에 코드가없습니다)
void StorageManager::ChangeData(void * data, bool & _result, char * _code)
{
	int len = 0;
	bool result = false;
	char* ptr = (char*)data;

	memcpy(&result, ptr, sizeof(bool));
	ptr += sizeof(bool);
	
	if (result)
	{
		memcpy(&len, ptr, sizeof(int));
		ptr += sizeof(int);

		memcpy(_code, ptr, len);
		ptr += len;
	}
	_result = result;
}

// 던전 스폰위치 정보
void StorageManager::ChangeData(void * data, char*& _code, float& _pos_x, float& _pos_y, float& _pos_z)
{
	int len = 0;
	char* ptr = (char*)data;

	memcpy(&len, ptr, sizeof(int));
	ptr += sizeof(int);

	memcpy(_code, ptr, len);
	ptr += len;

	memcpy(&_pos_x, ptr, sizeof(float));
	ptr += sizeof(float);

	memcpy(&_pos_y, ptr, sizeof(float));
	ptr += sizeof(float);

	memcpy(&_pos_z, ptr, sizeof(float));
	ptr += sizeof(float);
}

// 몬스터정보 (코드,몬스터숫자,좌표)
void StorageManager::ChangeData(void * data, int & _code, int & _count, float & _pos_x, float & _pos_y, float & _pos_z)
{
	char* ptr = (char*)data;

	memcpy(&_code, ptr, sizeof(int));
	ptr += sizeof(int);

	memcpy(&_count, ptr, sizeof(int));
	ptr += sizeof(int);

	memcpy(&_pos_x, ptr, sizeof(float));
	ptr += sizeof(float);

	memcpy(&_pos_y, ptr, sizeof(float));
	ptr += sizeof(float);

	memcpy(&_pos_z, ptr, sizeof(float));
	ptr += sizeof(float);
}

// 공격정보 (코드,공격번호)
void StorageManager::ChangeData(void * data, char * _code, int _attacknum)
{
	int len = 0;
	char* ptr = (char*)data;

	memcpy(&len, ptr, sizeof(int));
	ptr += sizeof(int);

	memcpy(_code, ptr, len);
	ptr += len;

	memcpy(&_attacknum, ptr, sizeof(int));
	ptr += sizeof(int);
}

// 몬스터 피격정보
void StorageManager::ChangeData(void * data, int & _monstercode, int & _monsternum, int & _damage)
{
	char* ptr = (char*)data;

	memcpy(&_monstercode, ptr, sizeof(int));
	ptr += sizeof(int);

	memcpy(&_monsternum, ptr, sizeof(int));
	ptr += sizeof(int);

	memcpy(&_damage, ptr, sizeof(int));
	ptr += sizeof(int);
}

// 유저 피격정보(결과,데미지,살아있는지)
void StorageManager::ChangeData(void * data, bool & _result, int & _damage, bool & _is_live)
{
	char* ptr = (char*)data;

	memcpy(&_result, ptr, sizeof(bool));
	ptr += sizeof(bool);

	if (_result)
	{
		memcpy(&_damage, ptr, sizeof(int));
		ptr += sizeof(int);

		memcpy(&_is_live, ptr, sizeof(bool));
		ptr += sizeof(bool);
	}
}

// 다른 유저 피격정보(캐릭터코드,데미지,살아있는지)
void StorageManager::ChangeData(void * data, char * _code, int & _damage, bool & _is_live)
{
	int len = 0;
	char* ptr = (char*)data;

	memcpy(&len, ptr, sizeof(int));
	ptr += sizeof(int);

	memcpy(_code, ptr, len);
	ptr += len;

	memcpy(&_damage, ptr, sizeof(int));
	ptr += sizeof(int);

	memcpy(&_is_live, ptr, sizeof(bool));
	ptr += sizeof(bool);
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
