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
	void ChangeData(void* data, bool& type);
	void ChangeData(void* data, int& _count);
	void ChangeData(void* data, bool& _type, int& _count, CharacterSlot*& _slot);
	void ChangeData(void* data, CharacterInfo*& _charinfo,int& _channelnum);
	void ChangeData(void* data, CharacterInfo*& _charinfo);
	void ChangeData(void* data, bool& _result, float*& _posxyz);
	void ChangeData(void* data, float*& _posxyz, float*& _rotxyz);
	void ChangeData(void* data, char*& _code, float*& _pos_rot_xyz);
	void ChangeData(void* data, char*& _code);
	void ChangeData(void* data, OtherCharacterInfo& _otherinfo);
	void ChangeData(void* data, ChannelInfo*& _channelinfo);
	bool PopData();
};

#endif