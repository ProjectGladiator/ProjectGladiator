#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include "User.h"
#include <list>

// 친구창 관리 //
class UserManager
{
private:
	//User * list[CLIENTCOUNT];				// std 리스트로 교체 예정
	std::list<User*> ConnectUserlist;		// 접속한 유저 리스트
	std::list<User*>::iterator save;		// 검색용 유저 저장할 변수
	static UserManager* Instance;

	UserManager();
	~UserManager();

public:
	static void CreateInstance();
	static UserManager* GetInstance();
	static void DestroyInstance();
	
	bool InitializeManager();
	void EndManager();

	User* addUser(SOCKET _sock);
	void removeUser(User* _user);
	User* getUser(SOCKET _sock);
	User* getUser(char* _id);

	void startSearch();						// 리스트
	bool searchData(User*& _user);			// 리스트
};

#endif
