#ifndef _NETWORK_MANAGER_H
#define _NETWORK_MANAGER_H
#include "LoginManager.h"
#include "ErrorManager.h"
#include "ThreadManager.h"
#include "EnryptManager.h"
#include "StorageManager.h"

namespace NetworkClient_main
{
	class NetworkManager
	{
	private:
		static NetworkManager* Instance;
		User* user;
		HANDLE RecvEvent;

		NetworkManager();
		~NetworkManager();
	public:
		static void CreateInstance();
		static NetworkManager* GetInstance();
		static void DestroyInstance();

		User* GetUser() { return user; };

		void Recvprocess();
		bool Send();										// 패킷 전송
		bool Initialize();									// Wsa 초기화 // 이벤트 생성
		bool InitializeSocket();							// 소켓만들기
		bool Connect();										// Connect
		void Wait();										// Recv 대기
		HANDLE CreatRecvThread();
		bool MangerInitialize();
		void EndManager();
	};
}
#endif
