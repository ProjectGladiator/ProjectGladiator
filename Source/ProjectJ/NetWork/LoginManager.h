#ifndef LOGIN_MANAGER_H
#define LOGIN_MANAGER_H

#include "User.h"

const struct
{
	enum
	{
		LOGIN = 1,
		JOIN = 2,
		EXIT
	};
} LogoutMenu = {};
const struct
{
	enum
	{
		TENDER = 1,
		LEAVE,
		LOGOUT,
		EXIT
	};
} LoginMenu = {};

struct UserInfo
{
	char id[IDSIZE];
	char pw[IDSIZE];
	char nickname[IDSIZE];
};

class LoginManager
{
private:
	static LoginManager* Instance;

	LoginManager();
	~LoginManager();
	const UserInfo* getUser(const char* id);

public:
	static void CreateInstance();
	static LoginManager* GetInstance();
	static void DestroyInstance();

	bool InitializeManager();
	void EndManager();

	void logoutMenuChoice();			// �α���/ȸ������ �Ŵ� ����
	void exitJoin();							// ȸ������ ��� ����
	void reqIdOverlapCheck(char* _id);			// ���̵� �ߺ�üũ ��û
	bool IdOverlapCheck(char* _buf);			// ���̵� �ߺ�üũ ���
	void reqJoin(char* _id, char* _pw);			// ȸ������ ��û
	void reqLogin(char* _id, char* _pw);		// �α��� ��û
	RESULT InitRecvResult();					// 
	RESULT JoinRecvResult();					// 
	bool Join(char* _buf);						// ȸ������ ���
	bool Login(char* _buf);						// �α��� ���
	bool isLogin();								// ���� �α��λ��� ��ȯ
	bool isJoin();								// ȸ������ ���
};

#endif
