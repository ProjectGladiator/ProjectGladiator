#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include "User.h"

class UserManager
{
private:
	User * list[CLIENTCOUNT];
	static UserManager* Instance;
	int count;

	UserManager();
	~UserManager();

public:
	static void CreateInstance();
	static UserManager* GetInstance();
	static void DestroyInstance();
	
	bool InitializeManager();
	void EndManager();

	User* addUser(SOCKET sock);
	void removeUser(User* user);
	User* getUser(SOCKET sock);
	User* getUser(char* id);
};

#endif
