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
	type = *(bool*)data;
}

void StorageManager::ChangeData(void * data, bool& _type, int& _count, CharacterSlot*& _slot)
{
	char* ptr = (char*)data;
	
	int joblen;
	char* jobname;
	int level;
	int nicklen;
	char* nick;

	_type = *(bool*)ptr;
	ptr += sizeof(bool);

	if (_type == false)
	{
		return;
	}

	_count = *(int*)ptr;
	ptr += sizeof(int);
	
	CharacterSlot* characterslot;

	memset(characterslot, 0, sizeof(characterslot));

	for (int i = 0; i < _count; i++)
	{
		joblen = *(int*)ptr;
		ptr += sizeof(int);

		jobname = (char*)ptr;
		ptr += joblen;

		level = *(int*)ptr;
		ptr += sizeof(int);

		nicklen = *(int*)ptr;
		ptr += sizeof(int);

		nick = (char*)ptr;
		ptr += nicklen;

		characterslot[i].name = jobname;

		characterslot[i].nick = nick;

		characterslot[i].level = level;
	}


	_slot = characterslot;
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

// 데이터 제거
//void StorageManager::removeData(void* data)
//{
//	int i;
//	DataStorage.
//		PacketData* Stored_packetdata;
//	for (list<PacketData*>::iterator i = DataStorage.begin(); i != DataStorage.end(); ++i)
//	{
//		Stored_packetdata = (*i);
//		if (Stored_packetdata->data == data)
//		{
//			delete[] Stored_packetdata->data;
//			DataStorage.remove(Stored_packetdata);
//			return;
//		}
//	}
//}


//bool StorageManager::searchData(PacketData*& packetdata)
//{
//	if (save != DataStorage.end())
//	{
//		packetdata = *save;
//		++save;
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}

//void StorageManager::startSearch()
//{
//	save = DataStorage.begin();
//}
//
//void* StorageManager::getData(PROTOCOL p)
//{
//	PacketData* packetdata;
//	for (list<PacketData*>::iterator i = DataStorage.begin(); i != DataStorage.end(); ++i)
//	{
//		packetdata = (*i);
//		if (packetdata->p == p)
//		{
//			return packetdata->data;
//		}
//	}
//	return nullptr;
//}
