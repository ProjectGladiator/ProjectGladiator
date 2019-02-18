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

	void InGame_Req_UserList();							// ���� �������� ��������Ʈ ��û
	bool InGame_Recv_UserList(char* _buf);				// ���� �������� ��������Ʈ ����
	bool InGame_Recv_MoveResult(char* _buf);			// �̵� ���
	void InGame_Recv_OtherUserMoveInfo(char* _buf);		// �ٸ� ���� �̵� ����

	RESULT InGameInitRecvResult(User* _user);			// �ΰ��� 
};

#endif
