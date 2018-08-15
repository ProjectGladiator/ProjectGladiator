#include "UserManager.h"

UserManager* UserManager::Instance = nullptr;

UserManager::UserManager()
{
	count = 0;
}

UserManager::~UserManager()
{
	for (int idx = 0; idx < count; idx++)
	{
		if (list[idx] != nullptr)
		{
			delete list[idx];
		}
	}
}

void UserManager::CreateInstance()
{
	if (Instance != nullptr)
	{
		delete Instance;
	}

	Instance = new UserManager();
}

UserManager* UserManager::GetInstance()
{
	return Instance;
}

void UserManager::DestroyInstance()
{
	delete Instance;
}

bool UserManager::InitializeManager()
{
	return true;
}

void UserManager::EndManager()
{

}

User* UserManager::addUser(SOCKET sock)
{
	User* newUser = nullptr;

	if (count < CLIENTCOUNT &&
		sock != SOCKET_ERROR)
	{
		SOCKADDR_IN addr;
		int addrlen = sizeof(addr);

		getpeername(sock, (SOCKADDR*)&addr, &addrlen);

		newUser = new User(sock, addr);
		list[count++] = newUser;
	}
	return newUser;
}

void UserManager::removeUser(User* user)
{
	int idx = 0;
	//search and delete
	while (idx < count)
	{
		if (list[idx] == user)
		{
			delete list[idx];
			list[idx] = nullptr;
			count--;

			//shift
			while (idx < count)
			{
				list[idx] = list[idx + 1];
				idx++;
			}

			list[idx] = nullptr;

			break;
		}

		idx++;
	}
	
}

User* UserManager::getUser(SOCKET sock)
{
	User* target = nullptr;
	
	//search
	for (int idx = 0; idx < count; idx++)
	{
		if (list[idx]->getSocket() == sock)
		{
			target = list[idx];
			break;
		}
	}

	return target;
}

User* UserManager::getUser(char* id)
{
	User* target = nullptr;

	//search
	for (int idx = 0; idx < count; idx++)
	{
		if (!strcmp(list[idx]->getID(), id))
		{
			target = list[idx];
			break;
		}
	}

	return target;
}
