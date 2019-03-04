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

	void logoutMenuChoice();			// 로그인/회원가입 매뉴 선택
	void exitJoin();							// 회원가입 취소 선택
	void reqIdOverlapCheck(char* _id);			// 아이디 중복체크 요청
	bool IdOverlapCheck(char* _buf);			// 아이디 중복체크 결과
	void reqJoin(char* _id, char* _pw);			// 회원가입 요청
	void reqLogin(char* _id, char* _pw);		// 로그인 요청
	RESULT InitRecvResult();					// 
	RESULT JoinRecvResult();					// 
	bool Join(char* _buf);						// 회원가입 결과
	bool Login(char* _buf);						// 로그인 결과
	bool isLogin();								// 현재 로그인상태 반환
	bool isJoin();								// 회원가입 결과
};

#endif
