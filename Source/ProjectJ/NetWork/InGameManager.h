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

	bool InGame_Recv_UserList(char* _buf);								// ���� �������� ��������Ʈ ����
	void InGame_Recv_ConnectUserInfo(char* _buf);						// ������ �ٸ� �������� ����
	bool InGame_Recv_MoveResult(char* _buf);							// �̵� ���
	void InGame_Recv_OtherUserMoveInfo(char* _buf, int _protocol);		// �ٸ� ���� �̵� ����
	void InGame_Recv_OtherUserRotation(char* _buf);						// �ٸ� ���� ȸ�� ����
	void InGame_Recv_OtherUserLeave(char* _buf);						// �ٸ� ���� ��������
	void InGame_Recv_ChannelInfo(char* _buf);							// ä�� ����
	void InGame_Recv_CharacterSelect();									// ĳ���� ����ȭ������ �޾�����
	void InGame_Recv_Logout();											// �α׾ƿ� �޾�����
	void InGame_Recv_ChannelChange(char* _buf);							// ä���̵� ���

public:
	static void CreateInstance();
	static InGameManager* GetInstance();
	static void DestroyInstance();

	bool MangerInitialize();
	void EndManager();

	void InGame_Req_UserList();										    // ���� �������� ��������Ʈ ��û
	void InGame_Req_Move(float _px, float _py, float _pz);			    // �̵���û ������ ����
	void InGame_Req_Rotation(float _rx, float _ry, float _rz);		    // ȸ������ ������ ����
	void InGame_Req_ChannelInfo();									    // ä�� ���� ��û
	void InGame_Req_ChannelChange(int _channelnum);					    // ä�� �̵� ��û
	void InGame_Req_Menu_Character();								    // ĳ���� ����ȭ������ ��û
	void InGame_Req_Menu_Title();									    // �α׾ƿ� ��û
	// �������� ��û ������ ����

	RESULT InGameInitRecvResult(User* _user);			// �ΰ��� 
};

#endif
