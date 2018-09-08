#include "User.h"
#include "LoginState.h"

User::User()
{
	ZeroMemory(id, IDSIZE);
	ZeroMemory(pw, IDSIZE);
	ZeroMemory(nickname, IDSIZE);

	money = 100000;
	
	state = nullptr;
	login = false;
}
// »ý¼ºÀÚ
User::User(SOCKET _sock, SOCKADDR_IN _addr): Packet(_sock, _addr)
{
	ZeroMemory(id, IDSIZE);
	ZeroMemory(pw, IDSIZE);
	ZeroMemory(nickname, IDSIZE);

	money = 100000;

	state = nullptr;
	login = false;
}

User::~User()
{
	delete loginstate;
}

UserState* User::getState()
{
	return state;
}

LoginState * User::getLoginState()
{
	return loginstate;
}

CharacterState * User::getCharacterState()
{
	return characterstate;
}

void User::SetState(UserState * _state)
{
	state = _state;
}

void User::setID(char * id)
{
	memcpy(this->id, id, sizeof(this->id));
}

const char * User::getID()
{
	return id;
}

void User::setPW(char * pw)
{
	memcpy(this->pw, pw, sizeof(this->pw));
}

const char * User::getPW()
{
	return pw;
}

void User::setNickName(char * nickname)
{
	memcpy(this->nickname, nickname, sizeof(this->nickname));
}

const char * User::getNickName()
{
	return nickname;
}

bool User::checkmoney(int money)
{
	return true;
}

void User::setmoney(int money)
{

}

void User::InitState()
{
	loginstate = new LoginState();
	state = loginstate;
}
