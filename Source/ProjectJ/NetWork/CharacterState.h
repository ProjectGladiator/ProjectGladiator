#ifndef _CHARACTER_STATE_H_
#define _CHARACTER_STATE_H_

#include"UserState.h"

class CharacterState :public UserState
{
private:
	enum CSTATE {
		// REC V 스테이트
		CHARACTER_INIT_RECV, CHARACTER_REQ_RECV,
	};

	CSTATE state;
public:

	CharacterState() { state = CHARACTER_INIT_RECV; };
	~CharacterState() {};

	virtual bool Read(User* _user);
	virtual bool Write(User* _user);
};

#endif
