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

// 현재 접속중인 유저리스트 요청
void InGameManager::InGame_Req_UserList()
{
	UINT64 protocol = 0;
	char buf[BUFSIZE];
	memset(buf, 0, sizeof(buf));

	protocol = NetworkClient_main::NetworkManager::GetInstance()->GetUser()->BitPackProtocol(protocol, PROTOCOL_INGAME, PROTOCOL_INGAME_CHARACER, PROTOCOL_REQ_OTHERPLAYERLIST);

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->pack(protocol, buf, 0);
}

// 이동 요청
void InGameManager::InGame_Req_Move(float _px, float _py, float _pz)
{
	UINT64 protocol = 0;
	char buf[BUFSIZE];
	char* ptr = buf;
	int datasize = 0;
	memset(buf, 0, sizeof(buf));

	// 위치값
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

// 회전 요청
void InGameManager::InGame_Req_Rotation(float _rx, float _ry, float _rz)
{
	UINT64 protocol = 0;
	char buf[BUFSIZE];
	char* ptr = buf;
	int datasize = 0;
	memset(buf, 0, sizeof(buf));

	// 회전값
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

// 채널 정보 요청
void InGameManager::InGame_Req_ChannelInfo()
{
	UINT64 protocol = 0;
	char buf[BUFSIZE];
	memset(buf, 0, sizeof(buf));

	protocol = NetworkClient_main::NetworkManager::GetInstance()->GetUser()->BitPackProtocol(protocol, PROTOCOL_INGAME, PROTOCOL_INGAME_CHANNEL, PROTOCOL_REQ_CHANNEL_INFO);

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->pack(protocol, buf, 0);
}

// 채널 이동 요청
void InGameManager::InGame_Req_ChannelChange(int _channelnum)
{
	UINT64 protocol = 0;
	char buf[BUFSIZE];
	char* ptr = buf;
	int datasize = 0;
	memset(buf, 0, sizeof(buf));

	// 채널 번호
	memcpy(ptr, &_channelnum, sizeof(int));
	datasize += sizeof(int);
	ptr += sizeof(int);
	
	protocol = NetworkClient_main::NetworkManager::GetInstance()->GetUser()->BitPackProtocol(protocol, PROTOCOL_INGAME, PROTOCOL_INGAME_CHANNEL, PROTOCOL_REQ_CHANNEL_CHANGE);

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->pack(protocol, buf, datasize);
}

// 캐릭터 선택화면으로 요청
void InGameManager::InGame_Req_Menu_Character()
{
	UINT64 protocol = 0;
	char buf[BUFSIZE];
	memset(buf, 0, sizeof(buf));

	protocol = NetworkClient_main::NetworkManager::GetInstance()->GetUser()->BitPackProtocol(protocol, PROTOCOL_INGAME, PROTOCOL_INGMAE_MENU, PROTOCOL_MENU_REQ_CHARACTER);

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->pack(protocol, buf, 0);
}

// 로그아웃 요청
void InGameManager::InGame_Req_Menu_Title()
{
	UINT64 protocol = 0;
	char buf[BUFSIZE];
	memset(buf, 0, sizeof(buf));

	protocol = NetworkClient_main::NetworkManager::GetInstance()->GetUser()->BitPackProtocol(protocol, PROTOCOL_INGAME, PROTOCOL_INGMAE_MENU, PROTOCOL_MENU_REQ_LOGOUT);

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->pack(protocol, buf, 0);
}

// 강퇴요청
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

// 탈퇴요청
void InGameManager::InGame_Req_LeaveParty()
{
	UINT64 protocol = 0;
	char buf[BUFSIZE];
	memset(buf, 0, sizeof(buf));

	protocol = NetworkClient_main::NetworkManager::GetInstance()->GetUser()->BitPackProtocol(protocol, PROTOCOL_INGAME, PROTOCOL_INGAME_PARTY, PROTOCOL_REQ_USER_LEAVE);

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->pack(protocol, buf, 0);
}

// 파티 리더 위임하기
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

// 현재 접속중인 유저리스트 받음
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

		// 코드 사이즈
		memcpy(&len, ptr_buf, sizeof(int));
		ptr_buf += sizeof(int);
		size += sizeof(int);
		memcpy(ptr_data, &len, sizeof(int));
		ptr_data += sizeof(int);

		// 코드
		memcpy(code, ptr_buf, len);
		ptr_buf += len;
		size += len;
		memcpy(ptr_data, code, len);
		ptr_data += len;

		// 캐릭터 직업코드
		memcpy(&jobcode, ptr_buf, sizeof(int));
		ptr_buf += sizeof(int);
		size += sizeof(int);
		memcpy(ptr_data, &jobcode, sizeof(int));
		ptr_data += sizeof(int);

		// 닉네임 사이즈
		memcpy(&len, ptr_buf, sizeof(int));
		ptr_buf += sizeof(int);
		size += sizeof(int);
		memcpy(ptr_data, &len, sizeof(int));
		ptr_data += sizeof(int);

		// 닉네임
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

// 접속한 다른유저 정보
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

	// 코드 사이즈
	memcpy(&len, ptr_buf, sizeof(int));
	ptr_buf += sizeof(int);
	size += sizeof(int);
	memcpy(ptr_data, &len, sizeof(int));
	ptr_data += sizeof(int);

	// 코드
	memcpy(code, ptr_buf, len);
	ptr_buf += len;
	size += len;
	memcpy(ptr_data, code, len);
	ptr_data += len;

	// 직업코드
	memcpy(&jobcode, ptr_buf, sizeof(int));
	ptr_buf += sizeof(int);
	size += sizeof(int);
	memcpy(ptr_data, &jobcode, sizeof(int));
	ptr_data += sizeof(int);

	// 닉네임 사이즈
	memcpy(&len, ptr_buf, sizeof(int));
	ptr_buf += sizeof(int);
	size += sizeof(int);
	memcpy(ptr_data, &len, sizeof(int));
	ptr_data += sizeof(int);

	// 닉네임
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

// 플레이어 이동 결과 
bool InGameManager::InGame_Recv_MoveResult(char * _buf)
{
	bool result;
	char* ptr_buf = _buf;

	char data[BUFSIZE];
	char* ptr_data = data;
	int size = 0;
	float xyz[3];

	// 이동결과
	memcpy(&result, ptr_buf, sizeof(bool));
	ptr_buf += sizeof(bool);

	// 이동결과 스토리지에 넣음
	//StorageManager::GetInstance()->PushData(PGAMEDATA_PLAYER_MOVE_RESULT, data, size);

	memset(data, 0, sizeof(data));
	ptr_data = data;

	// 실패 시 
	if (result == false)
	{
		// position x, y, z
		memcpy(xyz, ptr_buf, sizeof(float) * 3);
		ptr_buf += sizeof(float) * 3;
		size += sizeof(float) * 3;
		memcpy(ptr_data, xyz, sizeof(float) * 3);
		ptr_data += sizeof(float) * 3;

		// 실패 시 예전 이동결과
		StorageManager::GetInstance()->PushData(PGAMEDATA_PLAYER_MOVE_INFO, data, size);
	}

	return result;
}

// 다른 유저 이동 정보
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

	// 코드 사이즈
	memcpy(&len, ptr_buf, sizeof(int));
	ptr_buf += sizeof(int);
	size += sizeof(int);
	memcpy(ptr_data, &len, sizeof(int));
	ptr_data += sizeof(int);

	// 코드
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

// 다른 유저 회전
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

	// 코드 사이즈
	memcpy(&len, ptr_buf, sizeof(int));
	ptr_buf += sizeof(int);
	size += sizeof(int);
	memcpy(ptr_data, &len, sizeof(int));
	ptr_data += sizeof(int);

	// 코드
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

// 다른 유저 나간정보
void InGameManager::InGame_Recv_OtherUserLeave(char * _buf)
{
	char* ptr_buf = _buf;

	char data[BUFSIZE];
	char code[CHARACTERCODESIZE];
	char* ptr_data = data;
	int size = 0;
	int len = 0;

	memset(code, 0, CHARACTERCODESIZE);

	// 코드 사이즈
	memcpy(&len, ptr_buf, sizeof(int));
	ptr_buf += sizeof(int);
	size += sizeof(int);
	memcpy(ptr_data, &len, sizeof(int));
	ptr_data += sizeof(int);

	// 코드
	memcpy(code, ptr_buf, len);
	ptr_buf += len;
	size += len;
	memcpy(ptr_data, code, len);
	ptr_data += len;

	StorageManager::GetInstance()->PushData(PGAMEDATA_LEAVE_PLAYER, data, size);
}

// 채널 정보
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
		// 채널번호
		memcpy(&channelnum, ptr, sizeof(int));
		ptr += sizeof(int);
		// 해당 채널 유저수
		memcpy(&channelusercount, ptr, sizeof(int));
		ptr += sizeof(int);

		// 형변환
		f_channelnum = (float)channelnum;
		f_channelusercount = (float)channelusercount;

		// data에 채널번호 패킹
		memcpy(ptr_data, &f_channelnum, sizeof(float));
		ptr_data += sizeof(float);
		size += sizeof(float);
		// data에 채널 유저수 패킹
		memcpy(ptr_data, &f_channelusercount, sizeof(float));
		ptr_data += sizeof(float);
		size += sizeof(float);
	}

	StorageManager::GetInstance()->PushData(PGAMEDATA_CHANNEL_INFO, data, size);
}

