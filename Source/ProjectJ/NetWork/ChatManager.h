#pragma once
#ifndef _CHAT_MANAGER_
#define _CHAT_MANAGER_

#include "Global.h"
#include "User.h"
#include <list>

using namespace std;

struct ChatRoomList
{
private:
	int roomnum;
	list<User*> list;
public:
	ChatRoomList() { roomnum = 0; }
	~ChatRoomList() { }
	int getRoomNum() { return roomnum; }
};

class ChatManager
{
private:
	static ChatManager* Instance;

	list<ChatRoomList*>roomlist;

	void ReqUsertList(User* _user);
	void ReqChatList(User* _user, char* _buf);
	void ChatMsg(User* _user, char* _buf);

	ChatManager();
	~ChatManager();
public:
	static void CreateInstance();
	static ChatManager* GetInstance();
	static void DestroyInstance();

	bool InitializeManager();
	void EndManager();

	bool IsChat(User* _user);
};

#endif // !_CHAT_MANAGER_
