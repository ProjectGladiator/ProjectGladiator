#include "InGameManager.h"
#include "NetworkManager.h"
#include "LogManager.h"

InGameManager* InGameManager::Instance = nullptr;

InGameManager::InGameManager()
{

}

InGameManager::~InGameManager()
{

}

void InGameManager::CreateInstance()
{
	if (Instance == nullptr)
	{
		Instance = new InGameManager();
	}
}

InGameManager * InGameManager::GetInstance()
{
	return Instance;
}

void InGameManager::DestroyInstance()
{
	if (Instance != nullptr)
	{
		delete Instance;
		Instance = nullptr;
	}
}

bool InGameManager::MangerInitialize()
{
	return true;
}

void InGameManager::EndManager()
{

}

// ���� �������� ��������Ʈ ��û
void InGameManager::InGame_Req_UserList()
{
	UINT64 protocol = 0;
	char buf[BUFSIZE];
	memset(buf, 0, sizeof(buf));

	protocol = NetworkClient_main::NetworkManager::GetInstance()->GetUser()->BitPackProtocol(protocol, PROTOCOL_INGAME, PROTOCOL_INGAME_CHARACER, PROTOCOL_REQ_OTHERPLAYERLIST);

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->pack(protocol, buf, 0);
}

// �̵� ��û
void InGameManager::InGame_Req_Move(float _px, float _py, float _pz)
{
	UINT64 protocol = 0;
	char buf[BUFSIZE];
	char* ptr = buf;
	int datasize = 0;
	memset(buf, 0, sizeof(buf));

	// ��ġ��
	memcpy(ptr, &_px, sizeof(float));
	datasize += sizeof(float);
	ptr += sizeof(float);

	memcpy(ptr, &_py, sizeof(float));
	datasize += sizeof(float);
	ptr += sizeof(float);

	memcpy(ptr, &_pz, sizeof(float));
	datasize += sizeof(float);
	ptr += sizeof(float);

	protocol = NetworkClient_main::NetworkManager::GetInstance()->GetUser()->BitPackProtocol(protocol, PROTOCOL_INGAME, PROTOCOL_INGAME_CHARACER, PROTOCOL_MOVE_REPORT);

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->pack(protocol, buf, datasize);
}

// ȸ�� ��û
void InGameManager::InGame_Req_Rotation(float _rx, float _ry, float _rz)
{
	UINT64 protocol = 0;
	char buf[BUFSIZE];
	char* ptr = buf;
	int datasize = 0;
	memset(buf, 0, sizeof(buf));

	// ȸ����
	memcpy(ptr, &_rx, sizeof(float));
	datasize += sizeof(float);
	ptr += sizeof(float);

	memcpy(ptr, &_ry, sizeof(float));
	datasize += sizeof(float);
	ptr += sizeof(float);

	memcpy(ptr, &_rz, sizeof(float));
	datasize += sizeof(float);
	ptr += sizeof(float);

	protocol = NetworkClient_main::NetworkManager::GetInstance()->GetUser()->BitPackProtocol(protocol, PROTOCOL_INGAME, PROTOCOL_INGAME_CHARACER, PROTOCOL_MOVE_ROTATION);

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->pack(protocol, buf, datasize);
}

// ���� �����ߴٰ� �˸�
void InGameManager::InGame_Character_Start_Jump()
{
	UINT64 protocol = 0;
	char buf[BUFSIZE];
	memset(buf, 0, sizeof(buf));

	protocol = NetworkClient_main::NetworkManager::GetInstance()->GetUser()->BitPackProtocol(protocol, PROTOCOL_INGAME, PROTOCOL_INGAME_CHARACER, PROTOCOL_INGAME_MOVE_START_JUMP);

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->pack(protocol, buf, 0);
}


//// �����ߴٰ� �˸�
//void InGameManager::InGame_Character_End_Jump()
//{
//	UINT64 protocol = 0;
//	char buf[BUFSIZE];
//	memset(buf, 0, sizeof(buf));
//
//	protocol = NetworkClient_main::NetworkManager::GetInstance()->GetUser()->BitPackProtocol(protocol, PROTOCOL_INGAME, PROTOCOL_INGAME_CHARACER, PROTOCOL_INGAME_MOVE_END_JUMP);
//
//	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->pack(protocol, buf, 0);
//}

// ���� �ϰڴٰ� �˸�
void InGameManager::InGame_Character_Attack(int _attacknum)
{
	UINT64 protocol = 0;
	char buf[BUFSIZE];
	memset(buf, 0, sizeof(buf));
	char* ptr = buf;
	int datasize = 0;

	memcpy(ptr, &_attacknum, sizeof(int));
	datasize += sizeof(int);

	protocol = NetworkClient_main::NetworkManager::GetInstance()->GetUser()->BitPackProtocol(protocol, PROTOCOL_INGAME, PROTOCOL_INGAME_CHARACER, PROTOCOL_INGAME_ATTACK);

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->pack(protocol, buf, datasize);
}

// �����ߴµ� ���Ͷ� �ǰ��������Ͱ���.�����ڵ�,���͹�ȣ
void InGameManager::InGame_Character_Attack_Success(int _monstercode, int _monsternum, int _attacknum, float _x, float _y, float _z)
{
	UINT64 protocol = 0;
	char buf[BUFSIZE];
	memset(buf, 0, sizeof(buf));
	char* ptr = buf;
	int datasize = 0;

	// ���� �ڵ�
	memcpy(ptr, &_monstercode, sizeof(int));
	datasize += sizeof(int);
	ptr += sizeof(int);
	// ���� ��ȣ
	memcpy(ptr, &_monsternum, sizeof(int));
	datasize += sizeof(int);
	ptr += sizeof(int);
	// ���� ��ȣ
	memcpy(ptr, &_attacknum, sizeof(int));
	datasize += sizeof(int);
	ptr += sizeof(int);
	// x
	memcpy(ptr, &_x, sizeof(float));
	datasize += sizeof(float);
	ptr += sizeof(float);
	// y
	memcpy(ptr, &_y, sizeof(float));
	datasize += sizeof(float);
	ptr += sizeof(float);
	// z
	memcpy(ptr, &_z, sizeof(float));
	datasize += sizeof(float);
	ptr += sizeof(float);

	protocol = NetworkClient_main::NetworkManager::GetInstance()->GetUser()->BitPackProtocol(protocol, PROTOCOL_INGAME, PROTOCOL_INGAME_CHARACER, PROTOCOL_INGAME_ATTACK_SUCCESS);

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->pack(protocol, buf, datasize);
}

// ä�� ���� ��û
void InGameManager::InGame_Req_ChannelInfo()
{
	UINT64 protocol = 0;
	char buf[BUFSIZE];
	memset(buf, 0, sizeof(buf));

	protocol = NetworkClient_main::NetworkManager::GetInstance()->GetUser()->BitPackProtocol(protocol, PROTOCOL_INGAME, PROTOCOL_INGAME_CHANNEL, PROTOCOL_REQ_CHANNEL_INFO);

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->pack(protocol, buf, 0);
}

// ä�� �̵� ��û
void InGameManager::InGame_Req_ChannelChange(int _channelnum)
{
	UINT64 protocol = 0;
	char buf[BUFSIZE];
	char* ptr = buf;
	int datasize = 0;
	memset(buf, 0, sizeof(buf));

	// ä�� ��ȣ
	memcpy(ptr, &_channelnum, sizeof(int));
	datasize += sizeof(int);
	ptr += sizeof(int);
	
	protocol = NetworkClient_main::NetworkManager::GetInstance()->GetUser()->BitPackProtocol(protocol, PROTOCOL_INGAME, PROTOCOL_INGAME_CHANNEL, PROTOCOL_REQ_CHANNEL_CHANGE);

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->pack(protocol, buf, datasize);
}

// ĳ���� ����ȭ������ ��û
void InGameManager::InGame_Req_Menu_Character()
{
	UINT64 protocol = 0;
	char buf[BUFSIZE];
	memset(buf, 0, sizeof(buf));

	protocol = NetworkClient_main::NetworkManager::GetInstance()->GetUser()->BitPackProtocol(protocol, PROTOCOL_INGAME, PROTOCOL_INGMAE_MENU, PROTOCOL_MENU_REQ_CHARACTER);

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->pack(protocol, buf, 0);
}

// �α׾ƿ� ��û
void InGameManager::InGame_Req_Menu_Title()
{
	UINT64 protocol = 0;
	char buf[BUFSIZE];
	memset(buf, 0, sizeof(buf));

	protocol = NetworkClient_main::NetworkManager::GetInstance()->GetUser()->BitPackProtocol(protocol, PROTOCOL_INGAME, PROTOCOL_INGMAE_MENU, PROTOCOL_MENU_REQ_LOGOUT);

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->pack(protocol, buf, 0);
}

// �����û
void InGameManager::InGame_Req_KickUser(char * _code)
{
	UINT64 protocol = 0;
	char buf[BUFSIZE];
	memset(buf, 0, sizeof(buf));
	int codelen = strlen(_code) + 1;
	int datasize = 0;
	char* ptr = buf;

	memcpy(ptr, &codelen, sizeof(int));
	ptr += sizeof(int);
	datasize += sizeof(int);

	memcpy(ptr, _code, codelen);
	ptr += codelen;
	datasize += codelen;

	protocol = NetworkClient_main::NetworkManager::GetInstance()->GetUser()->BitPackProtocol(protocol, PROTOCOL_INGAME, PROTOCOL_INGAME_PARTY, PROTOCOL_REQ_USER_KICK);

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->pack(protocol, buf, datasize);
}

// Ż���û
void InGameManager::InGame_Req_LeaveParty()
{
	UINT64 protocol = 0;
	char buf[BUFSIZE];
	memset(buf, 0, sizeof(buf));

	protocol = NetworkClient_main::NetworkManager::GetInstance()->GetUser()->BitPackProtocol(protocol, PROTOCOL_INGAME, PROTOCOL_INGAME_PARTY, PROTOCOL_REQ_USER_LEAVE);

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->pack(protocol, buf, 0);
}

