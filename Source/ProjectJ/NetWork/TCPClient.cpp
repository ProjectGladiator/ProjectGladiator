#include "TCPClient.h"
#include "ErrorManager.h"
#include "LogManager.h"

// 생성자
TCPClient::TCPClient()
{
}

// 생성자
TCPClient::TCPClient(SOCKET _socket, SOCKADDR_IN _addr) : Socket(_socket, _addr)
{
}

// TCP소켓 생성(클라이언트용)
bool TCPClient::createSocket()
{
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		//LogManager::GetInstance()->SetTime();
		//LogManager::GetInstance()->LogWrite("TCPClient::createSocket : ERROR : socket() result = INVALID_SOCKET");
		ErrorManager::GetInstance()->err_display("createSocket socket()");
		return false;
	}

	return true;
}

// connect 
bool TCPClient::connect_client(const char * ip, int port)
{
	SOCKADDR_IN serveraddr;							// 소켓 주소 구조체 준비. 연결요청할 서버의 내용이 들어간다.
	ZeroMemory(&serveraddr, sizeof(serveraddr));

	serveraddr.sin_family = AF_INET;				//IP4타입
	serveraddr.sin_addr.s_addr = inet_addr(ip);	    //IP주소
	serveraddr.sin_port = htons(port);			    //포트번호

	int retval = connect(sock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR)						// 예외 처리
	{
		//LogManager::GetInstance()->SetTime();
		//LogManager::GetInstance()->LogWrite("TCPClient::connect_client : ERROR : connect() result = SOCKET_ERROR");
		ErrorManager::GetInstance()->err_display("TCPClient connect()");
		return false;
	}
	else
	{
		return true;
	}
}

// 소켓 정리
void TCPClient::stop()
{
	printf("[TCP 서버] 클라이언트 종료: IP 주소=%s, 포트 번호=%d\n",
		inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
	closesocket(sock);
}