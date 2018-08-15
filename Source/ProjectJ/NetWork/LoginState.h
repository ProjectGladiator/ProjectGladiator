#ifndef _LOGIN_STATE_H_
#define _LOGIN_STATE_H_

#include"UserState.h"


class LoginState :public UserState
{
private:
	enum LSTATE {
		// RECV 스테이트
		INIT_RECV, REQUEST_RECV, LOGIN_RECV,JOIN_RECV,
		// SEND 스테이트
		INIT_SEND, REQUEST_RESULT_SEND, LOGIN_RESULT_SEND, LOGINFAIL_RESULT_SEND, LOGOUT_SEND, LEAVE_SEND
	};

	LSTATE state;
public:

	LoginState() { state = INIT_RECV; };
	~LoginState() {};

	virtual bool Read(User* _user);
	virtual bool Write(User* _user);
};

#endif
