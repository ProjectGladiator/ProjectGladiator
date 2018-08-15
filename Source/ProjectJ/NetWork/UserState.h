#ifndef _USER_STATE_H_
#define _USER_STATE_H_

#include "Global.h"

class User;

class UserState
{
private:
public:
	UserState() {};
	~UserState() {};

	virtual bool Read(User* _user) = 0;
	virtual bool Write(User* _user) = 0;
};

#endif