// 캐릭터 선택화면으로 받았을때
void InGameManager::InGame_Recv_CharacterSelect()
{
	StorageManager::GetInstance()->PushData(PGAMEDATA_MENU_CHARACTER_SELECT, 0, 0);
}

// 로그아웃 받았을때
void InGameManager::InGame_Recv_Logout()
{
	StorageManager::GetInstance()->PushData(PGAMEDATA_MENU_LOGOUT, 0, 0);
}

// 채널이동 결과
void InGameManager::InGame_Recv_ChannelChange(char * _buf)
{
	char* ptr = _buf;

	char data[BUFSIZE];
	char* ptr_data = data;
	int size = 0;

	bool result = false;
	int channelnum = 0;

	// 결과 언팩
	memcpy(&result, ptr, sizeof(bool));
	ptr += sizeof(bool);

	if (result)
	{
		// 바뀐 채널 언팩
		memcpy(&channelnum, ptr, sizeof(int));
		ptr += sizeof(int);

		// 결과 패킹
		memcpy(ptr_data, &result, sizeof(bool));
		ptr_data += sizeof(bool);
		size += sizeof(bool);

		// 바뀐 채널 패킹
		memcpy(ptr_data, &channelnum, sizeof(int));
		ptr_data += sizeof(int);
		size += sizeof(int);
	}
	else
	{
		// 결과 패킹
		memcpy(ptr_data, &result, sizeof(bool));
		ptr_data += sizeof(bool);
		size += sizeof(bool);
	}

	StorageManager::GetInstance()->PushData(PGAMEDATA_CHANNEL_REQ_CHANGE, data, size);
}

// 파티 초대 받음
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

	// 코드길이
	memcpy(&codelen, ptr, sizeof(int));
	ptr += sizeof(int);
	// 코드
	memcpy(code, ptr, codelen);
	ptr += codelen;
	// 닉네임길이
	memcpy(&nicklen, ptr, sizeof(int));
	ptr += sizeof(int);
	//닉네임
	memcpy(nick, ptr, nicklen);
	ptr += nicklen;
	// 파티번호
	memcpy(&partyroom, ptr, sizeof(int));
	ptr += sizeof(int);

	// data에 코드길이 패킹
	memcpy(ptr_data, &codelen, sizeof(int));
	ptr_data += sizeof(int);
	size += sizeof(int);
	// data에 코드 패킹
	memcpy(ptr_data, code, codelen);
	ptr_data += codelen;
	size += codelen;
	// data에 닉네임길이 패킹
	memcpy(ptr_data, &nicklen, sizeof(int));
	ptr_data += sizeof(int);
	size += sizeof(int);
	// data에 닉네임 패킹
	memcpy(ptr_data, nick, nicklen);
	ptr_data += nicklen;
	size += nicklen;
	// data에 파티번호 패킹
	memcpy(ptr_data, &partyroom, sizeof(int));
	ptr_data += sizeof(int);
	size += sizeof(int);

	StorageManager::GetInstance()->PushData(PGAMEDATA_PARTY_INVITE, data, size);
}

