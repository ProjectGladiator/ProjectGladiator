#include "EnryptManager.h"

EncryptManager* EncryptManager::Instance = nullptr;

EncryptManager::EncryptManager(int key)
{
	memcpy(this->key, &key, sizeof(int));
}
EncryptManager::~EncryptManager()
{

}


void EncryptManager::CreateInstance(int key)
{
	if (Instance == nullptr)
	{
		Instance = new EncryptManager(key);
	}
}
EncryptManager* EncryptManager::GetInstance()
{
	return Instance;
}
void EncryptManager::DestroyInstance()
{
	if (Instance != nullptr)
	{
		delete Instance;
	}
}

bool EncryptManager::InitializeManager()
{
	return true;
}

void EncryptManager::EndManager()
{

}

void EncryptManager::encoding(char *packet, int size)
{
	for (int i = 0; i < size; i++)
	{
		packet[i] ^= key[i%4];
	}
}
void EncryptManager::decoding(char *packet, int size)
{
	for (int i = 0; i < size; i++)
	{
		packet[i] ^= key[i % 4];
	}
}

