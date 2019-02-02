#include "Socket.h"
#include "ErrorManager.h"
#include "LogManager.h"

Socket::Socket()
{
	include_wset = false;
	include_rset = true;
}

Socket::Socket(SOCKET _socket, SOCKADDR_IN _addr)
{
	ZeroMemory(&sock, sizeof(sock));
	ZeroMemory(&this->addr, sizeof(this->addr));
	sock = _socket;
	addr = _addr;

	include_wset = false;
	include_rset = true;
}

SOCKET Socket::getSocket()
{
	return this->sock;
}

void Socket::setBlocking(bool set)
{
	int retval;
	u_long on;

	if (set)
	{
		on = 0;
		retval = ioctlsocket(sock, FIONBIO, &on);
		if (retval == SOCKET_ERROR)
		{
			//LogManager::GetInstance()->SetTime();
			//LogManager::GetInstance()->LogWrite("Socket::setBlocking : ERROR : ioctlsocket() result = SOCKET_ERROR");
			ErrorManager::GetInstance()->err_display("TCPServer ioctlsocket()");
		}
	}
	else
	{
		on = 1;
		retval = ioctlsocket(sock, FIONBIO, &on);
		if (retval == SOCKET_ERROR)
		{
			//LogManager::GetInstance()->SetTime();
			//LogManager::GetInstance()->LogWrite("Socket::setBlocking : ERROR : ioctlsocket() result = SOCKET_ERROR");
			ErrorManager::GetInstance()->err_display("TCPServer ioctlsocket()");
		}
	}
}