// 파티 초대 결과받음
void InGameManager::InGame_Recv_Invite_Result(char * _buf)
{
	char* ptr = _buf;

	char data[BUFSIZE];
	memset(data, 0, sizeof(BUFSIZE));
	char* ptr_data = data;
	int size = 0;

	bool result = false;

	// 결과
	memcpy(&result, ptr, sizeof(bool));
	ptr += sizeof(bool);

	// data에 결과
	memcpy(ptr_data, &result, sizeof(bool));
	ptr_data += sizeof(bool);
	size += sizeof(bool);

	StorageManager::GetInstance()->PushData(PGAMEDATA_PARTY_INVITE_RESULT, data, size);
}

// 파티 참여 결과
void InGameManager::InGame_Recv_Join_Result(char * _buf)
{
	char* ptr = _buf;

	char data[BUFSIZE];
	memset(data, 0, sizeof(BUFSIZE));
	char* ptr_data = data;
	int size = 0;

	bool result = false;

	// 결과
	memcpy(&result, ptr, sizeof(bool));
	ptr += sizeof(bool);

	// data에 결과
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

		// 코드 사이즈
		memcpy(&codelen, ptr_buf, sizeof(int));
		ptr_buf += sizeof(int);
		size += sizeof(int);
		memcpy(ptr_data, &codelen, sizeof(int));
		ptr_data += sizeof(int);

		// 코드
		memcpy(code, ptr_buf, codelen);
		ptr_buf += codelen;
		size += codelen;
		memcpy(ptr_data, code, codelen);
		ptr_data += codelen;

		// 캐릭터 직업코드
		memcpy(&jobcode, ptr_buf, sizeof(int));
		ptr_buf += sizeof(int);
		size += sizeof(int);
		memcpy(ptr_data, &jobcode, sizeof(int));
		ptr_data += sizeof(int);

		// 닉네임 사이즈
		memcpy(&nicklen, ptr_buf, sizeof(int));
		ptr_buf += sizeof(int);
		size += sizeof(int);
		memcpy(ptr_data, &nicklen, sizeof(int));
		ptr_data += sizeof(int);

		// 닉네임
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

		// 방장인지 아닌지
		memcpy(&leader, ptr_buf, sizeof(bool));
		ptr_buf += sizeof(bool);
		size += sizeof(bool);
		memcpy(ptr_data, &leader, sizeof(bool));
		ptr_data += sizeof(bool);

		StorageManager::GetInstance()->PushData(PGAMEDATA_PARTY_USER_INFO, data, size);
	}

}

// 파티 강퇴 받은
void InGameManager::InGame_Recv_Kick()
{
	StorageManager::GetInstance()->PushData(PGAMEDATA_PARTY_KICK, 0, 0);
}

// 파티 강퇴받은 유저 정보 받은
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

	// 코드길이
	memcpy(&codelen, ptr, sizeof(int));
	ptr += sizeof(int);
	// 코드
	memcpy(code, ptr, codelen);
	ptr += codelen;

	// data에 코드길이 패킹
	memcpy(ptr_data, &codelen, sizeof(int));
	ptr_data += sizeof(int);
	size += sizeof(int);
	// data에 코드 패킹
	memcpy(ptr_data, code, codelen);
	ptr_data += codelen;
	size += codelen;

	StorageManager::GetInstance()->PushData(PGAMEDATA_PARTY_USER_KICK_INFO, data, size);
}

// 파티 강퇴결과
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

	// 결과
	memcpy(&result, ptr, sizeof(bool));
	ptr += sizeof(bool);

	if (result == false)
	{
		// data에 결과 패킹
		memcpy(ptr_data, &result, sizeof(bool));
		ptr_data += sizeof(bool);
		size += sizeof(bool);

		StorageManager::GetInstance()->PushData(PGAMEDATA_PARTY_USER_KICK_RESULT, data, size);
	}
	else
	{
		// 코드길이
		memcpy(&codelen, ptr, sizeof(int));
		ptr += sizeof(int);
		// 코드
		memcpy(code, ptr, codelen);
		ptr += codelen;

		// data에 결과 패킹
		memcpy(ptr_data, &result, sizeof(bool));
		ptr_data += sizeof(bool);
		size += sizeof(bool);
		// data에 코드길이 패킹
		memcpy(ptr_data, &codelen, sizeof(int));
		ptr_data += sizeof(int);
		size += sizeof(int);
		// data에 코드 패킹
		memcpy(ptr_data, code, codelen);
		ptr_data += codelen;
		size += codelen;

		StorageManager::GetInstance()->PushData(PGAMEDATA_PARTY_USER_KICK_RESULT, data, size);
	}
}

// 파티 탈퇴받은 유저 정보받음
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

	// 코드길이
	memcpy(&codelen, ptr, sizeof(int));
	ptr += sizeof(int);
	// 코드
	memcpy(code, ptr, codelen);
	ptr += codelen;

	// data에 코드길이 패킹
	memcpy(ptr_data, &codelen, sizeof(int));
	ptr_data += sizeof(int);
	size += sizeof(int);
	// data에 코드 패킹
	memcpy(ptr_data, code, codelen);
	ptr_data += codelen;
	size += codelen;

	StorageManager::GetInstance()->PushData(PGAMEDATA_PARTY_LEAVE_INFO, data, size);
}

// 파티 탈퇴 결과
void InGameManager::InGame_Recv_Leave_Result(char * _buf)
{
	char* ptr = _buf;

	char data[BUFSIZE];
	memset(data, 0, sizeof(BUFSIZE));
	char* ptr_data = data;
	int size = 0;

	bool result = false;

	// 결과
	memcpy(&result, ptr, sizeof(bool));
	ptr += sizeof(bool);

	// data에 결과 패킹
	memcpy(ptr_data, &result, sizeof(bool));
	ptr_data += sizeof(bool);
	size += sizeof(bool);

	StorageManager::GetInstance()->PushData(PGAMEDATA_PARTY_LEAVE_RESULT, data, size);
}

