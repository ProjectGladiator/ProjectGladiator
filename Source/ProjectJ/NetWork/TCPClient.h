#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include "Socket.h"

class TCPClient : public Socket
{
private:
protected:
public:
	TCPClient();
	TCPClient(SOCKET _socket, SOCKADDR_IN _addr);		
	bool createSocket();									// 家南 积己
	bool connect_client(const char *ip, int port);			// connect()
	void stop();											// closesocket()
};

#endif