// ��Ƽ ���� �����ϱ�
void InGameManager::InGame_Req_LeaderDelegate(char * _code)
{
	UINT64 protocol = 0;
	char buf[BUFSIZE];
	memset(buf, 0, sizeof(buf));
	int codelen = strlen(_code) + 1;
	int datasize = 0;
	char* ptr = buf;

	memcpy(ptr, &codelen, sizeof(int));
	ptr += sizeof(int);
	datasize += sizeof(int);

	memcpy(ptr, _code, codelen);
	ptr += codelen;
	datasize += codelen;

	protocol = NetworkClient_main::NetworkManager::GetInstance()->GetUser()->BitPackProtocol(protocol, PROTOCOL_INGAME, PROTOCOL_INGAME_PARTY, PROTOCOL_REQ_LEADER_DELEGATE);

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->pack(protocol, buf, datasize);
}

// ���� �������� ��������Ʈ ����
bool InGameManager::InGame_Recv_UserList(char * _buf)
{
	int count;
	char* ptr_buf = _buf;

	char data[BUFSIZE];
	char* ptr_data = data;
	int size = 0;
	int jobcode = 0;
	int len = 0;
	char code[CHARACTERCODESIZE];
	char nick[NICKNAMESIZE];
	float xyz[3];
	float rot_xyz[3];

	memcpy(&count, ptr_buf, sizeof(int));
	ptr_buf += sizeof(int);

	StorageManager::GetInstance()->PushData(PGAMEDATA_USERLIST_COUNT, (void*)&count, sizeof(int));

	for (int i = 0; i < count; i++)
	{
		memset(data, 0, sizeof(data));
		memset(nick, 0, sizeof(nick));
		memset(code, 0, sizeof(code));
		ptr_data = data;
		size = 0;
		len = 0;
		jobcode = 0;

		// �ڵ� ������
		memcpy(&len, ptr_buf, sizeof(int));
		ptr_buf += sizeof(int);
		size += sizeof(int);
		memcpy(ptr_data, &len, sizeof(int));
		ptr_data += sizeof(int);

		// �ڵ�
		memcpy(code, ptr_buf, len);
		ptr_buf += len;
		size += len;
		memcpy(ptr_data, code, len);
		ptr_data += len;

		// ĳ���� �����ڵ�
		memcpy(&jobcode, ptr_buf, sizeof(int));
		ptr_buf += sizeof(int);
		size += sizeof(int);
		memcpy(ptr_data, &jobcode, sizeof(int));
		ptr_data += sizeof(int);

		// �г��� ������
		memcpy(&len, ptr_buf, sizeof(int));
		ptr_buf += sizeof(int);
		size += sizeof(int);
		memcpy(ptr_data, &len, sizeof(int));
		ptr_data += sizeof(int);

		// �г���
		memcpy(nick, ptr_buf, len);
		ptr_buf += len;
		size += len;
		memcpy(ptr_data, nick, len);
		ptr_data += len;

		// position x, y, z
		memcpy(xyz, ptr_buf, sizeof(float) * 3);
		ptr_buf += sizeof(float) * 3;
		size += sizeof(float) * 3;
		memcpy(ptr_data, xyz, sizeof(float) * 3);
		ptr_data += sizeof(float) * 3;

		// rotation x, y, z
		memcpy(rot_xyz, ptr_buf, sizeof(float) * 3);
		ptr_buf += sizeof(float) * 3;
		size += sizeof(float) * 3;
		memcpy(ptr_data, rot_xyz, sizeof(float) * 3);
		ptr_data += sizeof(float) * 3;

		StorageManager::GetInstance()->PushData(PGAMEDATA_USERLIST_USER, data, size);
	}

	return true;
}

// ������ �ٸ����� ����
void InGameManager::InGame_Recv_ConnectUserInfo(char * _buf)
{
	char* ptr_buf = _buf;

	char data[BUFSIZE];
	char code[CHARACTERCODESIZE];
	char nick[NICKNAMESIZE];
	char* ptr_data = data;
	int size = 0;
	int len = 0;
	int jobcode = 0;
	float xyz[3];
	float rot_xyz[3];

	memset(data, 0, sizeof(data));
	memset(code, 0, sizeof(code));
	memset(nick, 0, sizeof(nick));

	// �ڵ� ������
	memcpy(&len, ptr_buf, sizeof(int));
	ptr_buf += sizeof(int);
	size += sizeof(int);
	memcpy(ptr_data, &len, sizeof(int));
	ptr_data += sizeof(int);

	// �ڵ�
	memcpy(code, ptr_buf, len);
	ptr_buf += len;
	size += len;
	memcpy(ptr_data, code, len);
	ptr_data += len;

	// �����ڵ�
	memcpy(&jobcode, ptr_buf, sizeof(int));
	ptr_buf += sizeof(int);
	size += sizeof(int);
	memcpy(ptr_data, &jobcode, sizeof(int));
	ptr_data += sizeof(int);

	// �г��� ������
	memcpy(&len, ptr_buf, sizeof(int));
	ptr_buf += sizeof(int);
	size += sizeof(int);
	memcpy(ptr_data, &len, sizeof(int));
	ptr_data += sizeof(int);

	// �г���
	memcpy(nick, ptr_buf, len);
	ptr_buf += len;
	size += len;
	memcpy(ptr_data, nick, len);
	ptr_data += len;

	// position x, y, z
	memcpy(xyz, ptr_buf, sizeof(float) * 3);
	ptr_buf += sizeof(float) * 3;
	size += sizeof(float) * 3;
	memcpy(ptr_data, xyz, sizeof(float) * 3);
	ptr_data += sizeof(float) * 3;

	// rotation x, y, z
	memcpy(rot_xyz, ptr_buf, sizeof(float) * 3);
	ptr_buf += sizeof(float) * 3;
	size += sizeof(float) * 3;
	memcpy(ptr_data, rot_xyz, sizeof(float) * 3);
	ptr_data += sizeof(float) * 3;

	StorageManager::GetInstance()->PushData(PGAMEDATA_USERLIST_USER, data, size);
}

// �÷��̾� �̵� ��� 
bool InGameManager::InGame_Recv_MoveResult(char * _buf)
{
	bool result;
	char* ptr_buf = _buf;

	char data[BUFSIZE];
	char* ptr_data = data;
	int size = 0;
	float xyz[3];

	// �̵����
	memcpy(&result, ptr_buf, sizeof(bool));
	ptr_buf += sizeof(bool);

	// �̵���� ���丮���� ����
	//StorageManager::GetInstance()->PushData(PGAMEDATA_PLAYER_MOVE_RESULT, data, size);

	memset(data, 0, sizeof(data));
	ptr_data = data;

	// ���� �� 
	if (result == false)
	{
		// position x, y, z
		memcpy(xyz, ptr_buf, sizeof(float) * 3);
		ptr_buf += sizeof(float) * 3;
		size += sizeof(float) * 3;
		memcpy(ptr_data, xyz, sizeof(float) * 3);
		ptr_data += sizeof(float) * 3;

		// ���� �� ���� �̵����
		StorageManager::GetInstance()->PushData(PGAMEDATA_PLAYER_MOVE_INFO, data, size);
	}

	return result;
}

// �ٸ� ���� �̵� ����
void InGameManager::InGame_Recv_OtherUserMoveInfo(char * _buf, int _dataprotocol)
{
	char* ptr_buf = _buf;

	char data[BUFSIZE];
	char code[CHARACTERCODESIZE];
	char* ptr_data = data;
	int size = 0;
	int len = 0;
	float xyz[3];

	memset(data, 0, BUFSIZE);
	memset(code, 0, CHARACTERCODESIZE);

	// �ڵ� ������
	memcpy(&len, ptr_buf, sizeof(int));
	ptr_buf += sizeof(int);
	size += sizeof(int);
	memcpy(ptr_data, &len, sizeof(int));
	ptr_data += sizeof(int);

	// �ڵ�
	memcpy(code, ptr_buf, len);
	ptr_buf += len;
	size += len;
	memcpy(ptr_data, code, len);
	ptr_data += len;

	// position x, y, z
	memcpy(xyz, ptr_buf, sizeof(float) * 3);
	ptr_buf += sizeof(float) * 3;
	size += sizeof(float) * 3;
	memcpy(ptr_data, xyz, sizeof(float) * 3);
	ptr_data += sizeof(float) * 3;

	StorageManager::GetInstance()->PushData(_dataprotocol, data, size);
}

// �ٸ� ���� ȸ��
void InGameManager::InGame_Recv_OtherUserRotation(char * _buf)
{
	char* ptr_buf = _buf;

	char data[BUFSIZE];
	char code[CHARACTERCODESIZE];
	char* ptr_data = data;
	int size = 0;
	int len = 0;
	float rot_xyz[3];

	memset(code, 0, CHARACTERCODESIZE);

	// �ڵ� ������
	memcpy(&len, ptr_buf, sizeof(int));
	ptr_buf += sizeof(int);
	size += sizeof(int);
	memcpy(ptr_data, &len, sizeof(int));
	ptr_data += sizeof(int);

	// �ڵ�
	memcpy(code, ptr_buf, len);
	ptr_buf += len;
	size += len;
	memcpy(ptr_data, code, len);
	ptr_data += len;

	// rotation x, y, z
	memcpy(rot_xyz, ptr_buf, sizeof(float) * 3);
	ptr_buf += sizeof(float) * 3;
	size += sizeof(float) * 3;
	memcpy(ptr_data, rot_xyz, sizeof(float) * 3);
	ptr_data += sizeof(float) * 3;

	StorageManager::GetInstance()->PushData(PGAMEDATA_PLAYER_OTHERROTATION, data, size);
}