// 파티방 터진결과
void InGameManager::InGame_Recv_PartyRoom_Remove(char * _buf)
{
	StorageManager::GetInstance()->PushData(PGAMEDATA_PARTY_PARTYROOM_REMOVE, 0, 0);
}

// 새로운 파티 리더 들어옴
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

	// 전 파티 리더 코드길이
	memcpy(&oldcodelen, ptr, sizeof(int));
	ptr += sizeof(int);
	// 전 파티 리더 코드
	memcpy(oldcode, ptr, oldcodelen);
	ptr += oldcodelen;

	// 현 파티 리더 코드길이
	memcpy(&newcodelen, ptr, sizeof(int));
	ptr += sizeof(int);
	// 현 파티 리더 코드
	memcpy(newcode, ptr, newcodelen);
	ptr += newcodelen;

	// data에 전 파티 리더 코드길이 패킹
	memcpy(ptr_data, &oldcodelen, sizeof(int));
	ptr_data += sizeof(int);
	size += sizeof(int);
	// data에 전 파티 리더 코드 패킹
	memcpy(ptr_data, oldcode, oldcodelen);
	ptr_data += oldcodelen;
	size += oldcodelen;

	// data에 현 파티 리더 코드길이 패킹
	memcpy(ptr_data, &newcodelen, sizeof(int));
	ptr_data += sizeof(int);
	size += sizeof(int);
	// data에 현 파티 리더 코드 패킹
	memcpy(ptr_data, newcode, newcodelen);
	ptr_data += newcodelen;
	size += newcodelen;

	StorageManager::GetInstance()->PushData(PGAMEDATA_PARTY_LEADER_INFO, data, size);
}

// 파티 리더 보낸 결과
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

	// 결과
	memcpy(&result, ptr, sizeof(bool));
	ptr += sizeof(bool);

	if (result == false)
	{
		// data에 결과 패킹
		memcpy(ptr_data, &result, sizeof(bool));
		ptr_data += sizeof(bool);
		size += sizeof(bool);

		StorageManager::GetInstance()->PushData(PGAMEDATA_PARTY_LEADER_DELEGATE_RESULT, data, size);
	}
	else
	{
		// 코드길이
		memcpy(&codelen, ptr, sizeof(int));
		ptr += sizeof(int);
		// 코드
		memcpy(code, ptr, codelen);
		ptr += codelen;

		// data에 결과 패킹
		memcpy(ptr_data, &result, sizeof(bool));
		ptr_data += sizeof(bool);
		size += sizeof(bool);
		// data에 코드길이 패킹
		memcpy(ptr_data, &codelen, sizeof(int));
		ptr_data += sizeof(int);
		size += sizeof(int);
		// data에 코드 패킹
		memcpy(ptr_data, code, codelen);
		ptr_data += codelen;
		size += codelen;

		StorageManager::GetInstance()->PushData(PGAMEDATA_PARTY_LEADER_DELEGATE_RESULT, data, size);
	}
}

// 던전 입장 결과
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

		// 코드 사이즈
		memcpy(&len, ptr_buf, sizeof(int));
		ptr_buf += sizeof(int);
		// 코드
		memcpy(code, ptr_buf, len);
		ptr_buf += len;
		// 스폰위치 언패
		memcpy(xyz, ptr_buf, sizeof(float) * 3);
		ptr_buf += sizeof(float) * 3;

		// data에 코드 길이
		memcpy(ptr_data, &len, sizeof(int));
		ptr_data += sizeof(int);
		size += sizeof(int);
		// data에 코드
		memcpy(ptr_data, code, len);
		ptr_data += len;
		size += len;
		// data에 스폰위치 패킹.x
		memcpy(ptr_data, &xyz[0], sizeof(float));
		ptr_data += sizeof(float);
		size += sizeof(float);
		// data에 스폰위치 패킹.y
		memcpy(ptr_data, &xyz[1], sizeof(float));
		ptr_data += sizeof(float);
		size += sizeof(float);
		// data에 스폰위치 패킹.z
		memcpy(ptr_data, &xyz[2], sizeof(float));
		ptr_data += sizeof(float);
		size += sizeof(float);

		StorageManager::GetInstance()->PushData(PGAMEDATA_PARTY_DUNGEON_SPAWNINFO, data, size);
	}
}

// 던정 퇴장 결과
void InGameManager::InGame_Recv_Leave_Dungeon_Leave_Result(char * _buf)
{
	char* ptr = _buf;

	char data[BUFSIZE];
	memset(data, 0, sizeof(BUFSIZE));
	char* ptr_data = data;
	int size = 0;

	int channelnum = 0;

	// 채널번호
	memcpy(&channelnum, ptr, sizeof(int));
	ptr += sizeof(int);

	// data에 채널번호 패킹
	memcpy(ptr_data, &channelnum, sizeof(int));
	ptr_data += sizeof(int);
	size += sizeof(int);

	StorageManager::GetInstance()->PushData(PGAMEDATA_PARTY_DUNGEON_LEAVE_RESULT, data, size);
}

// 스테이지 입장 결과
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

		// 코드 사이즈
		memcpy(&len, ptr_buf, sizeof(int));
		ptr_buf += sizeof(int);
		// 코드
		memcpy(code, ptr_buf, len);
		ptr_buf += len;
		// 스폰위치 언패
		memcpy(xyz, ptr_buf, sizeof(float) * 3);
		ptr_buf += sizeof(float) * 3;

		// data에 코드 길이
		memcpy(ptr_data, &len, sizeof(int));
		ptr_data += sizeof(int);
		size += sizeof(int);
		// data에 코드
		memcpy(ptr_data, code, len);
		ptr_data += len;
		size += len;
		// data에 스폰위치 패킹.x
		memcpy(ptr_data, &xyz[0], sizeof(float));
		ptr_data += sizeof(float);
		size += sizeof(float);
		// data에 스폰위치 패킹.y
		memcpy(ptr_data, &xyz[1], sizeof(float));
		ptr_data += sizeof(float);
		size += sizeof(float);
		// data에 스폰위치 패킹.z
		memcpy(ptr_data, &xyz[2], sizeof(float));
		ptr_data += sizeof(float);
		size += sizeof(float);

		StorageManager::GetInstance()->PushData(PGAMEDATA_PARTY_DUNGEON_STAGE_SPAWNINFO, data, size);
	}
}

