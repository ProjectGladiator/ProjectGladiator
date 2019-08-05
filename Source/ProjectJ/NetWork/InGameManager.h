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

	// ���� �������� ��������Ʈ ����
	bool InGame_Recv_UserList(char* _buf);
	// ������ �ٸ� �������� ����
	void InGame_Recv_ConnectUserInfo(char* _buf);
	// �̵� ���
	bool InGame_Recv_MoveResult(char* _buf);
	// �ٸ� ���� �̵� ����
	void InGame_Recv_OtherUserMoveInfo(char* _buf, int _protocol);
	// �ٸ� ���� ȸ�� ����
	void InGame_Recv_OtherUserRotation(char* _buf);
	// �ٸ� ���� ��������
	void InGame_Recv_OtherUserLeave(char* _buf);
	// �ٸ� ���� ���� �ߴٴ� ����
	void InGame_Recv_OtherUser_Start_Jump(char* _buf);
	// �ٸ� ���� ���� �ߴٴ� ����
	void InGame_Recv_OtherUser_End_Jump(char* _buf);
	// �ٸ� ���� �����ߴٴ� ����
	void InGame_Recv_OtherUser_Attack(char* _buf);
	// ä�� ����
	void InGame_Recv_ChannelInfo(char* _buf);
	// ĳ���� ����ȭ������ �޾�����
	void InGame_Recv_CharacterSelect();
	// �α׾ƿ� �޾�����
	void InGame_Recv_Logout();
	// ä���̵� ���
	void InGame_Recv_ChannelChange(char* _buf);

	// ��Ƽ �ʴ� ����
	void InGame_Recv_Invite(char* _buf);
	// ��Ƽ �ʴ� �������
	void InGame_Recv_Invite_Result(char* _buf);
	// ��Ƽ ���� ���
	void InGame_Recv_Join_Result(char* _buf);
	// ��Ƽ ���� �߰�
	void InGame_Recv_Party_User_Info(char* _buf);

	// ��Ƽ ���� ����
	void InGame_Recv_Kick();
	// ��Ƽ ������� ���� ���� ����
	void InGame_Recv_Kick_User_Info(char* _buf);
	// ��Ƽ ������
	void InGame_Recv_Kick_Result(char* _buf);
	// ��Ƽ Ż����� ���� ��������
	void InGame_Recv_Leave_User_Info(char* _buf);
	// ��Ƽ Ż�� ���
	void InGame_Recv_Leave_Result(char* _buf);
	// ��Ƽ�� �������
	void InGame_Recv_PartyRoom_Remove(char* _buf);
	// ���ο� ��Ƽ ���� ����
	void InGame_Recv_PartyRoom_Leader_Info(char* _buf);
	// ��Ƽ ���� ���� ���
	void InGame_Recv_PartyRoom_Leader_Delegate_Result(char* _buf);

	// ���� ���� ���
	void InGame_Recv_Leave_Dungeon_Enter_Result(char* _buf);
	// ���� ���� ���
	void InGame_Recv_Leave_Dungeon_Leave_Result(char* _buf);

	// �������� ���� ���
	void InGame_Recv_Stage_Enter_Result(char* _buf);

	// �������� ������ �޴� ��������(�ʱ�ȭ����)
	void InGame_Recv_Stage_MonsterInfo(char* _buf);
	// ���� �̵�����
	void InGame_Recv_Monster_MoveInfo(char* _buf);
	// ���� �ǰ�����
	void InGame_Recv_Monster_has_been_Attacked(char* _buf);
	// �ٸ� ���� ���� �ǰ�����
	void InGame_Recv_OtherMonster_has_been_Attack(char* _buf);
	// ���� �ǰ�����
	void InGame_Recv_UnderAttack(char* _buf);
	// �ٸ� ���� �ǰ�����
	void InGame_Recv_Other_UnderAttack(char* _buf);

	// ���� ���� �ִϸ��̼�
	//void InGame_Recv_Monster_Attack_Animation(char* _buf);

public:
	static void CreateInstance();
	static InGameManager* GetInstance();
	static void DestroyInstance();

	bool MangerInitialize();
	void EndManager();

	/*--ĳ����--*/
	// ���� �������� ��������Ʈ ��û
	void InGame_Req_UserList();
	// �̵���û ������ ����
	void InGame_Req_Move(float _px, float _py, float _pz);
	// ȸ������ ������ ����
	void InGame_Req_Rotation(float _rx, float _ry, float _rz);
	// ���� �����ߴٰ� �˸�
	void InGame_Character_Start_Jump();
	// �����ߴٰ� �˸�
	//void InGame_Character_End_Jump();
	// ���� �ϰڴٰ� �˸�(���� �����ߴ���)
	void InGame_Character_Attack(int _attacknum);
	// �����ߴµ� ���Ͷ� �ǰ��������Ͱ���.(�����ڵ�,���͹�ȣ,���ݹ�ȣ,���� ��Ÿ� ��ǥ)
	void InGame_Character_Attack_Success(int _monstercode, int _monsternum, int _attacknum, float _x, float _y, float _z);

	/*--ä��--*/
	// ä�� ���� ��û
	void InGame_Req_ChannelInfo();
	// ä�� �̵� ��û
	void InGame_Req_ChannelChange(int _channelnum);

	/*--�Ŵ�--*/
	// ĳ���� ����ȭ������ ��û
	void InGame_Req_Menu_Character();
	// �α׾ƿ� ��û
	void InGame_Req_Menu_Title();
	// �������� ��û ������ ����
	// ���� �̱���

	/*--��Ƽ--*/
	// �����û
	void InGame_Req_KickUser(char* _code);
	// Ż���û
	void InGame_Req_LeaveParty();
	// ��Ƽ ���� �����ϱ�
	void InGame_Req_LeaderDelegate(char* _code);
	// ��Ƽ �ʴ� ��û
	void InGame_Req_Party_Invite(char* _code);
	// ��Ƽ �ʴ� ����
	void InGame_Req_Party_Invite_Result(bool _result, char* _code, int _partyroomnum);

	/*--����/��������--*/
	// ���� ���� ��û
	void InGame_Req_Dungeon_Enter();
	// ���� ���� ��û
	void InGame_Req_Dungeon_Leave();
	// �������� ����
	void InGame_Req_Dungeon_Stage_Enter();
	// ���� �������� ���� ��û

	// ���� ���������� ��������

	//

	/*--����--*/
	// ���� ���� ��û
	void InGame_Req_Monster_Info();
	// ��Ƽ������ ���� �̵� ���� ����
	void InGame_Req_Monster_Move_Info(int _code, int _num, float _px, float _py, float _pz);
	// �ǰݹ��� ������ ���� ���� ���� ����(ĳ�����ڵ�, �����ڵ�, ���͹�ȣ, ���ݹ�ȣ, ���ݻ�Ÿ���ǥ)
	void InGame_Req_Monster_Attack(int _monstercode, int _monsternum, int _attacknum, float _x, float _y, float _z);

	RESULT InGameInitRecvResult(User* _user);			// �ΰ��� 
};

#endif
