#ifndef _STORAGE_MANAGER_H_
#define _STORAGE_MANAGER_H_

#include "global.h"
#include "DataProtocol.h"
#include "StorageDataType.h"
#include "LogManager.h"
#include <queue>

using namespace std;
using namespace DataProtocol;

struct PacketData
{
	int protocol;
	char* data;
	int datasize;

	~PacketData()
	{
		if (datasize == 1)
		{
			delete data;
		}
		else
		{
			delete[] data;
		}

	}
};

class StorageManager
{
private:
	queue<PacketData*> DataStorage;
	//queue<PacketData*>::iterator save;

	static StorageManager* Instance;

	StorageManager();
	~StorageManager();

	//int NProtocoltoDProtocol(int _networkprotocol);
public:
	static void CreateInstance();
	static StorageManager* GetInstance();
	static void DestroyInstance();

	bool InitializeManager();
	void EndManager();

	void PushData(int _protocol, void* _data, int _data_size);
	bool GetFront(PacketData*& data);
	// bool형 변환
	void ChangeData(void* data, bool& type);
	// int형 변환
	void ChangeData(void* data, int& _count);
	// float형 변환
	void ChangeData(void* data, float& _num);
	// 파티방번호, 파티원숫자
	void ChangeData(void* data, int& _partyroomnum,int& _partyusercount);
	// 채널 이동 결과
	void ChangeData(void* data, bool& _type, int& _count);
	// 캐릭터슬롯정보
	void ChangeData(void* data, bool& _type, int& _count, CharacterSlot*& _slot);
	// 캐릭터 정보 + 채널번호
	void ChangeData(void* data, CharacterInfo*& _charinfo, int& _channelnum);
	// 캐릭터 정보
	void ChangeData(void* data, CharacterInfo*& _charinfo);
	// 이동정보 결과용
	void ChangeData(void* data, bool& _result, float*& _posxyz);
	// 플레이어 이동정보 결과용
	void ChangeData(void* data, float*& _posxyz, float*& _rotxyz);
	// 다른 플레이어 이동정보 결과용
	void ChangeData(void* data, char*& _code, float*& _pos_rot_xyz);
	// 다른 플레이어 나간정보용
	void ChangeData(void* data, char*& _code);
	// 새로운 파티 리더 정보
	void ChangeData(void* data, char*& _oldcode, char*& _newcode);
	// 다른 플레이어 이동정보 결과용
	void ChangeData(void* data, OtherCharacterInfo& _otherinfo);
	// 채널 정보
	void ChangeData(void* data, ChannelInfo*& _channelinfo);
	// 파티 초대 정보
	void ChangeData(void* data, int& _partyroomnum, char*& _code, char*& _nick);
	// 파티 유저 정보
	void ChangeData(void* data, PartyUserInfo*& _partyuserinfo);
	// 강퇴 결과 정보,파티 리더 위임 결과 정보(성공이면 코드있고,실패하면 뒤에 코드가없습니다)
	void ChangeData(void* data, bool& _result, char* _code);
	// 던전 스폰위치 정보, 스테이지 스폰위치 정보
	void ChangeData(void* data, char*& _code,float& _pos_x, float& _pos_y, float& _pos_z);
	// 몬스터정보 (코드,몬스터숫자,좌표)
	void ChangeData(void* data, int& _code, int& _count, float& _pos_x, float& _pos_y, float& _pos_z);
	// 공격정보 (코드,공격번호)
	void ChangeData(void* data, char* _code, int _attacknum);
	// 몬스터 피격정보 (몬스터코드, 몬스터숫자,데미지)
	void ChangeData(void* data, int& _monstercode, int& _monsternum, int& _damage);
	// 유저 피격정보(결과,데미지,살아있는지)
	void ChangeData(void* data, bool& _result, int& _damage, bool& _is_live);
	// 다른 유저 피격정보(캐릭터코드,데미지,살아있는지)
	void ChangeData(void* data, char* _code, int& _damage, bool& _is_live);


	bool PopData();
};

#endif