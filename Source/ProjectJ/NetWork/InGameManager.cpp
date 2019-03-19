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
	char buf[BUFSIZE];
	memset(buf, 0, sizeof(buf));

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->pack(CLIENT_INGAME_OTHERPLAYERLIST, buf, 0);
}

// �̵� ��û
void InGameManager::InGame_Req_Move(float _px, float _py, float _pz)
{
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

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->pack(CLIENT_INGAME_MOVE_REPORT, buf, datasize);
}

// ȸ�� ��û
void InGameManager::InGame_Req_Rotation(float _rx, float _ry, float _rz)
{
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

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->pack(CLIENT_INGAME_MOVE_ROTATION, buf, datasize);
}

// ä�� ���� ��û
void InGameManager::InGame_Req_ChannelInfo()
{
	char buf[BUFSIZE];
	memset(buf, 0, sizeof(buf));

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->pack(CLIENT_INGAME_CHANNEL_INFO, buf, 0);
}

// ä�� �̵� ��û
void InGameManager::InGame_Req_ChannelChange(int _channelnum)
{
	char buf[BUFSIZE];
	char* ptr = buf;
	int datasize = 0;
	memset(buf, 0, sizeof(buf));

	// ä�� ��ȣ
	memcpy(ptr, &_channelnum, sizeof(int));
	datasize += sizeof(int);
	ptr += sizeof(int);

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->pack(CLIENT_INGAME_CHANNEL_CHANGE, buf, datasize);
}

// ĳ���� ����ȭ������ ��û
void InGameManager::InGame_Req_Menu_Character()
{
	char buf[BUFSIZE];
	memset(buf, 0, sizeof(buf));

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->pack(CLIENT_INGAME_MENU_REQ_CHARACTER, buf, 0);
	char msg[BUFSIZE];
	memset(msg, 0, sizeof(msg));
	//sprintf(msg,"InGame_Req_Menu_Character :: ĳ���ͼ���ȭ��");
	LogManager::GetInstance()->LogWrite(msg);
}

// �α׾ƿ� ��û
void InGameManager::InGame_Req_Menu_Title()
{
	char buf[BUFSIZE];
	memset(buf, 0, sizeof(buf));

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->pack(CLIENT_INGAME_MENU_REQ_LOGOUT, buf, 0);

	char msg[BUFSIZE];
	memset(msg, 0, sizeof(msg));
	//sprintf(msg, "InGame_Req_Menu_Title :: �α׾ƿ�");
	LogManager::GetInstance()->LogWrite(msg);
}

// �̵� ���� ��û
//void InGameManager::InGame_Req_MoveStart(float _px, float _py, float _pz, float _rx, float _ry, float _rz, float _dirx, float _diry)
//{
//	char buf[BUFSIZE];
//	char* ptr = buf;
//	int datasize = 0;
//	memset(buf, 0, sizeof(buf));
//
//	// ��ġ��
//	memcpy(ptr, &_px, sizeof(float));
//	datasize += sizeof(float);
//	ptr += sizeof(float);
//
//	memcpy(ptr, &_py, sizeof(float));
//	datasize += sizeof(float);
//	ptr += sizeof(float);
//
//	memcpy(ptr, &_pz, sizeof(float));
//	datasize += sizeof(float);
//	ptr += sizeof(float);
//
//	// ȸ����
//	memcpy(ptr, &_rx, sizeof(float));
//	datasize += sizeof(float);
//	ptr += sizeof(float);
//
//	memcpy(ptr, &_ry, sizeof(float));
//	datasize += sizeof(float);
//	ptr += sizeof(float);
//
//	memcpy(ptr, &_rz, sizeof(float));
//	datasize += sizeof(float);
//	ptr += sizeof(float);
//
//	// ���Ⱚ
//	memcpy(ptr, &_dirx, sizeof(float));
//	datasize += sizeof(float);
//	ptr += sizeof(float);
//
//	memcpy(ptr, &_diry, sizeof(float));
//	datasize += sizeof(float);
//	ptr += sizeof(float);
//
//	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->pack(CLIENT_INGAME_MOVE_START, buf, datasize);
//}

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

RESULT InGameManager::InGameInitRecvResult(User * _user)
{
	PROTOCOL protocol;
	char buf[BUFSIZE];

	RESULT result;
	bool check;

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->unPack(&protocol, buf);

	switch (protocol)
	{
	case SERVER_INGAME_OTHERPLAYER_CONNECT:
		InGame_Recv_ConnectUserInfo(buf);
		result = RT_INGAME_OTHERPLAYER_INFO;
		break;
	case SERVER_INGAME_MOVE_RESULT:
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
	case SERVER_INGAME_MOVE_ORDER:
		InGame_Recv_OtherUserMoveInfo(buf, PGAMEDATA_PLAYER_OTHERMOVEORDER);
		result = RT_INGAME_OTHERPLAYER_INFO;
		break;
	case SERVER_INGAME_MOVE_OTHERPLAYERINFO:
		InGame_Recv_OtherUserMoveInfo(buf, PGAMEDATA_PLAYER_OTHERMOVEINFO);
		result = RT_INGAME_OTHERPLAYER_INFO;
		break;
	case SERVER_INGAME_OTHERPLAYERLIST_RESULT:
		check = InGame_Recv_UserList(buf);
		if (check)
		{
			result = RT_INGAME_OTHERPLAYER_LIST;
		}
		break;
	case SERVER_INGAME_MOVE_ROTATION:
		InGame_Recv_OtherUserRotation(buf);
		result = RT_INGAME_MOVE;
		break;
	case SERVER_INGAME_OTHERPLAYER_LEAVE:
		InGame_Recv_OtherUserLeave(buf);
		result = RT_INGAME_OTHERPLAYER_LEAVE;
		break;
	case SERVER_INGAME_CHANNLE_INFO_RESULT:
		InGame_Recv_ChannelInfo(buf);
		result = RT_INGAME_CHANNEL_INFO;
		break;
	case SERVER_INGAME_CHANNLE_CHANGE_RESULT:
		InGame_Recv_ChannelChange(buf);
		result = RT_INGAME_CHANNEL_CHANGE;
		break;
	case SERVER_INGAME_MENU_RESULT_CHARACTER:
		InGame_Recv_CharacterSelect();
		result = RT_INGAME_MENU_CHARACTER;
		break;
	case SERVER_INGAME_MENU_RESULT_LOGOUT:
		InGame_Recv_Logout();
		result = RT_INGAME_MENU_LOGOUT;
		break;
	default:
		break;
	}

	return result;
}
