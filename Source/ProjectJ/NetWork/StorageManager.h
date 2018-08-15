#ifndef _STORAGE_MANAGER_H_
#define _STORAGE_MANAGER_H_

#include "global.h"
#include "DataProtocol.h"
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

	void PushData(PROTOCOL p, void* data, int data_size);
	bool GetFront(PacketData*& data);
	void ChangeData(void* data, bool& type);
	bool PopData();
	
	// ¼öÁ¤ ÈÄ Æó±â
	//void removeData(void* data);
	//void* getData(PROTOCOL p);
	//void startSearch();
	//bool searchData(PacketData*& packetdata);
};

#endif