#ifndef _STORAGE_MANAGER_H_
#define _STORAGE_MANAGER_H_

#include "global.h"
#include "DataProtocol.h"
#include "StorageDataType.h"
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
		delete[] data;
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

	int NProtocoltoDProtocol(int _networkprotocol);
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
	void ChangeData(void* data, int _count, CharacterInfo*& _charinfo);
	bool PopData();
};

#endif