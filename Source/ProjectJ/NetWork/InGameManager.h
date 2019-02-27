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
	void InGame_Recv_ConnectUserInfo(char* _buf);				// ������ �ٸ� �������� ����
	bool InGame_Recv_MoveResult(char* _buf);			// �̵� ���
	void InGame_Recv_OtherUserMoveInfo(char* _buf, int _protocol);		// �ٸ� ���� �̵� ����
	void InGame_Recv_OtherUserRotation(char* _buf);
public:
	static void CreateInstance();
	static InGameManager* GetInstance();
	static void DestroyInstance();

	bool MangerInitialize();
	void EndManager();

	void InGame_Req_UserList();							// ���� �������� ��������Ʈ ��û
	// �̵���û ������ ����
	void InGame_Req_Move(float _px, float _py, float _pz);
	// �̵����� ������ ����
	//void InGame_Req_MoveStart(float _px, float _py, float _pz, float _rx, float _ry, float _rz, float _dirx, float _diry);
	void InGame_Req_Rotation(float _rx, float _ry, float _rz);

	RESULT InGameInitRecvResult(User* _user);			// �ΰ��� 
};

#endif
