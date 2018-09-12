#include "UserManager.h"

UserManager* UserManager::Instance = nullptr;

UserManager::UserManager()
{

}
UserManager::~UserManager()
{
	User* target = nullptr;

	for (std::list<User*>::iterator i = ConnectUserlist.begin(); i != ConnectUserlist.end(); ++i)
	{
		target = (*i);
		delete target;
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



User* UserManager::addUser(SOCKET _sock)
{
	User* newUser = nullptr;

	if (ConnectUserlist.size() < CLIENTCOUNT &&
		_sock != SOCKET_ERROR)
	{
		SOCKADDR_IN addr;
		int addrlen = sizeof(addr);

		getpeername(_sock, (SOCKADDR*)&addr, &addrlen);

		newUser = new User(_sock, addr);
		ConnectUserlist.push_back(newUser);
	}
	return newUser;
}

void UserManager::removeUser(User* _user)
{
	// 유저 찾아서 삭제
	ConnectUserlist.remove(_user);
}

User* UserManager::getUser(SOCKET _sock)
{
	User* target = nullptr;

	for (std::list<User*>::iterator i = ConnectUserlist.begin(); i != ConnectUserlist.end(); ++i)
	{
		target = (*i);
		if (target->getSocket() == _sock)
		{
			break;
		}
	}
	return target;
}

User* UserManager::getUser(char* _id)
{
	User* target = nullptr;

	for (std::list<User*>::iterator i = ConnectUserlist.begin(); i != ConnectUserlist.end(); ++i)
	{
		target = (*i);
		if (target->getID() == _id)
		{
			break;
		}
	}
	return target;
}

void UserManager::startSearch()
{
	// 리스트 시작부 세팅
	save = ConnectUserlist.begin();
}

bool UserManager::searchData(User *& _user)
{
	// 유저 하나씩 꺼내서 save에 넣음
	if (save != ConnectUserlist.end())
	{
		_user = *save;
		++save;
		return true;
	}
	else
	{
		return false;
	}
}