// 스테이지 입장후 받는 몬스터정보(초기화정보)
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

	// 몬스터 종류 숫자
	memcpy(&monster_tpyes_count, ptr_buf, sizeof(int));
	ptr_buf += sizeof(int);

	StorageManager::GetInstance()->PushData(PGAMEDATA_STAGE_MONSTER_TPYES_COUNT, (void*)&monster_tpyes_count, sizeof(int));

	// 몬스터 스폰 시간
	memcpy(&monster_spawn_time, ptr_buf, sizeof(float));
	ptr_buf += sizeof(float);

	StorageManager::GetInstance()->PushData(PGAMEDATA_STAGE_MONSTER_SPAWN_TIME, (void*)&monster_spawn_time, sizeof(int));

	for (int i = 0; i < monster_tpyes_count; i++)
	{
		ptr_data = data;
		code = 0;
		monster_num = 0;
		size = 0;

		// 몬스터 코드
		memcpy(&code, ptr_buf, sizeof(int));
		ptr_buf += sizeof(int);
		// 몬스터 숫자
		memcpy(&monster_num, ptr_buf, sizeof(int));
		ptr_buf += sizeof(int);
		// 스폰위치
		memcpy(xyz, ptr_buf, sizeof(float) * 3);
		ptr_buf += sizeof(float) * 3;

		// data에 몬스터 코드 패킹
		memcpy(ptr_data, &code, sizeof(int));
		ptr_data += sizeof(int);
		size += sizeof(int);
		// data에 몬스터 숫자 패킹
		memcpy(ptr_data, &monster_num, sizeof(int));
		ptr_data += sizeof(int);
		size += sizeof(int);
		// data에 스폰위치 패킹.x
		memcpy(ptr_data, &xyz[0], sizeof(float));
		ptr_data += sizeof(float);
		size += sizeof(float);
		// data에 스폰위치 패킹.y
		memcpy(ptr_data, &xyz[1], sizeof(float));
		ptr_data += sizeof(float);
		size += sizeof(float);
		// data에 스폰위치 패킹.z
		memcpy(ptr_data, &xyz[2], sizeof(float));
		ptr_data += sizeof(float);
		size += sizeof(float);

		StorageManager::GetInstance()->PushData(PGAMEDATA_STAGE_MONSTER_INFO, data, size);
	}
}

// 몬스터 이동정보
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

	// 몬스터 코드
	memcpy(&code, ptr_buf, sizeof(int));
	ptr_buf += sizeof(int);
	size += sizeof(int);
	memcpy(ptr_data, &code, sizeof(int));
	ptr_data += sizeof(int);

	// 캐릭터 직업코드
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

// 파티 초대 요청
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

// 파티 초대 응답 [_result : 초대수락할지거절할지] [_code : 초대보낸사람의 코드를 넣습니다] [_partyroomnum : 초대보낸사람의 파티방번호를 넣습니다]
void InGameManager::InGame_Req_Party_Invite_Result(bool _result, char * _code, int _partyroomnum)
{
	UINT64 protocol = 0;
	char buf[BUFSIZE];
	memset(buf, 0, sizeof(buf));
	char* ptr = buf;
	int datasize = 0;

	int codelen = 0;
	codelen = strlen(_code) + 1;

	// 초대 결과
	memcpy(ptr, &_result, sizeof(bool));
	ptr += sizeof(bool);
	datasize += sizeof(bool);
	// 코드 길이
	memcpy(ptr, &codelen, sizeof(int));
	ptr += sizeof(int);
	datasize += sizeof(int);
	// 코드
	memcpy(ptr, _code, codelen);
	ptr += codelen;
	datasize += codelen;
	// 파티 번호
	memcpy(ptr, &_partyroomnum, sizeof(int));
	ptr += sizeof(int);
	datasize += sizeof(int);

	protocol = NetworkClient_main::NetworkManager::GetInstance()->GetUser()->BitPackProtocol(protocol, PROTOCOL_INGAME, PROTOCOL_INGAME_PARTY, PROTOCOL_PARTY_ROOM_ANSWER_INVITE);

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->pack(protocol, buf, datasize);
}

// 던전 입장 요청
void InGameManager::InGame_Req_Dungeon_Enter()
{
	UINT64 protocol = 0;
	char buf[BUFSIZE];
	memset(buf, 0, sizeof(buf));

	protocol = NetworkClient_main::NetworkManager::GetInstance()->GetUser()->BitPackProtocol(protocol, PROTOCOL_INGAME, PROTOCOL_INGAME_DUNGEON, PROTOCOL_REQ_DUNGEON_ENTER);

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->pack(protocol, buf, 0);
}

// 던전 퇴장 요청
void InGameManager::InGame_Req_Dungeon_Leave()
{
	UINT64 protocol = 0;
	char buf[BUFSIZE];
	memset(buf, 0, sizeof(buf));

	protocol = NetworkClient_main::NetworkManager::GetInstance()->GetUser()->BitPackProtocol(protocol, PROTOCOL_INGAME, PROTOCOL_INGAME_DUNGEON, PROTOCOL_REQ_DUNGEON_LEAVE);

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->pack(protocol, buf, 0);
}

// 스테이지 입장
void InGameManager::InGame_Req_Dungeon_Stage_Enter()
{
	UINT64 protocol = 0;
	char buf[BUFSIZE];
	memset(buf, 0, sizeof(buf));

	protocol = NetworkClient_main::NetworkManager::GetInstance()->GetUser()->BitPackProtocol(protocol, PROTOCOL_INGAME, PROTOCOL_INGAME_DUNGEON, PROTOCOL_DUNGEON_STAGE_IN);

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->pack(protocol, buf, 0);
}