// �ٸ� ���� ��������
void InGameManager::InGame_Recv_OtherUserLeave(char * _buf)
{
	char* ptr_buf = _buf;

	char data[BUFSIZE];
	char code[CHARACTERCODESIZE];
	char* ptr_data = data;
	int size = 0;
	int len = 0;

	memset(code, 0, CHARACTERCODESIZE);

	// �ڵ� ������
	memcpy(&len, ptr_buf, sizeof(int));
	ptr_buf += sizeof(int);
	size += sizeof(int);
	memcpy(ptr_data, &len, sizeof(int));
	ptr_data += sizeof(int);

	// �ڵ�
	memcpy(code, ptr_buf, len);
	ptr_buf += len;
	size += len;
	memcpy(ptr_data, code, len);
	ptr_data += len;

	StorageManager::GetInstance()->PushData(PGAMEDATA_LEAVE_PLAYER, data, size);
}

// �ٸ� ���� ���� �ߴٴ� ����
void InGameManager::InGame_Recv_OtherUser_Start_Jump(char * _buf)
{
	char* ptr_buf = _buf;

	char data[BUFSIZE];
	char code[CHARACTERCODESIZE];
	char* ptr_data = data;
	int size = 0;
	int len = 0;

	memset(code, 0, CHARACTERCODESIZE);

	// �ڵ� ������
	memcpy(&len, ptr_buf, sizeof(int));
	ptr_buf += sizeof(int);
	size += sizeof(int);
	memcpy(ptr_data, &len, sizeof(int));
	ptr_data += sizeof(int);

	// �ڵ�
	memcpy(code, ptr_buf, len);
	ptr_buf += len;
	size += len;
	memcpy(ptr_data, code, len);
	ptr_data += len;

	StorageManager::GetInstance()->PushData(PGAMEDATA_PLAYER_OTHER_START_JUMP, data, size);
}

// �ٸ� ���� ���� �ߴٴ� ����
void InGameManager::InGame_Recv_OtherUser_End_Jump(char * _buf)
{
	char* ptr_buf = _buf;

	char data[BUFSIZE];
	char code[CHARACTERCODESIZE];
	char* ptr_data = data;
	int size = 0;
	int len = 0;

	memset(code, 0, CHARACTERCODESIZE);

	// �ڵ� ������
	memcpy(&len, ptr_buf, sizeof(int));
	ptr_buf += sizeof(int);
	size += sizeof(int);
	memcpy(ptr_data, &len, sizeof(int));
	ptr_data += sizeof(int);

	// �ڵ�
	memcpy(code, ptr_buf, len);
	ptr_buf += len;
	size += len;
	memcpy(ptr_data, code, len);
	ptr_data += len;

	StorageManager::GetInstance()->PushData(PGAMEDATA_PLAYER_OTHER_END_JUMP, data, size);
}

// �ٸ� ���� �����ߴٴ� ����
void InGameManager::InGame_Recv_OtherUser_Attack(char * _buf)
{
	char* ptr_buf = _buf;

	char data[BUFSIZE];
	char code[CHARACTERCODESIZE];
	char* ptr_data = data;
	int size = 0;
	int len = 0;
	int attacknum = 0;

	memset(code, 0, CHARACTERCODESIZE);

	// �ڵ� ������
	memcpy(&len, ptr_buf, sizeof(int));
	ptr_buf += sizeof(int);
	size += sizeof(int);
	memcpy(ptr_data, &len, sizeof(int));
	ptr_data += sizeof(int);

	// �ڵ�
	memcpy(code, ptr_buf, len);
	ptr_buf += len;
	size += len;
	memcpy(ptr_data, code, len);
	ptr_data += len;

	// ���ݹ�ȣ
	memcpy(&attacknum, ptr_buf, sizeof(int));
	ptr_buf += sizeof(int);
	size += sizeof(int);
	memcpy(ptr_data, &attacknum, sizeof(int));
	ptr_data += sizeof(int);

	StorageManager::GetInstance()->PushData(PGAMEDATA_PLAYER_ATTACK, data, size);
}

// ä�� ����
void InGameManager::InGame_Recv_ChannelInfo(char * _buf)
{
	char* ptr = _buf;

	char data[BUFSIZE];
	char* ptr_data = data;
	int size = 0;

	int channelnum = 0;
	int channelusercount = 0;

	float f_channelnum = 0;
	float f_channelusercount = 0;

	for (int i = 0; i < 6; i++)
	{
		// ä�ι�ȣ
		memcpy(&channelnum, ptr, sizeof(int));
		ptr += sizeof(int);
		// �ش� ä�� ������
		memcpy(&channelusercount, ptr, sizeof(int));
		ptr += sizeof(int);

		// ����ȯ
		f_channelnum = (float)channelnum;
		f_channelusercount = (float)channelusercount;

		// data�� ä�ι�ȣ ��ŷ
		memcpy(ptr_data, &f_channelnum, sizeof(float));
		ptr_data += sizeof(float);
		size += sizeof(float);
		// data�� ä�� ������ ��ŷ
		memcpy(ptr_data, &f_channelusercount, sizeof(float));
		ptr_data += sizeof(float);
		size += sizeof(float);
	}

	StorageManager::GetInstance()->PushData(PGAMEDATA_CHANNEL_INFO, data, size);
}

// ĳ���� ����ȭ������ �޾�����
void InGameManager::InGame_Recv_CharacterSelect()
{
	StorageManager::GetInstance()->PushData(PGAMEDATA_MENU_CHARACTER_SELECT, 0, 0);
}

// �α׾ƿ� �޾�����
void InGameManager::InGame_Recv_Logout()
{
	StorageManager::GetInstance()->PushData(PGAMEDATA_MENU_LOGOUT, 0, 0);
}

// ä���̵� ���
void InGameManager::InGame_Recv_ChannelChange(char * _buf)
{
	char* ptr = _buf;

	char data[BUFSIZE];
	char* ptr_data = data;
	int size = 0;

	bool result = false;
	int channelnum = 0;

	// ��� ����
	memcpy(&result, ptr, sizeof(bool));
	ptr += sizeof(bool);

	if (result)
	{
		// �ٲ� ä�� ����
		memcpy(&channelnum, ptr, sizeof(int));
		ptr += sizeof(int);

		// ��� ��ŷ
		memcpy(ptr_data, &result, sizeof(bool));
		ptr_data += sizeof(bool);
		size += sizeof(bool);

		// �ٲ� ä�� ��ŷ
		memcpy(ptr_data, &channelnum, sizeof(int));
		ptr_data += sizeof(int);
		size += sizeof(int);
	}
	else
	{
		// ��� ��ŷ
		memcpy(ptr_data, &result, sizeof(bool));
		ptr_data += sizeof(bool);
		size += sizeof(bool);
	}

	StorageManager::GetInstance()->PushData(PGAMEDATA_CHANNEL_REQ_CHANGE, data, size);
}

// ��Ƽ �ʴ� ����
void InGameManager::InGame_Recv_Invite(char * _buf)
{
	char* ptr = _buf;

	char data[BUFSIZE];
	memset(data, 0, sizeof(BUFSIZE));
	char* ptr_data = data;
	int size = 0;

	char code[CHARACTERCODESIZE];
	char nick[NICKNAMESIZE];
	int partyroom = 0;
	int codelen = 0;
	int nicklen = 0;

	memset(code, 0, CHARACTERCODESIZE);
	memset(nick, 0, NICKNAMESIZE);

	// �ڵ����
	memcpy(&codelen, ptr, sizeof(int));
	ptr += sizeof(int);
	// �ڵ�
	memcpy(code, ptr, codelen);
	ptr += codelen;
	// �г��ӱ���
	memcpy(&nicklen, ptr, sizeof(int));
	ptr += sizeof(int);
	//�г���
	memcpy(nick, ptr, nicklen);
	ptr += nicklen;
	// ��Ƽ��ȣ
	memcpy(&partyroom, ptr, sizeof(int));
	ptr += sizeof(int);

	// data�� �ڵ���� ��ŷ
	memcpy(ptr_data, &codelen, sizeof(int));
	ptr_data += sizeof(int);
	size += sizeof(int);
	// data�� �ڵ� ��ŷ
	memcpy(ptr_data, code, codelen);
	ptr_data += codelen;
	size += codelen;
	// data�� �г��ӱ��� ��ŷ
	memcpy(ptr_data, &nicklen, sizeof(int));
	ptr_data += sizeof(int);
	size += sizeof(int);
	// data�� �г��� ��ŷ
	memcpy(ptr_data, nick, nicklen);
	ptr_data += nicklen;
	size += nicklen;
	// data�� ��Ƽ��ȣ ��ŷ
	memcpy(ptr_data, &partyroom, sizeof(int));
	ptr_data += sizeof(int);
	size += sizeof(int);

	StorageManager::GetInstance()->PushData(PGAMEDATA_PARTY_INVITE, data, size);
}

// ��Ƽ �ʴ� �������
void InGameManager::InGame_Recv_Invite_Result(char * _buf)
{
	char* ptr = _buf;

	char data[BUFSIZE];
	memset(data, 0, sizeof(BUFSIZE));
	char* ptr_data = data;
	int size = 0;

	bool result = false;

	// ���
	memcpy(&result, ptr, sizeof(bool));
	ptr += sizeof(bool);

	// data�� ���
	memcpy(ptr_data, &result, sizeof(bool));
	ptr_data += sizeof(bool);
	size += sizeof(bool);

	StorageManager::GetInstance()->PushData(PGAMEDATA_PARTY_INVITE_RESULT, data, size);
}

// ��Ƽ ���� ���
void InGameManager::InGame_Recv_Join_Result(char * _buf)
{
	char* ptr = _buf;

	char data[BUFSIZE];
	memset(data, 0, sizeof(BUFSIZE));
	char* ptr_data = data;
	int size = 0;

	bool result = false;

	// ���
	memcpy(&result, ptr, sizeof(bool));
	ptr += sizeof(bool);

	// data�� ���
	memcpy(ptr_data, &result, sizeof(bool));
	ptr_data += sizeof(bool);
	size += sizeof(bool);

	StorageManager::GetInstance()->PushData(PGAMEDATA_PARTY_JOIN_RESULT, data, size);
}

