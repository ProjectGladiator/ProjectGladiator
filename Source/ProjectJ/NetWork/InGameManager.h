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

	bool InGame_Recv_UserList(char* _buf);				// ���� �������� ��������Ʈ ����
	bool InGame_Recv_MoveResult(char* _buf);			// �̵� ���
	void InGame_Recv_OtherUserMoveInfo(char* _buf, int _protocol);		// �ٸ� ���� �̵� ����
public:
	static void CreateInstance();
	static InGameManager* GetInstance();
	static void DestroyInstance();

	bool MangerInitialize();
	void EndManager();

	void InGame_Req_UserList();							// ���� �������� ��������Ʈ ��û
	// �̵���û ������ ����
	void InGame_Req_Move(float _px, float _py, float _pz, float _rx, float _ry, float _rz);
	// �̵����� ������ ����
	//void InGame_Req_MoveStart(float _px, float _py, float _pz, float _rx, float _ry, float _rz, float _dirx, float _diry);

	RESULT InGameInitRecvResult(User* _user);			// �ΰ��� 
};

#endif