// 몬스터 정보 요청
void InGameManager::InGame_Req_Monster_Info()
{
	UINT64 protocol = 0;
	char buf[BUFSIZE];
	memset(buf, 0, sizeof(buf));

	protocol = NetworkClient_main::NetworkManager::GetInstance()->GetUser()->BitPackProtocol(protocol, PROTOCOL_INGAME, PROTOCOL_INGMAE_MONSTER, PROTOCOL_REQ_MONSTER_INFO);

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->pack(protocol, buf, 0);
}

// 파티리더가 몬스터 이동 정보 전송
void InGameManager::InGame_Req_Monster_Move_Info(int _code, int _num, float _px, float _py, float _pz)
{
	UINT64 protocol = 0;
	char buf[BUFSIZE];
	char* ptr = buf;
	int datasize = 0;
	memset(buf, 0, sizeof(buf));

	// 몬스터 코드
	memcpy(ptr, &_code, sizeof(int));
	datasize += sizeof(int);
	ptr += sizeof(int);

	// 몬스터 번호
	memcpy(ptr, &_num, sizeof(int));
	datasize += sizeof(int);
	ptr += sizeof(int);

	// 위치값
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

RESULT InGameManager::InGameInitRecvResult(User * _user)
{
	UINT64 protocol = 0;
	char buf[BUFSIZE];

	RESULT result;
	bool check;

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->BitunPack(protocol, buf);

	// 프로토콜 중간틀 캐릭터관련 이면
	if ((protocol&PROTOCOL_INGAME_CHARACER) == PROTOCOL_INGAME_CHARACER)
	{
		// 유저들 정보
		if ((protocol&PROTOCOL_INGAME_OTHERPLAYERLIST_INFO) == PROTOCOL_INGAME_OTHERPLAYERLIST_INFO)
		{
			check = InGame_Recv_UserList(buf);
			if (check)
			{
				result = RT_INGAME_OTHERPLAYER_LIST;
			}
		}
		// 유저 이동 결과
		else if ((protocol&PROTOCOL_INGAME_MOVE_RESULT) == PROTOCOL_INGAME_MOVE_RESULT)
		{
			check = InGame_Recv_MoveResult(buf);
			if (check)	// 이동 성공
			{
				result = RT_INGAME_MOVE;
			}
			else		// 이동 실패
			{
				result = RT_INGAME_MOVE;
			}
		}
		// 다른 유저 이동 정보
		else if ((protocol&PROTOCOL_INGAME_MOVE_OTHERPLAYERINFO) == PROTOCOL_INGAME_MOVE_OTHERPLAYERINFO)
		{
			InGame_Recv_OtherUserMoveInfo(buf, PGAMEDATA_PLAYER_OTHERMOVEINFO);
			result = RT_INGAME_OTHERPLAYER_INFO;
		}
		// 다른 유저 회전 정보
		else if ((protocol&PROTOCOL_INGAME_MOVE_ROTATION) == PROTOCOL_INGAME_MOVE_ROTATION)
		{
			InGame_Recv_OtherUserRotation(buf);
			result = RT_INGAME_MOVE;
		}
		// 다른 유저 접속정보
		else if ((protocol&PROTOCOL_INGAME_OTHERPLAYER_CONNECT) == PROTOCOL_INGAME_OTHERPLAYER_CONNECT)
		{
			InGame_Recv_ConnectUserInfo(buf);
			result = RT_INGAME_OTHERPLAYER_INFO;
		}
		// 다른 유저 나간정보
		else if ((protocol&PROTOCOL_INGAME_OTHERPLAYER_LEAVE) == PROTOCOL_INGAME_OTHERPLAYER_LEAVE)
		{
			InGame_Recv_OtherUserLeave(buf);
			result = RT_INGAME_OTHERPLAYER_LEAVE;
		}

	}

	// 프로토콜 중간틀 애니메이션관련 이면
	if ((protocol&PROTOCOL_INGAME_ANIMATION) == PROTOCOL_INGAME_ANIMATION)
	{
		// 캐릭터 애니메이션
		if ((protocol&PROTOCOL_CHARACER_ANIMATION) == PROTOCOL_CHARACER_ANIMATION)
		{

		}
		// 몬스터 애니메이션
		else if ((protocol&PROTOCOL_MONSTER_ANIMATION) == PROTOCOL_MONSTER_ANIMATION)
		{

		}
	}

	// 프로토콜 중간틀 채널관련 이면
	if ((protocol&PROTOCOL_INGAME_CHANNEL) == PROTOCOL_INGAME_CHANNEL)
	{
		// 채널 정보
		if ((protocol&PROTOCOL_CHANNLE_INFO) == PROTOCOL_CHANNLE_INFO)
		{
			InGame_Recv_ChannelInfo(buf);
			result = RT_INGAME_CHANNEL_INFO;
		}
		// 채널 변경 결과
		else if ((protocol&PROTOCOL_CHANNLE_CHANGE_RESULT) == PROTOCOL_CHANNLE_CHANGE_RESULT)
		{
			InGame_Recv_ChannelChange(buf);
			result = RT_INGAME_CHANNEL_CHANGE;
		}
		// 채널 이동한 유저 정보
		else if ((protocol&PROTOCOL_CHANNLE_USER_CHANGE) == PROTOCOL_CHANNLE_USER_CHANGE)
		{
			InGame_Recv_OtherUserLeave(buf);
			result = RT_INGAME_OTHERPLAYER_LEAVE;
		}
	}

	// 프로토콜 중간틀 파티관련 이면
	if ((protocol&PROTOCOL_INGAME_PARTY) == PROTOCOL_INGAME_PARTY)
	{
		// 파티 초대(특정유저에게)
		if ((protocol&PROTOCOL_PARTY_ROOM_INVITE) == PROTOCOL_PARTY_ROOM_INVITE)
		{
			InGame_Recv_Invite(buf);
			result = RT_INGAME_PARTY_INVITE;
		}
		// 파티 초대 결과
		else if ((protocol&PROTOCOL_PARTY_ROOM_INVITE_RESULT) == PROTOCOL_PARTY_ROOM_INVITE_RESULT)
		{
			InGame_Recv_Invite_Result(buf);
			result = RT_INGAME_PARTY_INVITE_RESULT;
		}
		// 참여 결과
		else if ((protocol&PROTOCOL_PARTY_ROOM_JOIN_RESULT) == PROTOCOL_PARTY_ROOM_JOIN_RESULT)
		{
			InGame_Recv_Join_Result(buf);
			result = RT_INGAME_PARTY_JOIN_RESULT;
		}
		// 새로운 파티원이 들어옴
		else if ((protocol&PROTOCOL_PARTY_ROOM_ADD_USER) == PROTOCOL_PARTY_ROOM_ADD_USER)
		{
			InGame_Recv_Party_User_Info(buf);
			result = RT_INGAME_PARTY_ADD_USER;
		}
		// 강퇴당한사람에게 보내는 프로토콜
		else if ((protocol&PROTOCOL_PARTY_USER_KICK) == PROTOCOL_PARTY_USER_KICK)
		{
			// 프로토콜만 온다
			InGame_Recv_Kick();
			result = RT_INGAME_PARTY_KICK;
		}
		// 강퇴당한 유저 정보
		else if ((protocol&PROTOCOL_PARTY_USER_KICK_INFO) == PROTOCOL_PARTY_USER_KICK_INFO)
		{
			// 유저코드 온다
			InGame_Recv_Kick_User_Info(buf);
			result = RT_INGAME_PARTY_KICK_USER_INFO;
		}
		// 강퇴결과
		else if ((protocol&PROTOCOL_PARTY_USER_KICK_RESULT) == PROTOCOL_PARTY_USER_KICK_RESULT)
		{
			// 결과 온다. 성공이면 뒤에 코드도 온다
			InGame_Recv_Kick_Result(buf);
			result = RT_INGAME_PARTY_KICK_RESULT;
		}
		// 탈퇴하는 유저 정보
		else if ((protocol&PROTOCOL_PARTY_USER_LEAVE_INFO) == PROTOCOL_PARTY_USER_LEAVE_INFO)
		{
			// 캐릭터 코드 온다
			InGame_Recv_Leave_User_Info(buf);
			result = RT_INGAME_PARTY_LEAVE_INFO;
		}
		// 탈퇴결과
		else if ((protocol&PROTOCOL_PARTY_USER_LEAVE_RESULT) == PROTOCOL_PARTY_USER_LEAVE_RESULT)
		{
			// 성공 실패 여부만 온다
			InGame_Recv_Leave_Result(buf);
			result = RT_INGAME_PARTY_LEAVE_RESULT;
		}
		// 파티방 사라졌을때 보내는 프로토콜
		else if ((protocol&PROTOCOL_PARTY_ROOM_REMOVE_RESULT) == PROTOCOL_PARTY_ROOM_REMOVE_RESULT)
		{
			// 파티방 터졌다는 프로토콜만 온다
			InGame_Recv_PartyRoom_Remove(buf);
			result = RT_INGAME_PARTY_ROOM_REMOVE;
		}
		// 리더 위임 받은 유저 정보
		else if ((protocol&PROTOCOL_PARTY_LEADER_DELEGATE) == PROTOCOL_PARTY_LEADER_DELEGATE)
		{
			// 파티방 구 리더, 새로운 리더 코드가 온다
			InGame_Recv_PartyRoom_Leader_Info(buf);
			result = RT_INGAME_PARTY_LEADER_DELEGATE;
		}
		// 리더 위임 결과
		else if ((protocol&PROTOCOL_PARTY_LEADER_DELEGATE_RESULT) == PROTOCOL_PARTY_LEADER_DELEGATE_RESULT)
		{
			// 리더 위임 결과가 오고 성공이면 뒤에 코드도 온다.
			InGame_Recv_PartyRoom_Leader_Delegate_Result(buf);
			result = RT_INGAME_PARTY_LEADER_DELEGATE_RESULT;
		}
		// 파티원정보
		else if ((protocol&PROTOCOL_PARTY_USER_INFO) == PROTOCOL_PARTY_USER_INFO)
		{

		}
	}

	// 프로토콜 중간틀 던전관련 이면
	if ((protocol&PROTOCOL_INGAME_DUNGEON) == PROTOCOL_INGAME_DUNGEON)
	{
		// 던전 입장 결과
		if ((protocol&PROTOCOL_DUNGEON_ENTER_RESULT) == PROTOCOL_DUNGEON_ENTER_RESULT)
		{
			// 던전 스폰 위치 옴(Vector3)
			InGame_Recv_Leave_Dungeon_Enter_Result(buf);
			result = RT_INGAME_DUNGEON_ENTER_RESULT;
		}
		// 던전 퇴장 결과
		else if ((protocol&PROTOCOL_DUNGEON_LEAVE_RESULT) == PROTOCOL_DUNGEON_LEAVE_RESULT)
		{
			// 채널번호옴
			InGame_Recv_Leave_Dungeon_Leave_Result(buf);
			result = RT_INGAME_DUNGEON_LEAVE_RESULT;
		}
		// 스테이지 입장 결과
		else if ((protocol&PROTOCOL_DUNGEON_STAGE_IN_RESULT) == PROTOCOL_DUNGEON_STAGE_IN_RESULT)
		{
			// 스테이지 입장 결과옴(Vector3)
			InGame_Recv_Stage_Enter_Result(buf);
			result = RT_INGAME_DUNGEON_STAGE_ENTER_RESULT;
		}
	}


	// 프로토콜 중간틀 몬스터관련 이면
	if ((protocol&PROTOCOL_INGMAE_MONSTER) == PROTOCOL_INGMAE_MONSTER)
	{
		// 몬스터 이동 정보
		if ((protocol&PROTOCOL_MONSTER_MOVE_RESULT) == PROTOCOL_MONSTER_MOVE_RESULT)
		{
			// 몬스터 이동정보 옴
			InGame_Recv_Monster_MoveInfo(buf);
			result = RT_INGAME_MONSTER_MOVE_INFO_RESULT;
		}
		// 몬스터 정보
		else if ((protocol&PROTOCOL_MONSTER_INFO) == PROTOCOL_MONSTER_INFO)
		{
			// 몬스터 정보 옴
			InGame_Recv_Stage_MonsterInfo(buf);
			result = RT_INGAME_MONSTER_INFO_RESULT;
		}
	}

	// 프로토콜 중간틀 매뉴관련 이면
	if ((protocol&PROTOCOL_INGMAE_MENU) == PROTOCOL_INGMAE_MENU)
	{
		// 캐릭터 생성요청 결과
		if ((protocol&PROTOCOL_MENU_RESULT_CHARACTER) == PROTOCOL_MENU_RESULT_CHARACTER)
		{
			InGame_Recv_CharacterSelect();
			result = RT_INGAME_MENU_CHARACTER;
		}
		// 캐릭터 삭제 요청 결과
		else if ((protocol&PROTOCOL_MENU_RESULT_LOGOUT) == PROTOCOL_MENU_RESULT_LOGOUT)
		{
			InGame_Recv_Logout();
			result = RT_INGAME_MENU_LOGOUT;
		}
		// 캐릭터 삭제 요청 결과
		else if ((protocol&PROTOCOL_OTHERPLAYER_LEAVE) == PROTOCOL_OTHERPLAYER_LEAVE)
		{

		}
	}


	/*
	switch (protocol)
	{
	case SERVER_INGAME_OTHERPLAYER_CONNECT:
		InGame_Recv_ConnectUserInfo(buf);
		result = RT_INGAME_OTHERPLAYER_INFO;
		break;
	case SERVER_INGAME_MOVE_RESULT:
		check = InGame_Recv_MoveResult(buf);
		if (check)	// 이동 성공
		{
			result = RT_INGAME_MOVE;
		}
		else		// 이동 실패
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
	case SERVER_INGAME_PARTY_ROOM_INVITE:
		InGame_Recv_Invite(buf);
		result = RT_INGAME_PARTY_INVITE;
		break;
	case SERVER_INGAME_PARTY_ROOM_INVITE_RESULT:
		InGame_Recv_Invite_Result(buf);
		result = RT_INGAME_PARTY_INVITE_RESULT;
		break;
	case SERVER_INGAME_PARTY_ROOM_JOIN_RESULT:
		InGame_Recv_Join_Result(buf);
		result = RT_INGAME_PARTY_JOIN_RESULT;
		break;
	case SERVER_INGAME_PARTY_ROOM_ADD_USER:
		InGame_Recv_Party_User_Info(buf);
		result = RT_INGAME_PARTY_ADD_USER;
		break;
	case SERVER_INGAME_PARTY_USER_KICK:
		// 프로토콜만 온다
		InGame_Recv_Kick();
		result = RT_INGAME_PARTY_KICK;
		break;
	case SERVER_INGAME_PARTY_USER_KICK_INFO:
		// 유저코드 온다
		InGame_Recv_Kick_User_Info(buf);
		result = RT_INGAME_PARTY_KICK_USER_INFO;
		break;
	case SERVER_INGAME_PARTY_USER_KICK_RESULT:
		// 결과 온다. 성공이면 뒤에 코드도 온다
		InGame_Recv_Kick_Result(buf);
		result = RT_INGAME_PARTY_KICK_RESULT;
		break;
	case SERVER_INGAME_PARTY_USER_LEAVE_INFO:
		// 캐릭터 코드 온다
		InGame_Recv_Leave_User_Info(buf);
		result = RT_INGAME_PARTY_LEAVE_INFO;
		break;
	case SERVER_INGAME_PARTY_USER_LEAVE_RESULT:
		// 성공 실패 여부만 온다
		InGame_Recv_Leave_Result(buf);
		result = RT_INGAME_PARTY_LEAVE_RESULT;
		break;
	case SERVER_INGAME_PARTY_ROOM_REMOVE_RESULT:
		// 파티방 터졌다는 프로토콜만 온다
		InGame_Recv_PartyRoom_Remove(buf);
		result = RT_INGAME_PARTY_ROOM_REMOVE;
		break;
	case SERVER_INGAME_PARTY_LEADER_DELEGATE:
		// 파티방 구 리더, 새로운 리더 코드가 온다
		InGame_Recv_PartyRoom_Leader_Info(buf);
		result = RT_INGAME_PARTY_LEADER_DELEGATE;
		break;
	case SERVER_INGAME_PARTY_LEADER_DELEGATE_RESULT:
		// 리더 위임 결과가 오고 성공이면 뒤에 코드도 온다.
		InGame_Recv_PartyRoom_Leader_Delegate_Result(buf);
		result = RT_INGAME_PARTY_LEADER_DELEGATE_RESULT;
		break;
	case SERVER_INGAME_DUNGEON_ENTER_RESULT:
		// 던전 스폰 위치 옴(Vector3)
		InGame_Recv_Leave_Dungeon_Enter_Result(buf);
		result = RT_INGAME_DUNGEON_ENTER_RESULT;
		break;
	case SERVER_INGAME_DUNGEON_LEAVE_RESULT:
		// 채널번호옴
		InGame_Recv_Leave_Dungeon_Leave_Result(buf);
		result = RT_INGAME_DUNGEON_LEAVE_RESULT;
		break;
	case SERVER_INGAME_DUNGEON_STAGE_IN_REULST:
		// 스테이지 입장 결과옴(Vector3)
		InGame_Recv_Stage_Enter_Result(buf);
		result = RT_INGAME_DUNGEON_STAGE_ENTER_RESULT;
		break;
	case SERVER_INGAME_MONSTER_INFO:
		// 몬스터 정보 옴
		InGame_Recv_Stage_MonsterInfo(buf);
		result = RT_INGAME_MONSTER_INFO_RESULT;
		break;
	case SERVER_INGAME_MONSTER_MOVE_RESULT:
		// 몬스터 이동정보 옴
		InGame_Recv_Monster_MoveInfo(buf);
		result = RT_INGAME_MONSTER_MOVE_INFO_RESULT;
		break;
	default:
		break;
	}
	*/

	return result;
}
