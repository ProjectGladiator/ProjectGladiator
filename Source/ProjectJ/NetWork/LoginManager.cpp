#include "LoginManager.h"
#include "NetworkManager.h"
#include "LogManager.h"

LoginManager* LoginManager::Instance = nullptr;

LoginManager::LoginManager()
{

}

LoginManager::~LoginManager()
{

}

const UserInfo* LoginManager::getUser(const char* id)
{

	return nullptr;
}

void LoginManager::CreateInstance()
{
	if (Instance == nullptr)
	{
		Instance = new LoginManager();
	}
}

LoginManager* LoginManager::GetInstance()
{
	return Instance;
}

void LoginManager::DestroyInstance()
{
	if (Instance != nullptr)
	{
		delete Instance;
		Instance = nullptr;
	}
}

bool LoginManager::InitializeManager()
{
	return true;
}

void LoginManager::EndManager()
{
}

// 로그인/회원가입 매뉴 선택
void LoginManager::logoutMenuChoice()
{
	char buf[BUFSIZE];
	memset(buf, 0, sizeof(buf));

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->pack(CLIENT_JOIN_MENU_CHOICE, buf, 0);
}

void LoginManager::exitJoin()
{
	char buf[BUFSIZE];
	memset(buf, 0, sizeof(buf));

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->pack(CLIENT_REQ_EXIT_JOIN, buf, 0);

}

// 아이디 중복체크 요청
void LoginManager::reqIdOverlapCheck(char* _id)
{
	UINT64 protocol = 0;
	char buf[BUFSIZE];
	memset(buf, 0, sizeof(buf));

	int idlen = strlen(_id) + 1;
	char* ptr = buf;

	int size = sizeof(int) + idlen;

	memcpy(ptr, &idlen, sizeof(int));
	ptr += sizeof(int);

	memcpy(ptr, _id, idlen);

	protocol = NetworkClient_main::NetworkManager::GetInstance()->GetUser()->BitPackProtocol(protocol, PROTOCOL_TITLE, PROTOCOL_LOGIN, PROTOCOL_REQ_ID_OVERLAP_CHECK);

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->pack(protocol, buf, size);
}

// 아이디 중복체크 결과
bool LoginManager::IdOverlapCheck(char* _buf)
{
	bool check;
	memcpy(&check, _buf, sizeof(bool));

	if (!check)
	{
		// 아이디 중복이 없을때
		return true;
	}
	else
	{
		// 아이디 중복이 있을때
		return false;
	}
}

// 회원가입 요청
void LoginManager::reqJoin(char* _id, char* _pw)
{
	UINT64 protocol = 0;
	char buf[BUFSIZE];
	memset(buf, 0, sizeof(buf));

	int idlen = strlen(_id) + 1;
	int pwlen = strlen(_pw) + 1;
	char* ptr = buf;

	int size = sizeof(int) + idlen + sizeof(int) + pwlen;

	memcpy(ptr, &idlen, sizeof(int));
	ptr += sizeof(int);

	memcpy(ptr, _id, idlen);
	ptr += idlen;

	memcpy(ptr, &pwlen, sizeof(int));
	ptr += sizeof(int);

	memcpy(ptr, _pw, pwlen);

	protocol = NetworkClient_main::NetworkManager::GetInstance()->GetUser()->BitPackProtocol(protocol, PROTOCOL_TITLE, PROTOCOL_LOGIN, PROTOCOL_REQ_JOIN);

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->pack(protocol, buf, size);
}

// 로그인 요청
void LoginManager::reqLogin(char* _id, char* _pw)
{
	UINT64 protocol = 0;
	char buf[BUFSIZE];
	memset(buf, 0, sizeof(buf));

	int idlen = strlen(_id) + 1;
	int pwlen = strlen(_pw) + 1;
	char* ptr = buf;

	int size = sizeof(int) + idlen + sizeof(int) + pwlen;

	memcpy(ptr, &idlen, sizeof(int));
	ptr += sizeof(int);

	memcpy(ptr, _id, idlen);
	ptr += idlen;

	memcpy(ptr, &pwlen, sizeof(int));
	ptr += sizeof(int);

	memcpy(ptr, _pw, pwlen);

	protocol = NetworkClient_main::NetworkManager::GetInstance()->GetUser()->BitPackProtocol(protocol, PROTOCOL_TITLE, PROTOCOL_LOGIN,PROTOCOL_REQ_LOGIN);

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->pack(protocol, buf, size);
}