void InGameManager::InGame_Recv_Party_User_Info(char * _buf)
{
	int partynum = 0;
	int count = 0;
	char* ptr_buf = _buf;

	char data[BUFSIZE];
	memset(data, 0, sizeof(data));
	char* ptr_data = data;
	int size = 0;

	int codelen = 0;
	int nicklen = 0;
	int jobcode = 0;
	bool leader = false;
	float hp = 0;
	float mp = 0;
	char code[CHARACTERCODESIZE];
	char nick[NICKNAMESIZE];

	memcpy(&partynum, ptr_buf, sizeof(int));
	ptr_buf += sizeof(int);
	memcpy(ptr_data, &partynum, sizeof(int));
	ptr_data += sizeof(int);
	size += sizeof(int);

	memcpy(&count, ptr_buf, sizeof(int));
	ptr_buf += sizeof(int);
	memcpy(ptr_data, &count, sizeof(int));
	ptr_data += sizeof(int);
	size += sizeof(int);

	StorageManager::GetInstance()->PushData(PGAMEDATA_PARTY_INFO, data, size);

	for (int i = 0; i < count; i++)
	{
		memset(data, 0, sizeof(data));
		memset(nick, 0, sizeof(nick));
		memset(code, 0, sizeof(code));
		ptr_data = data;
		size = 0;
		codelen = 0;
		nicklen = 0;
		jobcode = 0;
		hp = 0;
		mp = 0;

		// �ڵ� ������
		memcpy(&codelen, ptr_buf, sizeof(int));
		ptr_buf += sizeof(int);
		size += sizeof(int);
		memcpy(ptr_data, &codelen, sizeof(int));
		ptr_data += sizeof(int);

		// �ڵ�
		memcpy(code, ptr_buf, codelen);
		ptr_buf += codelen;
		size += codelen;
		memcpy(ptr_data, code, codelen);
		ptr_data += codelen;

		// ĳ���� �����ڵ�
		memcpy(&jobcode, ptr_buf, sizeof(int));
		ptr_buf += sizeof(int);
		size += sizeof(int);
		memcpy(ptr_data, &jobcode, sizeof(int));
		ptr_data += sizeof(int);

		// �г��� ������
		memcpy(&nicklen, ptr_buf, sizeof(int));
		ptr_buf += sizeof(int);
		size += sizeof(int);
		memcpy(ptr_data, &nicklen, sizeof(int));
		ptr_data += sizeof(int);

		// �г���
		memcpy(nick, ptr_buf, nicklen);
		ptr_buf += nicklen;
		size += nicklen;
		memcpy(ptr_data, nick, nicklen);
		ptr_data += nicklen;

		// HP
		memcpy(&hp, ptr_buf, sizeof(float));
		ptr_buf += sizeof(float);
		size += sizeof(float);
		memcpy(ptr_data, &hp, sizeof(float));
		ptr_data += sizeof(float);

		// MP
		memcpy(&mp, ptr_buf, sizeof(float));
		ptr_buf += sizeof(float);
		size += sizeof(float);
		memcpy(ptr_data, &mp, sizeof(float));
		ptr_data += sizeof(float);

		// �������� �ƴ���
		memcpy(&leader, ptr_buf, sizeof(bool));
		ptr_buf += sizeof(bool);
		size += sizeof(bool);
		memcpy(ptr_data, &leader, sizeof(bool));
		ptr_data += sizeof(bool);

		StorageManager::GetInstance()->PushData(PGAMEDATA_PARTY_USER_INFO, data, size);
	}

}

// ��Ƽ ���� ����
void InGameManager::InGame_Recv_Kick()
{
	StorageManager::GetInstance()->PushData(PGAMEDATA_PARTY_KICK, 0, 0);
}

// ��Ƽ ������� ���� ���� ����
void InGameManager::InGame_Recv_Kick_User_Info(char * _buf)
{
	char* ptr = _buf;

	char data[BUFSIZE];
	memset(data, 0, sizeof(BUFSIZE));
	char* ptr_data = data;
	int size = 0;

	char code[CHARACTERCODESIZE];
	int codelen = 0;

	memset(code, 0, CHARACTERCODESIZE);

	// �ڵ����
	memcpy(&codelen, ptr, sizeof(int));
	ptr += sizeof(int);
	// �ڵ�
	memcpy(code, ptr, codelen);
	ptr += codelen;

	// data�� �ڵ���� ��ŷ
	memcpy(ptr_data, &codelen, sizeof(int));
	ptr_data += sizeof(int);
	size += sizeof(int);
	// data�� �ڵ� ��ŷ
	memcpy(ptr_data, code, codelen);
	ptr_data += codelen;
	size += codelen;

	StorageManager::GetInstance()->PushData(PGAMEDATA_PARTY_USER_KICK_INFO, data, size);
}

// ��Ƽ ������
void InGameManager::InGame_Recv_Kick_Result(char * _buf)
{
	char* ptr = _buf;

	char data[BUFSIZE];
	memset(data, 0, sizeof(BUFSIZE));
	char* ptr_data = data;
	int size = 0;

	bool result = false;
	char code[CHARACTERCODESIZE];
	int codelen = 0;

	memset(code, 0, CHARACTERCODESIZE);

	// ���
	memcpy(&result, ptr, sizeof(bool));
	ptr += sizeof(bool);

	if (result == false)
	{
		// data�� ��� ��ŷ
		memcpy(ptr_data, &result, sizeof(bool));
		ptr_data += sizeof(bool);
		size += sizeof(bool);

		StorageManager::GetInstance()->PushData(PGAMEDATA_PARTY_USER_KICK_RESULT, data, size);
	}
	else
	{
		// �ڵ����
		memcpy(&codelen, ptr, sizeof(int));
		ptr += sizeof(int);
		// �ڵ�
		memcpy(code, ptr, codelen);
		ptr += codelen;

		// data�� ��� ��ŷ
		memcpy(ptr_data, &result, sizeof(bool));
		ptr_data += sizeof(bool);
		size += sizeof(bool);
		// data�� �ڵ���� ��ŷ
		memcpy(ptr_data, &codelen, sizeof(int));
		ptr_data += sizeof(int);
		size += sizeof(int);
		// data�� �ڵ� ��ŷ
		memcpy(ptr_data, code, codelen);
		ptr_data += codelen;
		size += codelen;

		StorageManager::GetInstance()->PushData(PGAMEDATA_PARTY_USER_KICK_RESULT, data, size);
	}
}

// ��Ƽ Ż����� ���� ��������
void InGameManager::InGame_Recv_Leave_User_Info(char * _buf)
{
	char* ptr = _buf;

	char data[BUFSIZE];
	memset(data, 0, sizeof(BUFSIZE));
	char* ptr_data = data;
	int size = 0;

	char code[CHARACTERCODESIZE];
	int codelen = 0;

	memset(code, 0, CHARACTERCODESIZE);

	// �ڵ����
	memcpy(&codelen, ptr, sizeof(int));
	ptr += sizeof(int);
	// �ڵ�
	memcpy(code, ptr, codelen);
	ptr += codelen;

	// data�� �ڵ���� ��ŷ
	memcpy(ptr_data, &codelen, sizeof(int));
	ptr_data += sizeof(int);
	size += sizeof(int);
	// data�� �ڵ� ��ŷ
	memcpy(ptr_data, code, codelen);
	ptr_data += codelen;
	size += codelen;

	StorageManager::GetInstance()->PushData(PGAMEDATA_PARTY_LEAVE_INFO, data, size);
}

// ��Ƽ Ż�� ���
void InGameManager::InGame_Recv_Leave_Result(char * _buf)
{
	char* ptr = _buf;

	char data[BUFSIZE];
	memset(data, 0, sizeof(BUFSIZE));
	char* ptr_data = data;
	int size = 0;

	bool result = false;

	// ���
	memcpy(&result, ptr, sizeof(bool));
	ptr += sizeof(bool);

	// data�� ��� ��ŷ
	memcpy(ptr_data, &result, sizeof(bool));
	ptr_data += sizeof(bool);
	size += sizeof(bool);

	StorageManager::GetInstance()->PushData(PGAMEDATA_PARTY_LEAVE_RESULT, data, size);
}

// ��Ƽ�� �������
void InGameManager::InGame_Recv_PartyRoom_Remove(char * _buf)
{
	StorageManager::GetInstance()->PushData(PGAMEDATA_PARTY_PARTYROOM_REMOVE, 0, 0);
}

// ���ο� ��Ƽ ���� ����
void InGameManager::InGame_Recv_PartyRoom_Leader_Info(char * _buf)
{
	char* ptr = _buf;

	char data[BUFSIZE];
	memset(data, 0, sizeof(BUFSIZE));
	char* ptr_data = data;
	int size = 0;

	char oldcode[CHARACTERCODESIZE];
	char newcode[CHARACTERCODESIZE];
	int oldcodelen = 0;
	int newcodelen = 0;

	memset(oldcode, 0, CHARACTERCODESIZE);
	memset(newcode, 0, CHARACTERCODESIZE);

	// �� ��Ƽ ���� �ڵ����
	memcpy(&oldcodelen, ptr, sizeof(int));
	ptr += sizeof(int);
	// �� ��Ƽ ���� �ڵ�
	memcpy(oldcode, ptr, oldcodelen);
	ptr += oldcodelen;

	// �� ��Ƽ ���� �ڵ����
	memcpy(&newcodelen, ptr, sizeof(int));
	ptr += sizeof(int);
	// �� ��Ƽ ���� �ڵ�
	memcpy(newcode, ptr, newcodelen);
	ptr += newcodelen;

	// data�� �� ��Ƽ ���� �ڵ���� ��ŷ
	memcpy(ptr_data, &oldcodelen, sizeof(int));
	ptr_data += sizeof(int);
	size += sizeof(int);
	// data�� �� ��Ƽ ���� �ڵ� ��ŷ
	memcpy(ptr_data, oldcode, oldcodelen);
	ptr_data += oldcodelen;
	size += oldcodelen;

	// data�� �� ��Ƽ ���� �ڵ���� ��ŷ
	memcpy(ptr_data, &newcodelen, sizeof(int));
	ptr_data += sizeof(int);
	size += sizeof(int);
	// data�� �� ��Ƽ ���� �ڵ� ��ŷ
	memcpy(ptr_data, newcode, newcodelen);
	ptr_data += newcodelen;
	size += newcodelen;

	StorageManager::GetInstance()->PushData(PGAMEDATA_PARTY_LEADER_INFO, data, size);
}

