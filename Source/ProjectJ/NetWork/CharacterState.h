#ifndef _CHARACTER_STATE_H_
#define _CHARACTER_STATE_H_

#include"UserState.h"

class CharacterState :public UserState
{
private:
	enum CSTATE {
		// REC V 스테이트
		CHARACTER_MENU_RECV, CHARACTER_REQ_RECV,
		// SEND 스테이트
		CHARACTER_SLOT_RESULT_SEND, CHARACTER_CREATE_MENU_SEND, CHARACTER_ENTER_SEND, CHARACTER_REQ_OVLAP_NICK_SEND, CHARACTER_REQ_CHARACTER_SEND, CHARACTER_EXIT_SEND
	};

	CSTATE state;
public:

	CharacterState() { state = CHARACTER_MENU_RECV; };
	~CharacterState() {};

	virtual bool Read(User* _user);
	virtual bool Write(User* _user);
};

#endif
