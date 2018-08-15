#ifndef SOCKET_H
#define SOCKET_H

#include "Global.h"

class Socket
{
protected:
	SOCKET sock;
	SOCKADDR_IN addr;


public:
	bool include_wset;
	bool include_rset;

	Socket();
	Socket(SOCKET _socket, SOCKADDR_IN _addr);

	SOCKET getSocket();
	void setBlocking(bool set);
	virtual void stop() = 0;
};

#endif
