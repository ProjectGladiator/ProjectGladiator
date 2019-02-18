#ifndef _INGAME_MANAGER_H_
#define _INGAME_MANAGER_H_

#include "Global.h"
#include "User.h"

class InGameManager
{
private:
	static InGameManager* Instance;

	InGameManager();
	~InGameManager();

public:
	static void CreateInstance();
	static InGameManager* GetInstance();
	static void DestroyInstance();

	bool MangerInitialize();
	void EndManager();

	void InGame_Req_UserList();							// 현재 접속중인 유저리스트 요청
	bool InGame_Recv_UserList(char* _buf);				// 현재 접속중인 유저리스트 받음
	bool InGame_Recv_MoveResult(char* _buf);			// 이동 결과
	void InGame_Recv_OtherUserMoveInfo(char* _buf);		// 다른 유저 이동 정보

	RESULT InGameInitRecvResult(User* _user);			// 인게임 
};

#endif
