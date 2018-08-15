#ifndef ENCRYPT_MANAGER_H
#define ENCRYPT_MANAGER_H

#include <Windows.h>

class EncryptManager
{
private:
	char key[4];
	static EncryptManager* Instance;

	EncryptManager(int key);
	~EncryptManager();

public:
	static void CreateInstance(int key);
	static EncryptManager* GetInstance();
	static void DestroyInstance();

	bool InitializeManager();
	void EndManager();

	void encoding(char *packet, int size);
	void decoding(char *packet, int size);
};
#endif