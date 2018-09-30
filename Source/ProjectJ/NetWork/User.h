#ifndef USER_H
#define USER_H

#include "Packet.h"
#include "UserState.h"
#include "LoginState.h"
#include "CharacterState.h"
#include "InGameState.h"

class User : public Packet
{
private:
	char id[IDSIZE];
	char pw[IDSIZE];
	char nickname[IDSIZE];
	int money;
	bool login;
	UserState* state;

	LoginState* loginstate;
	CharacterState* characterstate;
	InGameState* ingamestate;

public:
	User();
	User(SOCKET _sock, SOCKADDR_IN _addr);
	~User();
	UserState* getState() { return state; }
	LoginState* getLoginState() { return loginstate; }
	CharacterState* getCharacterState() { return characterstate; }
	InGameState* getIngameState() { return ingamestate; }

	void SetState(UserState* _state);
	void setID(char *id);
	const char* getID();
	void setPW(char *pw);
	const char* getPW();
	void setNickName(char *nickname);
	const char* getNickName();
	bool checkmoney(int money);
	void setmoney(int money);
	void setLogin() { login = true; }
	void setLogout() { login = false; }
	bool isLogin() { return login ? true : false; }

	void InitState();
};

#endif
