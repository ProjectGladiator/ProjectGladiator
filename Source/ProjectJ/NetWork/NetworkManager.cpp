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

// 패킷 수신
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
			// 완료 여부
			if (user->isRecvSuccess() == false)
			{
				continue;
			}

			// 후속 작업
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

// 패킷 전송
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
			// 전송 완료 여부
			if (user->isSendSuccess())
			{
				return true;
			}
		}
	}
}

bool NetworkManager::Initialize()
{	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)	// 소켓 DLL 초기화(DLL을 메모리에 올림). 사용하기에 앞서 "ws2_32"라이브러리를 포함시켜줘야함.( #pragma comment(lib, "ws2_32")  )
	{
		LogManager::GetInstance()->SetTime();
		LogManager::GetInstance()->LogWrite("NetworkManager::Initialize : ERROR : WSAStartup() failed ");
		return false;
	}

	// recv 이벤트 생성
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
	// RecvThread 생성
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

	// 각 매니저들 End 호출
	LoginManager::GetInstance()->EndManager();
	EncryptManager::GetInstance()->EndManager();
	ThreadManager::GetInstance()->EndManager();
	LogManager::GetInstance()->EndManager();
	ErrorManager::GetInstance()->EndManager();

	// 윈속 종료
	WSACleanup();	// 소켓 DLL 메모리 해제
}