// ��Ƽ ���� ���� ���
void InGameManager::InGame_Recv_PartyRoom_Leader_Delegate_Result(char * _buf)
{
	char* ptr = _buf;

	char data[BUFSIZE];
	memset(data, 0, sizeof(BUFSIZE));
	char* ptr_data = data;
	int size = 0;

	bool result = false;
	char code[CHARACTERCODESIZE];
	int codelen = 0;

	memset(code, 0, CHARACTERCODESIZE);

	// ���
	memcpy(&result, ptr, sizeof(bool));
	ptr += sizeof(bool);

	if (result == false)
	{
		// data�� ��� ��ŷ
		memcpy(ptr_data, &result, sizeof(bool));
		ptr_data += sizeof(bool);
		size += sizeof(bool);

		StorageManager::GetInstance()->PushData(PGAMEDATA_PARTY_LEADER_DELEGATE_RESULT, data, size);
	}
	else
	{
		// �ڵ����
		memcpy(&codelen, ptr, sizeof(int));
		ptr += sizeof(int);
		// �ڵ�
		memcpy(code, ptr, codelen);
		ptr += codelen;

		// data�� ��� ��ŷ
		memcpy(ptr_data, &result, sizeof(bool));
		ptr_data += sizeof(bool);
		size += sizeof(bool);
		// data�� �ڵ���� ��ŷ
		memcpy(ptr_data, &codelen, sizeof(int));
		ptr_data += sizeof(int);
		size += sizeof(int);
		// data�� �ڵ� ��ŷ
		memcpy(ptr_data, code, codelen);
		ptr_data += codelen;
		size += codelen;

		StorageManager::GetInstance()->PushData(PGAMEDATA_PARTY_LEADER_DELEGATE_RESULT, data, size);
	}
}

// ���� ���� ���
void InGameManager::InGame_Recv_Leave_Dungeon_Enter_Result(char * _buf)
{
	char* ptr_buf = _buf;

	char data[BUFSIZE];
	memset(data, 0, BUFSIZE);
	char* ptr_data = data;

	char code[CHARACTERCODESIZE];
	int len = 0;
	int size = 0;
	int count = 0;

	float xyz[3];

	memcpy(&count, ptr_buf, sizeof(int));
	ptr_buf += sizeof(int);

	StorageManager::GetInstance()->PushData(PGAMEDATA_PARTY_DUNGEON_ENTER_RESULT, (void*)&count, sizeof(int));

	for (int i = 0; i < count; i++)
	{
		memset(data, 0, sizeof(data));
		memset(code, 0, sizeof(code));
		ptr_data = data;
		size = 0;
		len = 0;

		// �ڵ� ������
		memcpy(&len, ptr_buf, sizeof(int));
		ptr_buf += sizeof(int);
		// �ڵ�
		memcpy(code, ptr_buf, len);
		ptr_buf += len;
		// ������ġ ����
		memcpy(xyz, ptr_buf, sizeof(float) * 3);
		ptr_buf += sizeof(float) * 3;

		// data�� �ڵ� ����
		memcpy(ptr_data, &len, sizeof(int));
		ptr_data += sizeof(int);
		size += sizeof(int);
		// data�� �ڵ�
		memcpy(ptr_data, code, len);
		ptr_data += len;
		size += len;
		// data�� ������ġ ��ŷ.x
		memcpy(ptr_data, &xyz[0], sizeof(float));
		ptr_data += sizeof(float);
		size += sizeof(float);
		// data�� ������ġ ��ŷ.y
		memcpy(ptr_data, &xyz[1], sizeof(float));
		ptr_data += sizeof(float);
		size += sizeof(float);
		// data�� ������ġ ��ŷ.z
		memcpy(ptr_data, &xyz[2], sizeof(float));
		ptr_data += sizeof(float);
		size += sizeof(float);

		StorageManager::GetInstance()->PushData(PGAMEDATA_PARTY_DUNGEON_SPAWNINFO, data, size);
	}
}

// ���� ���� ���
void InGameManager::InGame_Recv_Leave_Dungeon_Leave_Result(char * _buf)
{
	char* ptr = _buf;

	char data[BUFSIZE];
	memset(data, 0, sizeof(BUFSIZE));
	char* ptr_data = data;
	int size = 0;

	int channelnum = 0;

	// ä�ι�ȣ
	memcpy(&channelnum, ptr, sizeof(int));
	ptr += sizeof(int);

	// data�� ä�ι�ȣ ��ŷ
	memcpy(ptr_data, &channelnum, sizeof(int));
	ptr_data += sizeof(int);
	size += sizeof(int);

	StorageManager::GetInstance()->PushData(PGAMEDATA_PARTY_DUNGEON_LEAVE_RESULT, data, size);
}

// �������� ���� ���
void InGameManager::InGame_Recv_Stage_Enter_Result(char * _buf)
{
	char* ptr_buf = _buf;

	char data[BUFSIZE];
	memset(data, 0, BUFSIZE);
	char* ptr_data = data;

	char code[CHARACTERCODESIZE];
	int len = 0;
	int size = 0;
	int count = 0;

	float xyz[3];

	memcpy(&count, ptr_buf, sizeof(int));
	ptr_buf += sizeof(int);

	//StorageManager::GetInstance()->PushData(PGAMEDATA_PARTY_DUNGEON_STAGE_ENTER_RESULT, (void*)&count, sizeof(int));

	for (int i = 0; i < count; i++)
	{
		memset(data, 0, sizeof(data));
		memset(code, 0, sizeof(code));
		ptr_data = data;
		size = 0;
		len = 0;

		// �ڵ� ������
		memcpy(&len, ptr_buf, sizeof(int));
		ptr_buf += sizeof(int);
		// �ڵ�
		memcpy(code, ptr_buf, len);
		ptr_buf += len;
		// ������ġ ����
		memcpy(xyz, ptr_buf, sizeof(float) * 3);
		ptr_buf += sizeof(float) * 3;

		// data�� �ڵ� ����
		memcpy(ptr_data, &len, sizeof(int));
		ptr_data += sizeof(int);
		size += sizeof(int);
		// data�� �ڵ�
		memcpy(ptr_data, code, len);
		ptr_data += len;
		size += len;
		// data�� ������ġ ��ŷ.x
		memcpy(ptr_data, &xyz[0], sizeof(float));
		ptr_data += sizeof(float);
		size += sizeof(float);
		// data�� ������ġ ��ŷ.y
		memcpy(ptr_data, &xyz[1], sizeof(float));
		ptr_data += sizeof(float);
		size += sizeof(float);
		// data�� ������ġ ��ŷ.z
		memcpy(ptr_data, &xyz[2], sizeof(float));
		ptr_data += sizeof(float);
		size += sizeof(float);

		StorageManager::GetInstance()->PushData(PGAMEDATA_PARTY_DUNGEON_STAGE_SPAWNINFO, data, size);
	}
}

// �������� ������ �޴� ��������(�ʱ�ȭ����)
void InGameManager::InGame_Recv_Stage_MonsterInfo(char * _buf)
{
	char* ptr_buf = _buf;

	char data[BUFSIZE];
	memset(data, 0, BUFSIZE);
	char* ptr_data = data;
	int size = 0;

	int code = 0;
	int monster_num = 0;
	int monster_tpyes_count = 0;
	float monster_spawn_time = 0;

	float xyz[3] = { 0 };

	// ���� ���� ����
	memcpy(&monster_tpyes_count, ptr_buf, sizeof(int));
	ptr_buf += sizeof(int);

	StorageManager::GetInstance()->PushData(PGAMEDATA_STAGE_MONSTER_TPYES_COUNT, (void*)&monster_tpyes_count, sizeof(int));

	// ���� ���� �ð�
	memcpy(&monster_spawn_time, ptr_buf, sizeof(float));
	ptr_buf += sizeof(float);

	StorageManager::GetInstance()->PushData(PGAMEDATA_STAGE_MONSTER_SPAWN_TIME, (void*)&monster_spawn_time, sizeof(int));

	for (int i = 0; i < monster_tpyes_count; i++)
	{
		ptr_data = data;
		code = 0;
		monster_num = 0;
		size = 0;

		// ���� �ڵ�
		memcpy(&code, ptr_buf, sizeof(int));
		ptr_buf += sizeof(int);
		// ���� ����
		memcpy(&monster_num, ptr_buf, sizeof(int));
		ptr_buf += sizeof(int);
		// ������ġ
		memcpy(xyz, ptr_buf, sizeof(float) * 3);
		ptr_buf += sizeof(float) * 3;

		// data�� ���� �ڵ� ��ŷ
		memcpy(ptr_data, &code, sizeof(int));
		ptr_data += sizeof(int);
		size += sizeof(int);
		// data�� ���� ���� ��ŷ
		memcpy(ptr_data, &monster_num, sizeof(int));
		ptr_data += sizeof(int);
		size += sizeof(int);
		// data�� ������ġ ��ŷ.x
		memcpy(ptr_data, &xyz[0], sizeof(float));
		ptr_data += sizeof(float);
		size += sizeof(float);
		// data�� ������ġ ��ŷ.y
		memcpy(ptr_data, &xyz[1], sizeof(float));
		ptr_data += sizeof(float);
		size += sizeof(float);
		// data�� ������ġ ��ŷ.z
		memcpy(ptr_data, &xyz[2], sizeof(float));
		ptr_data += sizeof(float);
		size += sizeof(float);

		StorageManager::GetInstance()->PushData(PGAMEDATA_STAGE_MONSTER_INFO, data, size);
	}
}

