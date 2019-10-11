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

// �α���/ȸ������ �Ŵ� ����
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

// ���̵� �ߺ�üũ ��û
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

// ���̵� �ߺ�üũ ���
bool LoginManager::IdOverlapCheck(char* _buf)
{
	bool check;
	memcpy(&check, _buf, sizeof(bool));

	if (!check)
	{
		// ���̵� �ߺ��� ������
		return true;
	}
	else
	{
		// ���̵� �ߺ��� ������
		return false;
	}
}

// ȸ������ ��û
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

// �α��� ��û
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

// Ÿ��Ʋȭ���϶�
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
	case PROTOCOL_CHARACER_MENU: // �߰�Ʋ �α����̸�
		tempprotocol = protocol & PROTOCOL_SERVER_LOGIN_MENU_COMPARE;
		switch (tempprotocol)
		{
		case PROTOCOL_ID_OVERLAP_CHECK: // ���̵� �ߺ�Ȯ��
			result = IdOverlapCheck(buf);
			StorageManager::GetInstance()->PushData(PLOGIN_IDOVERLAP_RESULT, (void*)&result, sizeof(bool));
			if (result == true)
			{
				// ID �ߺ�üũ ��� �ߺ�������
				state = RT_ID_OVERLAP_SUCCESS;
			}
			else
			{
				// ID �ߺ�üũ ��� �ߺ�������
				state = RT_ID_OVERLAP_FAIL;
			}
			break;
		case PROTOCOL_JOIN_RESULT: // ���� ��û
			result = Join(buf);
			StorageManager::GetInstance()->PushData(PLOGIN_JOIN_RESULT, (void*)&result, sizeof(bool));
			if (result == true)
			{
				// ȸ������ �����϶�
				state = RT_JOIN;
			}
			else
			{
				// ȸ������ �����϶�
				state = RT_JOIN_FAIL;
			}
			break;
		case PROTOCOL_LOGIN_RESULT: // �α��� ��û ���
			isLogin = Login(buf);
			if (isLogin == true)
			{
				// �α��μ��� ���� ���º���
				NetworkClient_main::NetworkManager::GetInstance()->GetUser()->setLogin();
				state = RT_LOGIN;
			}
			else
			{
				// �α��ν���
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
			// �α��μ��� ���� ���º���
			NetworkClient_main::NetworkManager::GetInstance()->GetUser()->setLogin();
			result = RT_LOGIN;
		}
		else
		{
			// �α��ν���
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
			// ID �ߺ�üũ ��� �ߺ�������
			state = RT_ID_OVERLAP_SUCCESS;
		}
		else
		{
			// ID �ߺ�üũ ��� �ߺ�������
			state = RT_ID_OVERLAP_FAIL;
		}
		break;
	case SERVER_JOIN_SUCCESS:
		result = Join(buf);
		StorageManager::GetInstance()->PushData(PLOGIN_JOIN_RESULT, (void*)&result, sizeof(bool));
		if (result == true)
		{
			// ȸ������ �����϶�
			state = RT_JOIN;
		}
		else
		{
			// ȸ������ �����϶�
			state = RT_JOIN_FAIL;
		}
		break;
	default:
		break;
	}
	return state;
}

// ȸ������ ���
bool LoginManager::Join(char * _buf)
{
	bool check;

	memcpy(&check, _buf, sizeof(bool));

	if (check)
	{
		// ȸ������ ����
		return true;
	}
	else
	{
		// ȸ������ ����
		return false;
	}
}

// �α��� ���
bool LoginManager::Login(char * _buf)
{
	bool check;

	memcpy(&check, _buf, sizeof(bool));
	StorageManager::GetInstance()->PushData(PLOGIN_LOGIN_RESULT, &check, sizeof(bool));

	if (check)
	{
		// �α��� ����
		return true;
	}
	else
	{
		// �α��� ����
		return false;
	}
}

// �α��� ���
bool LoginManager::isLogin()
{
	StorageManager::GetInstance()->PopData();
	return NetworkClient_main::NetworkManager::GetInstance()->GetUser()->isLogin();
}

// ȸ������ ���
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
