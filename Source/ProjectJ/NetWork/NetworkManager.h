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
		bool Send();										// ��Ŷ ����
		bool Initialize();									// Wsa �ʱ�ȭ // �̺�Ʈ ����
		bool InitializeSocket();							// ���ϸ����
		bool Connect();										// Connect
		void Wait();										// Recv ���
		HANDLE CreatRecvThread();
		bool MangerInitialize();
		void EndManager();
	};
}
#endif