// ���� �̵�����
void InGameManager::InGame_Recv_Monster_MoveInfo(char * _buf)
{
	int count = 0;
	char* ptr_buf = _buf;

	char data[BUFSIZE];
	char* ptr_data = data;
	memset(data, 0, sizeof(data));
	int size = 0;

	int code = 0;
	int num = 0;
	float xyz[3];

	// ���� �ڵ�
	memcpy(&code, ptr_buf, sizeof(int));
	ptr_buf += sizeof(int);
	size += sizeof(int);
	memcpy(ptr_data, &code, sizeof(int));
	ptr_data += sizeof(int);

	// ĳ���� �����ڵ�
	memcpy(&num, ptr_buf, sizeof(int));
	ptr_buf += sizeof(int);
	size += sizeof(int);
	memcpy(ptr_data, &num, sizeof(int));
	ptr_data += sizeof(int);

	// position x, y, z
	memcpy(xyz, ptr_buf, sizeof(float) * 3);
	ptr_buf += sizeof(float) * 3;
	size += sizeof(float) * 3;
	memcpy(ptr_data, xyz, sizeof(float) * 3);
	ptr_data += sizeof(float) * 3;

	StorageManager::GetInstance()->PushData(PGAMEDATA_MONSTER_MOVE_INFO, data, size);
}

// ���� �ǰ�����
void InGameManager::InGame_Recv_Monster_has_been_Attacked(char * _buf)
{
	char* ptr_buf = _buf;

	char data[BUFSIZE];
	memset(data, 0, sizeof(data));
	char* ptr_data = data;
	int size = 0;

	bool result = false;
	bool check = false;

	int code = 0;
	int num = 0;
	int damage = 0;

	// �ǰ� ���
	memcpy(&result, ptr_buf, sizeof(bool));
	ptr_buf += sizeof(bool);
	memcpy(ptr_data, &result, sizeof(bool));
	ptr_data += sizeof(bool);
	size += sizeof(bool);

	if (result)
	{		
		// ���� �ڵ�
		memcpy(&code, ptr_buf, sizeof(int));
		ptr_buf += sizeof(int);
		memcpy(ptr_data, &code, sizeof(int));
		ptr_data += sizeof(int);
		size += sizeof(int);

		// ���� ��ȣ
		memcpy(&num, ptr_buf, sizeof(int));
		ptr_buf += sizeof(int);
		memcpy(ptr_data, &num, sizeof(int));
		ptr_data += sizeof(int);
		size += sizeof(int);

		// ������
		memcpy(&damage, ptr_buf, sizeof(int));
		ptr_buf += sizeof(int);
		memcpy(ptr_data, &damage, sizeof(int));
		ptr_data += sizeof(int);
		size += sizeof(int);

		// ����ߴ���
		memcpy(&check, ptr_buf, sizeof(bool));
		ptr_buf += sizeof(bool);
		memcpy(ptr_data, &check, sizeof(bool));
		ptr_data += sizeof(bool);
		size += sizeof(bool);
	}

	StorageManager::GetInstance()->PushData(PGAMEDATA_USER_ATTACKED_THE_MONSTER_RESULT, data, size);
}

// �ٸ� ���� ���� �ǰ�����
void InGameManager::InGame_Recv_OtherMonster_has_been_Attack(char * _buf)
{
	int count = 0;
	char* ptr_buf = _buf;

	char data[BUFSIZE];
	memset(data, 0, sizeof(data));
	char* ptr_data = data;
	int size = 0;

	bool check = false;
	int code = 0;
	int num = 0;
	int damage = 0;

	// ���� �ڵ�
	memcpy(&code, ptr_buf, sizeof(int));
	ptr_buf += sizeof(int);
	memcpy(ptr_data, &code, sizeof(int));
	ptr_data += sizeof(int);
	size += sizeof(int);

	// ���� ��ȣ
	memcpy(&num, ptr_buf, sizeof(int));
	ptr_buf += sizeof(int);
	memcpy(ptr_data, &num, sizeof(int));
	ptr_data += sizeof(int);
	size += sizeof(int);

	// ������
	memcpy(&damage, ptr_buf, sizeof(int));
	ptr_buf += sizeof(int);
	memcpy(ptr_data, &damage, sizeof(int));
	ptr_data += sizeof(int);
	size += sizeof(int);

	// ����ߴ���
	memcpy(&check, ptr_buf, sizeof(bool));
	ptr_buf += sizeof(bool);
	memcpy(ptr_data, &check, sizeof(bool));
	ptr_data += sizeof(bool);
	size += sizeof(bool);

	StorageManager::GetInstance()->PushData(PGAMEDATA_OTHERUSER_ATTACKED_THE_MONSTER, data, size);
}

// ���� �ǰ�����
void InGameManager::InGame_Recv_UnderAttack(char * _buf)
{
	char* ptr_buf = _buf;

	char data[BUFSIZE];
	memset(data, 0, sizeof(data));
	char* ptr_data = data;
	int size = 0;

	bool result = false;
	bool is_live = false;
	int damage = 0;

	// �ǰ� ���
	memcpy(&result, ptr_buf, sizeof(bool));
	ptr_buf += sizeof(bool);
	memcpy(ptr_data, &result, sizeof(bool));
	ptr_data += sizeof(bool);
	size += sizeof(bool);

	if (result)
	{
		// ������
		memcpy(&damage, ptr_buf, sizeof(int));
		ptr_buf += sizeof(int);
		memcpy(ptr_data, &damage, sizeof(int));
		ptr_data += sizeof(int);
		size += sizeof(int);

		// ��������
		memcpy(&is_live, ptr_buf, sizeof(bool));
		ptr_buf += sizeof(bool);
		memcpy(ptr_data, &is_live, sizeof(bool));
		ptr_data += sizeof(bool);
		size += sizeof(bool);
	}

	StorageManager::GetInstance()->PushData(PGAMEDATA_MONSTER_ATTACKED_THE_USER_RESULT, data, size);
}

// �ٸ� ���� �ǰ�����
void InGameManager::InGame_Recv_Other_UnderAttack(char * _buf)
{
	char* ptr_buf = _buf;

	char data[BUFSIZE];
	memset(data, 0, sizeof(data));
	char* ptr_data = data;
	int size = 0;

	char code[CHARACTERCODESIZE];
	int len = 0;
	int damage = 0;
	bool is_live = false;
	memset(code, 0, sizeof(code));

	// �ڵ� ����
	memcpy(&len, ptr_buf, sizeof(int));
	ptr_buf += sizeof(int);
	memcpy(ptr_data, &len, sizeof(int));
	ptr_data += sizeof(int);
	size += sizeof(int);

	// �ڵ�
	memcpy(code, ptr_buf, len);
	ptr_buf += len;
	memcpy(ptr_data, code, len);
	ptr_data += len;
	size += len;

	// ������
	memcpy(&damage, ptr_buf, sizeof(int));
	ptr_buf += sizeof(int);
	memcpy(ptr_data, &damage, sizeof(int));
	ptr_data += sizeof(int);
	size += sizeof(int);

	// ��������
	memcpy(&is_live, ptr_buf, sizeof(bool));
	ptr_buf += sizeof(bool);
	memcpy(ptr_data, &is_live, sizeof(bool));
	ptr_data += sizeof(bool);
	size += sizeof(bool);

	StorageManager::GetInstance()->PushData(PGAMEDATA_MONSTER_ATTACKED_THE_OTHERUSER, data, size);
}

//// ���� ���� �ִϸ��̼�
//void InGameManager::InGame_Recv_Monster_Attack_Animation(char * _buf)
//{
//	char* ptr_buf = _buf;
//
//	char data[BUFSIZE];
//	memset(data, 0, sizeof(data));
//	char* ptr_data = data;
//	int size = 0;
//
//	int code = 0;
//	int num = 0;
//	int attacknum = 0;
//
//	// ���� �ڵ�
//	memcpy(&code, ptr_buf, sizeof(int));
//	ptr_buf += sizeof(int);
//	size += sizeof(int);
//	memcpy(ptr_data, &code, sizeof(int));
//	ptr_data += sizeof(int);
//
//	// ���� ��ȣ
//	memcpy(&num, ptr_buf, sizeof(int));
//	ptr_buf += sizeof(int);
//	size += sizeof(int);
//	memcpy(ptr_data, &num, sizeof(int));
//	ptr_data += sizeof(int);
//
//	// ������
//	memcpy(&attacknum, ptr_buf, sizeof(int));
//	ptr_buf += sizeof(int);
//	size += sizeof(int);
//	memcpy(ptr_data, &attacknum, sizeof(int));
//	ptr_data += sizeof(int);
//
//
//	StorageManager::GetInstance()->PushData(PGAMEDATA_MONSTER_OTHERPLAYER_ATTACK_DIE, data, size);
//}

// ��Ƽ �ʴ� ��û
void InGameManager::InGame_Req_Party_Invite(char * _code)
{
	UINT64 protocol = 0;
	char buf[BUFSIZE];
	memset(buf, 0, sizeof(buf));
	int codelen = strlen(_code) + 1;
	int datasize = 0;
	char* ptr = buf;

	memcpy(ptr, &codelen, sizeof(int));
	ptr += sizeof(int);
	datasize += sizeof(int);

	memcpy(ptr, _code, codelen);
	ptr += codelen;
	datasize += codelen;

	protocol = NetworkClient_main::NetworkManager::GetInstance()->GetUser()->BitPackProtocol(protocol, PROTOCOL_INGAME, PROTOCOL_INGAME_PARTY, PROTOCOL_REQ_PARTY_ROOM_INVITE);

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->pack(protocol, buf, datasize);
}

// ��Ƽ �ʴ� ���� [_result : �ʴ����������������] [_code : �ʴ뺸������� �ڵ带 �ֽ��ϴ�] [_partyroomnum : �ʴ뺸������� ��Ƽ���ȣ�� �ֽ��ϴ�]
void InGameManager::InGame_Req_Party_Invite_Result(bool _result, char * _code, int _partyroomnum)
{
	UINT64 protocol = 0;
	char buf[BUFSIZE];
	memset(buf, 0, sizeof(buf));
	char* ptr = buf;
	int datasize = 0;

	int codelen = 0;
	codelen = strlen(_code) + 1;

	// �ʴ� ���
	memcpy(ptr, &_result, sizeof(bool));
	ptr += sizeof(bool);
	datasize += sizeof(bool);
	// �ڵ� ����
	memcpy(ptr, &codelen, sizeof(int));
	ptr += sizeof(int);
	datasize += sizeof(int);
	// �ڵ�
	memcpy(ptr, _code, codelen);
	ptr += codelen;
	datasize += codelen;
	// ��Ƽ ��ȣ
	memcpy(ptr, &_partyroomnum, sizeof(int));
	ptr += sizeof(int);
	datasize += sizeof(int);

	protocol = NetworkClient_main::NetworkManager::GetInstance()->GetUser()->BitPackProtocol(protocol, PROTOCOL_INGAME, PROTOCOL_INGAME_PARTY, PROTOCOL_PARTY_ROOM_ANSWER_INVITE);

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->pack(protocol, buf, datasize);
}

