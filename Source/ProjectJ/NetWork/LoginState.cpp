#include "LoginState.h"
#include "LoginManager.h"
#include "ChatManager.h"

bool LoginState::Read(User* _user)
{
	LoginManager* loginmanager = LoginManager::GetInstance();
	int result;

	// 세부 스테이트에 따라 다른 동작
	switch (state)
	{
	case LoginState::INIT_RECV:
		result = loginmanager->InitRecvResult();
		if (result == RT_LOGIN)
		{
			state = INIT_RECV;
			_user->SetState(_user->getCharacterState());
			// 로그인 성공
		}
		else if(result == RT_LOGINFAIL)
		{
			state = INIT_RECV;
		}
		else if (result == RT_JOINMENU)
		{
			state = JOIN_RECV;
		}
		break;
	case LoginState::JOIN_RECV:
		result = loginmanager->JoinRecvResult();
		if (result == RT_ID_OVERLAP_SUCCESS || result == RT_ID_OVERLAP_FAIL)
		{
			state = JOIN_RECV;
		}
		else if (result == RT_JOIN || result == RT_JOIN_MENU_EXIT)
		{
			state = INIT_RECV;
		}
		else if (result == RT_JOIN_FAIL)
		{
			state = JOIN_RECV;
		}
	}
	return true;
}

bool LoginState::Write(User* _user)
{
	switch (state)
	{
	case LoginState::INIT_SEND:
		state = REQUEST_RECV;
		break;
	case LoginState::REQUEST_RESULT_SEND:
		state = INIT_RECV;
		break;
	case LoginState::LOGIN_RESULT_SEND:
		state = LOGIN_RECV;
		break;
	case LoginState::LOGINFAIL_RESULT_SEND:
		state = INIT_RECV;
		break;
	//case LoginState::TENDER_SEND:
	//	state = LOGIN_RECV;		// 전 단계
	//	break;
	case LoginState::LEAVE_SEND:
		state = INIT_RECV;
		break;
	case LoginState::LOGOUT_SEND:
		state = INIT_RECV;	
		break;
	default:
		break;
	}
	return true;
}
