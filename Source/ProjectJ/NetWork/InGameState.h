#ifndef _INGAME_STATE_H_
#define _INGAME_STATE_H_

#include "UserState.h"

class InGameState : public UserState
{
private:
	enum CSTATE {
		// RECV 스테이트
		INGAME_INIT_RECV, 
		
	};

	CSTATE state;
public:

	InGameState() { state = INGAME_INIT_RECV; };
	~InGameState() {};

	virtual bool Read(User* _user);
	virtual bool Write(User* _user);
};

#endif
