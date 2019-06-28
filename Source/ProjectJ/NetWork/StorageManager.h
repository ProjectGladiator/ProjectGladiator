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
	// bool�� ��ȯ
	void ChangeData(void* data, bool& type);
	// int�� ��ȯ
	void ChangeData(void* data, int& _count);
	// float�� ��ȯ
	void ChangeData(void* data, float& _num);
	// ��Ƽ���ȣ, ��Ƽ������
	void ChangeData(void* data, int& _partyroomnum,int& _partyusercount);
	// ä�� �̵� ���
	void ChangeData(void* data, bool& _type, int& _count);
	// ĳ���ͽ�������
	void ChangeData(void* data, bool& _type, int& _count, CharacterSlot*& _slot);
	// ĳ���� ���� + ä�ι�ȣ
	void ChangeData(void* data, CharacterInfo*& _charinfo, int& _channelnum);
	// ĳ���� ����
	void ChangeData(void* data, CharacterInfo*& _charinfo);
	// �̵����� �����
	void ChangeData(void* data, bool& _result, float*& _posxyz);
	// �÷��̾� �̵����� �����
	void ChangeData(void* data, float*& _posxyz, float*& _rotxyz);
	// �ٸ� �÷��̾� �̵����� �����
	void ChangeData(void* data, char*& _code, float*& _pos_rot_xyz);
	// �ٸ� �÷��̾� ����������
	void ChangeData(void* data, char*& _code);
	// ���ο� ��Ƽ ���� ����
	void ChangeData(void* data, char*& _oldcode, char*& _newcode);
	// �ٸ� �÷��̾� �̵����� �����
	void ChangeData(void* data, OtherCharacterInfo& _otherinfo);
	// ä�� ����
	void ChangeData(void* data, ChannelInfo*& _channelinfo);
	// ��Ƽ �ʴ� ����
	void ChangeData(void* data, int& _partyroomnum, char*& _code, char*& _nick);
	// ��Ƽ ���� ����
	void ChangeData(void* data, PartyUserInfo*& _partyuserinfo);
	// ���� ��� ����,��Ƽ ���� ���� ��� ����(�����̸� �ڵ��ְ�,�����ϸ� �ڿ� �ڵ尡�����ϴ�)
	void ChangeData(void* data, bool& _result, char* _code);
	// ���� ������ġ ����, �������� ������ġ ����
	void ChangeData(void* data, char*& _code,float& _pos_x, float& _pos_y, float& _pos_z);
	// �������� (�ڵ�,���ͼ���,��ǥ)
	void ChangeData(void* data, int& _code, int& _count, float& _pos_x, float& _pos_y, float& _pos_z);
	// �������� (�ڵ�,���ݹ�ȣ)
	void ChangeData(void* data, char* _code, int _attacknum);
	// ���� �ǰ����� (�����ڵ�, ���ͼ���,������)
	void ChangeData(void* data, int& _monstercode, int& _monsternum, int& _damage);
	// ���� �ǰ�����(���,������,����ִ���)
	void ChangeData(void* data, bool& _result, int& _damage, bool& _is_live);
	// �ٸ� ���� �ǰ�����(ĳ�����ڵ�,������,����ִ���)
	void ChangeData(void* data, char* _code, int& _damage, bool& _is_live);


	bool PopData();
};

#endif