// 타이틀화면일때
RESULT LoginManager::TitleRecvResult()
{
	UINT64 protocol = 0;
	UINT64 compartrprotocol = 0;
	UINT64 tempprotocol = 0;
	char buf[BUFSIZE];

	RESULT state;
	bool result = false;
	bool isLogin = false;

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->BitunPack(protocol, buf);

	compartrprotocol = PROTOCOL_CHARACER_MENU;

	tempprotocol = 0;

	tempprotocol = protocol & compartrprotocol;
	switch (tempprotocol)
	{
	case PROTOCOL_CHARACER_MENU: // 중간틀 로그인이면
		tempprotocol = protocol & PROTOCOL_SERVER_LOGIN_MENU_COMPARE;
		switch (tempprotocol)
		{
		case PROTOCOL_ID_OVERLAP_CHECK: // 아이디 중복확인
			result = IdOverlapCheck(buf);
			StorageManager::GetInstance()->PushData(PLOGIN_IDOVERLAP_RESULT, (void*)&result, sizeof(bool));
			if (result == true)
			{
				// ID 중복체크 결과 중복없을때
				state = RT_ID_OVERLAP_SUCCESS;
			}
			else
			{
				// ID 중복체크 결과 중복있을때
				state = RT_ID_OVERLAP_FAIL;
			}
			break;
		case PROTOCOL_JOIN_RESULT: // 가입 요청
			result = Join(buf);
			StorageManager::GetInstance()->PushData(PLOGIN_JOIN_RESULT, (void*)&result, sizeof(bool));
			if (result == true)
			{
				// 회원가입 성공일때
				state = RT_JOIN;
			}
			else
			{
				// 회원가입 실패일때
				state = RT_JOIN_FAIL;
			}
			break;
		case PROTOCOL_LOGIN_RESULT: // 로그인 요청 결과
			isLogin = Login(buf);
			if (isLogin == true)
			{
				// 로그인성공 이후 상태변경
				NetworkClient_main::NetworkManager::GetInstance()->GetUser()->setLogin();
				state = RT_LOGIN;
			}
			else
			{
				// 로그인실패
				state = RT_LOGINFAIL;
			}
			StorageManager::GetInstance()->PushData(PLOGIN_LOGIN_RESULT, (void*)&isLogin, sizeof(bool));
			break;

		default:
			break;
		}
		break;
	default:
		break;
	}

	return state;
}

RESULT LoginManager::InitRecvResult()
{
	PROTOCOL protocol;
	char buf[BUFSIZE];

	RESULT result;
	bool isLogin = false;

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->unPack(&protocol, buf);

	switch (protocol)
	{
	case SERVER_LOGIN_SUCCESS:
		isLogin = Login(buf);
		if (isLogin == true)
		{
			// 로그인성공 이후 상태변경
			NetworkClient_main::NetworkManager::GetInstance()->GetUser()->setLogin();
			result = RT_LOGIN;
		}
		else
		{
			// 로그인실패
			result = RT_LOGINFAIL;
		}
		StorageManager::GetInstance()->PushData(PLOGIN_LOGIN_RESULT, (void*)&isLogin, sizeof(bool));
		break;
	default:
		break;
	}
	return result;
}

RESULT LoginManager::JoinRecvResult()
{
	PROTOCOL protocol;
	char buf[BUFSIZE];
	bool result;

	RESULT state;

	NetworkClient_main::NetworkManager::GetInstance()->GetUser()->unPack(&protocol, buf);

	switch (protocol)
	{
	case SERVER_ID_OVERLAP_CHECK:
		result = IdOverlapCheck(buf);
		StorageManager::GetInstance()->PushData(PLOGIN_IDOVERLAP_RESULT, (void*)&result, sizeof(bool));
		if (result == true)
		{
			// ID 중복체크 결과 중복없을때
			state = RT_ID_OVERLAP_SUCCESS;
		}
		else
		{
			// ID 중복체크 결과 중복있을때
			state = RT_ID_OVERLAP_FAIL;
		}
		break;
	case SERVER_JOIN_SUCCESS:
		result = Join(buf);
		StorageManager::GetInstance()->PushData(PLOGIN_JOIN_RESULT, (void*)&result, sizeof(bool));
		if (result == true)
		{
			// 회원가입 성공일때
			state = RT_JOIN;
		}
		else
		{
			// 회원가입 실패일때
			state = RT_JOIN_FAIL;
		}
		break;
	default:
		break;
	}
	return state;
}

// 회원가입 결과
bool LoginManager::Join(char * _buf)
{
	bool check;

	memcpy(&check, _buf, sizeof(bool));

	if (check)
	{
		// 회원가입 성공
		return true;
	}
	else
	{
		// 회원가입 실패
		return false;
	}
}

// 로그인 결과
bool LoginManager::Login(char * _buf)
{
	bool check;

	memcpy(&check, _buf, sizeof(bool));
	StorageManager::GetInstance()->PushData(PLOGIN_LOGIN_RESULT, &check, sizeof(bool));

	if (check)
	{
		// 로그인 성공
		return true;
	}
	else
	{
		// 로그인 실패
		return false;
	}
}

// 로그인 결과
bool LoginManager::isLogin()
{
	StorageManager::GetInstance()->PopData();
	return NetworkClient_main::NetworkManager::GetInstance()->GetUser()->isLogin();
}

// 회원가입 결과
bool LoginManager::isJoin()
{
	PacketData* paketdata;
	if (StorageManager::GetInstance()->GetFront(paketdata))
	{
		if (paketdata->protocol == PLOGIN_JOIN_RESULT)
		{
			bool joinresult;
			StorageManager::GetInstance()->ChangeData(paketdata->data, joinresult);
			StorageManager::GetInstance()->PopData();
			return joinresult;
		}
	}

	return false;
}