// ���� ���� ��û
void InGameManager::InGame_Req_Dungeon_Enter()
{
	UINT64 protocol = 0;
	char buf[BUFSIZE];
	memset(buf, 0, sizeof(buf));

	protocol = NetworkClient_main::NetworkManager::GetInstance()->GetUser()->BitPackProtocol(protocol, PROTOCOL_INGAME, PROTOCOL_INGAME_DUNGEON, PROTOCOL_REQ_DUNGEON_ENTER);

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->pack(protocol, buf, 0);
}

// ���� ���� ��û
void InGameManager::InGame_Req_Dungeon_Leave()
{
	UINT64 protocol = 0;
	char buf[BUFSIZE];
	memset(buf, 0, sizeof(buf));

	protocol = NetworkClient_main::NetworkManager::GetInstance()->GetUser()->BitPackProtocol(protocol, PROTOCOL_INGAME, PROTOCOL_INGAME_DUNGEON, PROTOCOL_REQ_DUNGEON_LEAVE);

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->pack(protocol, buf, 0);
}

// �������� ����
void InGameManager::InGame_Req_Dungeon_Stage_Enter()
{
	UINT64 protocol = 0;
	char buf[BUFSIZE];
	memset(buf, 0, sizeof(buf));

	protocol = NetworkClient_main::NetworkManager::GetInstance()->GetUser()->BitPackProtocol(protocol, PROTOCOL_INGAME, PROTOCOL_INGAME_DUNGEON, PROTOCOL_DUNGEON_STAGE_IN);

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->pack(protocol, buf, 0);
}

// ���� ���� ��û
void InGameManager::InGame_Req_Monster_Info()
{
	UINT64 protocol = 0;
	char buf[BUFSIZE];
	memset(buf, 0, sizeof(buf));

	protocol = NetworkClient_main::NetworkManager::GetInstance()->GetUser()->BitPackProtocol(protocol, PROTOCOL_INGAME, PROTOCOL_INGMAE_MONSTER, PROTOCOL_REQ_MONSTER_INFO);

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->pack(protocol, buf, 0);
}

// ��Ƽ������ ���� �̵� ���� ����
void InGameManager::InGame_Req_Monster_Move_Info(int _code, int _num, float _px, float _py, float _pz)
{
	UINT64 protocol = 0;
	char buf[BUFSIZE];
	char* ptr = buf;
	int datasize = 0;
	memset(buf, 0, sizeof(buf));

	// ���� �ڵ�
	memcpy(ptr, &_code, sizeof(int));
	datasize += sizeof(int);
	ptr += sizeof(int);

	// ���� ��ȣ
	memcpy(ptr, &_num, sizeof(int));
	datasize += sizeof(int);
	ptr += sizeof(int);

	// ��ġ��
	memcpy(ptr, &_px, sizeof(float));
	datasize += sizeof(float);
	ptr += sizeof(float);

	memcpy(ptr, &_py, sizeof(float));
	datasize += sizeof(float);
	ptr += sizeof(float);

	memcpy(ptr, &_pz, sizeof(float));
	datasize += sizeof(float);
	ptr += sizeof(float);

	protocol = NetworkClient_main::NetworkManager::GetInstance()->GetUser()->BitPackProtocol(protocol, PROTOCOL_INGAME, PROTOCOL_INGMAE_MONSTER, PROTOCOL_MONSTER_MOVE);

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->pack(protocol, buf, datasize);
}

// �ǰݹ��� ������ ���� ���� ���� ����(ĳ�����ڵ�, �����ڵ�, ���͹�ȣ, ���ݹ�ȣ, ���ݻ�Ÿ���ǥ)
void InGameManager::InGame_Req_Monster_Attack(int _monstercode, int _monsternum, int _attacknum, float _x, float _y, float _z)
{
	UINT64 protocol = 0;
	char buf[BUFSIZE];
	memset(buf, 0, sizeof(buf));
	char* ptr = buf;
	int datasize = 0;

	// ���� �ڵ�
	memcpy(ptr, &_monstercode, sizeof(int));
	datasize += sizeof(int);
	ptr += sizeof(int);
	// ���� ��ȣ
	memcpy(ptr, &_monsternum, sizeof(int));
	datasize += sizeof(int);
	ptr += sizeof(int);
	// ���� ��ȣ
	memcpy(ptr, &_attacknum, sizeof(int));
	datasize += sizeof(int);
	ptr += sizeof(int);
	// x
	memcpy(ptr, &_x, sizeof(float));
	datasize += sizeof(float);
	ptr += sizeof(float);
	// y
	memcpy(ptr, &_y, sizeof(float));
	datasize += sizeof(float);
	ptr += sizeof(float);
	// z
	memcpy(ptr, &_z, sizeof(float));
	datasize += sizeof(float);
	ptr += sizeof(float);

	protocol = NetworkClient_main::NetworkManager::GetInstance()->GetUser()->BitPackProtocol(protocol, PROTOCOL_INGAME, PROTOCOL_INGMAE_MONSTER, PROTOCOL_REQ_MONSTER_ATTACK);

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->pack(protocol, buf, datasize);
}

//// ��Ƽ������ ���� ���� ���� ����(ĳ�����ڵ�, �����ڵ�, ���͹�ȣ, ���ݹ�ȣ)
//void InGameManager::InGame_Req_Monster_Attack(int _monstercode, int _monsternum, int _attacknum)
//{
//	UINT64 protocol = 0;
//	char buf[BUFSIZE];
//	memset(buf, 0, sizeof(buf));
//	char* ptr = buf;
//	int datasize = 0;
//
//	// ���� �ڵ�
//	memcpy(ptr, &_monstercode, sizeof(int));
//	ptr += sizeof(int);
//	datasize += sizeof(int);
//
//	// ���� ��ȣ
//	memcpy(ptr, &_monsternum, sizeof(int));
//	ptr += sizeof(int);
//	datasize += sizeof(int);
//
//	// ���� ��ȣ
//	memcpy(ptr, &_attacknum, sizeof(int));
//	ptr += sizeof(int);
//	datasize += sizeof(int);
//
//	protocol = NetworkClient_main::NetworkManager::GetInstance()->GetUser()->BitPackProtocol(protocol, PROTOCOL_INGAME, PROTOCOL_INGMAE_MONSTER, PROTOCOL_REQ_MONSTER_ATTACK);
//
//	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->pack(protocol, buf, datasize);
//}

