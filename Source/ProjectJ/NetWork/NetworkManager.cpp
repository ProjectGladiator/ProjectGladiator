#include "NetworkManager.h"

using namespace NetworkClient_main;

NetworkManager* NetworkManager::Instance = nullptr;

NetworkManager::NetworkManager()
{

}
NetworkManager::~NetworkManager()
{

}

void NetworkManager::CreateInstance()
{
	if (Instance == nullptr)
	{
		Instance = new NetworkManager();
		LogManager::CreateInstance();
		ErrorManager::CreateInstance();
		ThreadManager::CreateInstance();
		LoginManager::CreateInstance();
		StorageManager::CreateInstance();
		EncryptManager::CreateInstance(ENCRYPT_KEY);
	}
}
NetworkManager* NetworkManager::GetInstance()
{
	return Instance;
}
void NetworkManager::DestroyInstance()
{
	if (Instance != nullptr)
	{
		delete Instance;
		Instance = nullptr;

		ThreadManager::DestroyInstance();
		LoginManager::DestroyInstance();
		StorageManager::DestroyInstance();
		EncryptManager::DestroyInstance();
		ErrorManager::DestroyInstance();
		LogManager::DestroyInstance();
	}
}

// ��Ŷ ����
void NetworkManager::Recvprocess()
{
	while (1)
	{
		// Recv
		if (user->recvMsg() == false)
		{
			user->InitState();
			break;
		}
		else
		{
			// �Ϸ� ����
			if (user->isRecvSuccess() == false)
			{
				continue;
			}

			// �ļ� �۾�
			if (user->getState()->Read(user) == false)
			{
				user->InitState();
			}
			else
			{
				SetEvent(RecvEvent);
			}
		}
	}
}

// ��Ŷ ����
bool NetworkManager::Send()
{
	while (1)
	{
		// Send
		if (user->sendMsg() == false)
		{
			return false;
		}
		else
		{
			// ���� �Ϸ� ����
			if (user->isSendSuccess())
			{
				return true;
			}
		}
	}
}

bool NetworkManager::Initialize()
{	// ���� �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)	// ���� DLL �ʱ�ȭ(DLL�� �޸𸮿� �ø�). ����ϱ⿡ �ռ� "ws2_32"���̺귯���� ���Խ��������.( #pragma comment(lib, "ws2_32")  )
	{
		LogManager::GetInstance()->SetTime();
		LogManager::GetInstance()->LogWrite("NetworkManager::Initialize : ERROR : WSAStartup() failed ");
		return false;
	}

	// recv �̺�Ʈ ����
	RecvEvent = CreateEvent(NULL, FALSE, NULL, NULL);
	return true;
}

bool NetworkManager::InitializeSocket()
{
	user = new User();

	if (user->createSocket() == false)
	{
		delete user;
		user = nullptr;
		ErrorManager::GetInstance()->err_display("createSocket() Error");
		return false;
	}

	user->InitState();

	return true;
}

bool NetworkManager::Connect()
{
	if (user->connect_client(SERVERIP, SERVERPORT) == false)
	{
		ErrorManager::GetInstance()->err_display("start() Error");
		return false;
	}
	else
	{
		CreatRecvThread();
		return true;
	}
}

void NetworkClient_main::NetworkManager::Wait()
{
	WaitForSingleObject(RecvEvent, INFINITE);
}

HANDLE NetworkManager::CreatRecvThread()
{
	// RecvThread ����
	HANDLE hrecv = ThreadManager::GetInstance()->addThread(ThreadManager::RecvProcess, 0, this);

	return hrecv;
}

bool NetworkManager::MangerInitialize()
{
	LogManager::GetInstance()->InitializeManager();
	ThreadManager::GetInstance()->InitializeManager();
	LoginManager::GetInstance()->InitializeManager();
	ErrorManager::GetInstance()->InitializeManager();
	EncryptManager::GetInstance()->InitializeManager();

	return true;
}

void NetworkManager::EndManager()
{
	user->stop();
	delete user;

	// �� �Ŵ����� End ȣ��
	LoginManager::GetInstance()->EndManager();
	EncryptManager::GetInstance()->EndManager();
	ThreadManager::GetInstance()->EndManager();
	LogManager::GetInstance()->EndManager();
	ErrorManager::GetInstance()->EndManager();

	// ���� ����
	WSACleanup();	// ���� DLL �޸� ����
}
