#include "ChatManager.h"
#include "UserManager.h"

ChatManager* ChatManager::Instance = nullptr;

ChatManager::ChatManager()
{

}

ChatManager::~ChatManager()
{

}

void ChatManager::CreateInstance()
{
	Instance = new ChatManager();
}

ChatManager * ChatManager::GetInstance()
{
	return Instance;
}

void ChatManager::DestroyInstance()
{
	if (Instance != nullptr)
	{
		delete Instance;
		Instance = nullptr;
	}
}

bool ChatManager::InitializeManager()
{
	return true;
}

void ChatManager::EndManager()
{
}

// 유저리스트 요청
void ChatManager::ReqUsertList(User * _user)
{
	char buf[BUFSIZE];
	int usernum = 0;

	while (1)
	{
		UserManager::GetInstance()->getUser("asd");
	}
	
	_user->pack(SERVER_CHAT_LIST_RESULT, buf, 0);
}

// 채팅방 요청
void ChatManager::ReqChatList(User * _user, char* _buf)
{
	ChatRoomList* room = new ChatRoomList();
		

}

void ChatManager::ChatMsg(User * _user, char* _buf)
{
	PROTOCOL protocol = EXIT;
	char msg[BUFSIZE];

	int roomnum;
	int msgsize;
	memcpy(&roomnum, _buf, sizeof(int));
	_buf += sizeof(int);

	memcpy(&msgsize, _buf, sizeof(int));
	_buf += sizeof(int);

	memcpy(msg, _buf,msgsize);

	ChatRoomList* data;
	for (list<ChatRoomList*>::iterator i = roomlist.begin(); i != roomlist.end(); ++i)
	{
		data = (*i);
		if (data->getRoomNum() == roomnum)
		{
			break;
		}
	}

}

bool ChatManager::IsChat(User * _user)
{
	PROTOCOL protocol;
	char buf[BUFSIZE];

	_user->unPack(&protocol, buf);
	
	switch (protocol)
	{
	case CLIENT_REQ_CHAT_LIST:
		ReqUsertList(_user);
		break;

	case CLIENT_REQ_CHAT_START:
		ReqChatList(_user, buf);
		break;

	case CLIENT_CHAT_MSG:
		ChatMsg(_user, buf);
		break;

	case CLIENT_CHAT_EXIT:
		break;
	default:
		return false;
	}

	return true;
}