RESULT InGameManager::InGameInitRecvResult(User * _user)
{
	UINT64 protocol = 0;
	UINT64 compartrprotocol = 0;
	UINT64 tempprotocol = 0;

	char buf[BUFSIZE];

	RESULT result;
	bool check;

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->BitunPack(protocol, buf);

	compartrprotocol = PROTOCOL_INGAME_CHARACER;

	while (1)
	{
		tempprotocol = 0;

		tempprotocol = protocol & compartrprotocol;
		switch (tempprotocol)
		{
		case PROTOCOL_INGAME_CHARACER:	// �������� �߰�Ʋ ĳ���� ���� �̸�
			tempprotocol = protocol & PROTOCOL_SERVER_INGAME_CHARACTER_COMPART;
			switch (tempprotocol)
			{
			case PROTOCOL_INGAME_OTHERPLAYERLIST_INFO: // ������ ����
				check = InGame_Recv_UserList(buf);
				if (check)
				{
					result = RT_INGAME_OTHERPLAYER_LIST;
				}
				break;
			case PROTOCOL_INGAME_MOVE_RESULT: // ���� �̵� ���
				check = InGame_Recv_MoveResult(buf);
				if (check)	// �̵� ����
				{
					result = RT_INGAME_MOVE;
				}
				else		// �̵� ����
				{
					result = RT_INGAME_MOVE;
				}
				break;
			case PROTOCOL_INGAME_MOVE_OTHERPLAYERINFO: // �ٸ� ���� �̵� ����
				InGame_Recv_OtherUserMoveInfo(buf, PGAMEDATA_PLAYER_OTHERMOVEINFO);
				result = RT_INGAME_OTHERPLAYER_INFO;
				break;
			case PROTOCOL_INGAME_MOVE_ROTATION: // �ٸ� ���� ȸ�� ����
				InGame_Recv_OtherUserRotation(buf);
				result = RT_INGAME_MOVE;
				break;
			case PROTOCOL_INGAME_OTHERPLAYER_CONNECT: // �ٸ� ���� ��������
				InGame_Recv_ConnectUserInfo(buf);
				result = RT_INGAME_OTHERPLAYER_INFO;
				break;
			case PROTOCOL_INGAME_OTHERPLAYER_LEAVE: // �ٸ� ���� ��������
				InGame_Recv_OtherUserLeave(buf);
				result = RT_INGAME_OTHERPLAYER_LEAVE;
				break;
			case PROTOCOL_INGAME_MOVE_OTHERPLAYER_START_JUMP: // �ٸ� ���� ����
				InGame_Recv_OtherUser_Start_Jump(buf);
				result = RT_INGAME_OTHERPLAYER_INFO;
				break;
			case PROTOCOL_INGAME_MOVE_OTHERPLAYER_END_JUMP: // �ٸ� ���� ����
				InGame_Recv_OtherUser_End_Jump(buf);
				result = RT_INGAME_OTHERPLAYER_INFO;
				break;
			case PROTOCOL_INGAME_OTHERPLAYER_ATTACK: // �ٸ� ���� �����ߴ�
				InGame_Recv_OtherUser_Attack(buf);
				result = RT_INGAME_OTHERPLAYER_INFO;
				break;
			case PROTOCOL_INGAME_ATTACK_RESULT: //���� ���� ���(���Ͱ������������� or ���ݾȹ���)
				InGame_Recv_Monster_has_been_Attacked(buf);
				result = RT_INGAME_OTHERPLAYER_INFO;
				break;
			case PROTOCOL_INGAME_OTHERPLAYER_ATTACK_SUCCESS: // �ٸ� ���� ���ݼ����ߴ�(���Ͱ�������������)
				InGame_Recv_OtherMonster_has_been_Attack(buf);
				result = RT_INGAME_OTHERPLAYER_INFO;
				break;
			default:
				break;
			}
			break;
		case PROTOCOL_INGMAE_MONSTER: 	// �������� �߰�Ʋ ���� ���� �̸�
			tempprotocol = protocol & PROTOCOL_SERVER_INGAME_MONSTER_COMPART;
			switch (tempprotocol)
			{
			case PROTOCOL_MONSTER_MOVE_RESULT: // ���� �̵� ����
			{
				// ���� �̵����� ��
				InGame_Recv_Monster_MoveInfo(buf);
				result = RT_INGAME_MONSTER_MOVE_INFO_RESULT;
				break;
			}
			case PROTOCOL_MONSTER_INFO: // ���� ����
			{
				// ���� ���� ��
				InGame_Recv_Stage_MonsterInfo(buf);
				result = RT_INGAME_MONSTER_INFO_RESULT;
				break;
			}
			case PROTOCOL_INGAME_MONSTER_ATTACK_RESULT: // ���Ͱ��� ���(������ ����)
			{
				// ���,������,��������
				InGame_Recv_UnderAttack(buf);
				result = RT_INGAME_USER_UNDERATTACK_RESULT;
				break;
			}
			case PROTOCOL_INGAME_MONSTER_OTHER_ATTACK_RESULT: // ���Ͱ��� ���(�ٸ�����������)
			{
				// �����,������,��������
				InGame_Recv_Other_UnderAttack(buf);
				result = RT_INGAME_OTHERUSER_UNDERATTACK_RESULT;
				break;
			}
			default:
				break;
			}
			break;
		case PROTOCOL_INGAME_CHANNEL:	// �������� �߰�Ʋ ä�� ���� �̸�
			tempprotocol = protocol & PROTOCOL_SERVER_INGAME_CHANNEL_COMPART;
			switch (tempprotocol)
			{
			case PROTOCOL_CHANNLE_INFO: // ä�� ����
				InGame_Recv_ChannelInfo(buf);
				result = RT_INGAME_CHANNEL_INFO;
				break;
			case PROTOCOL_CHANNLE_CHANGE_RESULT: // ä�� ���� ���
				InGame_Recv_ChannelChange(buf);
				result = RT_INGAME_CHANNEL_CHANGE;
				break;
			case PROTOCOL_CHANNLE_USER_CHANGE: // ä�� �̵��� ���� ����
				InGame_Recv_OtherUserLeave(buf);
				result = RT_INGAME_OTHERPLAYER_LEAVE;
				break;
			default:
				break;
			}
			break;
		case PROTOCOL_INGAME_PARTY:		// �������� �߰�Ʋ ��Ƽ ���� �̸�
			tempprotocol = protocol & PROTOCOL_SERVER_INGAME_PARTY_COMPART;
			switch (tempprotocol)
			{
			case PROTOCOL_PARTY_ROOM_INVITE: // ��Ƽ �ʴ�(Ư����������)
			{
				InGame_Recv_Invite(buf);
				result = RT_INGAME_PARTY_INVITE;
				break;
			}
			case PROTOCOL_PARTY_ROOM_ANSWER_INVITE: // ��Ƽ �ʴ� ���
			{
				InGame_Recv_Invite_Result(buf);
				result = RT_INGAME_PARTY_INVITE_RESULT;
				break;
			}
			case PROTOCOL_PARTY_ROOM_JOIN_RESULT: // ���� ���
			{
				InGame_Recv_Join_Result(buf);
				result = RT_INGAME_PARTY_JOIN_RESULT;
				break;
			}
			case PROTOCOL_PARTY_ROOM_ADD_USER: // ���ο� ��Ƽ���� ����
			{
				InGame_Recv_Party_User_Info(buf);
				result = RT_INGAME_PARTY_ADD_USER;
				break;
			}
			case PROTOCOL_REQ_LEADER_DELEGATE: // ������ѻ������ ������ ��������
			{
				// �������ݸ� �´�
				InGame_Recv_Kick();
				result = RT_INGAME_PARTY_KICK;
				break;
			}
			case PROTOCOL_PARTY_USER_KICK_INFO: // ������� ���� ����
			{
				// �����ڵ� �´�
				InGame_Recv_Kick_User_Info(buf);
				result = RT_INGAME_PARTY_KICK_USER_INFO;
				break;
			}
			case PROTOCOL_PARTY_USER_KICK_RESULT: // ������
			{
				// ��� �´�. �����̸� �ڿ� �ڵ嵵 �´�
				InGame_Recv_Kick_Result(buf);
				result = RT_INGAME_PARTY_KICK_RESULT;
				break;
			}
			case PROTOCOL_PARTY_USER_LEAVE_INFO: // Ż���ϴ� ���� ����
			{
				// ĳ���� �ڵ� �´�
				InGame_Recv_Leave_User_Info(buf);
				result = RT_INGAME_PARTY_LEAVE_INFO;
				break;
			}
			case PROTOCOL_PARTY_USER_LEAVE_RESULT: // Ż����
			{
				// ���� ���� ���θ� �´�
				InGame_Recv_Leave_Result(buf);
				result = RT_INGAME_PARTY_LEAVE_RESULT;
				break;
			}
			case PROTOCOL_PARTY_ROOM_REMOVE_RESULT: // ��Ƽ�� ��������� ������ ��������
			{
				// ��Ƽ�� �����ٴ� �������ݸ� �´�
				InGame_Recv_PartyRoom_Remove(buf);
				result = RT_INGAME_PARTY_ROOM_REMOVE;
				break;
			}
			case PROTOCOL_PARTY_LEADER_DELEGATE: // ���� ���� ���� ���� ����
			{
				// ��Ƽ�� �� ����, ���ο� ���� �ڵ尡 �´�
				InGame_Recv_PartyRoom_Leader_Info(buf);
				result = RT_INGAME_PARTY_LEADER_DELEGATE;
				break;
			}
			case PROTOCOL_PARTY_LEADER_DELEGATE_RESULT: // ������ѻ������ ������ ��������
			{
				// ���� ���� ����� ���� �����̸� �ڿ� �ڵ嵵 �´�.
				InGame_Recv_PartyRoom_Leader_Delegate_Result(buf);
				result = RT_INGAME_PARTY_LEADER_DELEGATE_RESULT;
				break;
			}
			case PROTOCOL_PARTY_USER_INFO: // ��Ƽ������
			{
				break;
			}

			default:
				break;
			}
			break;
		case PROTOCOL_INGAME_DUNGEON:	// �������� �߰�Ʋ ���� ���� �̸�
			tempprotocol = protocol & PROTOCOL_SERVER_INGAME_DUNGEON_COMPART;
			switch (tempprotocol)
			{
			case PROTOCOL_DUNGEON_ENTER_RESULT: // ���� ���� ���
			{
				// ���� ���� ��ġ ��(Vector3)
				InGame_Recv_Leave_Dungeon_Enter_Result(buf);
				result = RT_INGAME_DUNGEON_ENTER_RESULT;
				break;
			}
			case PROTOCOL_DUNGEON_LEAVE_RESULT: // ���� ���� ���
			{
				// ä�ι�ȣ��
				InGame_Recv_Leave_Dungeon_Leave_Result(buf);
				result = RT_INGAME_DUNGEON_LEAVE_RESULT;
				break;
			}
			case PROTOCOL_DUNGEON_STAGE_IN_RESULT: // �������� ���� ���
			{
				// �������� ���� �����(Vector3)
				InGame_Recv_Stage_Enter_Result(buf);
				result = RT_INGAME_DUNGEON_STAGE_ENTER_RESULT;
				break;
			}
			default:
				break;
			}
			break;
		case PROTOCOL_INGMAE_MENU:		// �������� �߰�Ʋ �Ŵ� ���� �̸�
			tempprotocol = protocol & PROTOCOL_SERVER_INGAME_MENU_COMPART;
			switch (tempprotocol)
			{
			case PROTOCOL_MENU_RESULT_CHARACTER: // ĳ���� ����ȭ������ ���
			{	InGame_Recv_CharacterSelect();
			result = RT_INGAME_MENU_CHARACTER;
				break;
			}
			case PROTOCOL_MENU_RESULT_LOGOUT: // �α׾ƿ� ���
			{
				InGame_Recv_Logout();
				result = RT_INGAME_MENU_LOGOUT;
				break;
			}
			//case PROTOCOL_MENU_RESULT_EXIT:  // ����������
			//{
			//	// ���� �ȸ���
			//	break;
			//}
			default:
				break;
			}
			break;
		case PROTOCOL_INGAME_ANIMATION: // �������� �߰�Ʋ �ִϸ��̼� ���� �̸�
			tempprotocol = protocol & PROTOCOL_SERVER_INGAME_ANIMATION_COMPART;
			switch (tempprotocol)
			{
			case PROTOCOL_CHARACER_ANIMATION: // ĳ���� �ִϸ��̼�
				break;
			case PROTOCOL_MONSTER_ANIMATION: // ���� �ִϸ��̼�
				break;
			//case PROTOCOL_MONSTER_ANIMATION_ATTACK: // ���� ���� �ִϸ��̼�
			//	break;
			default:
				break;
			}
			break;
		default:
			break;
		}

		// ������ ���������̸� Ż��
		if (compartrprotocol == PROTOCOL_INGMAE_MENU)
		{
			break;
		}

		// protocol�̶� ���� ��� ����Ʈ ����
		compartrprotocol = compartrprotocol << 1;
	}

	return result;
}
