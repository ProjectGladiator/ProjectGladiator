#ifndef PACKET_H
#define	PACKET_H

#include "TCPClient.h"
#include "EnryptManager.h"
#include "ErrorManager.h"
#include "LogManager.h"
#include <queue>

struct SendQueue
{
	char sendBuf[BUFSIZE];
	int sendSize;
	int sentSize;
};

class Packet : public TCPClient
{
private:
	queue<SendQueue*>sendQueue;

	char sendBuf[BUFSIZE];
	char recvBuf[BUFSIZE];
	int sendSize;				// �� ���� ��
	int sentSize;				// ���� ��
	int recvSize;				// �� ���� ��
	int recvedSize;				// ���� ��
	WSABUF sendwsabuf;
	WSABUF recvwsabuf;
public:
	Packet();
	Packet(SOCKET _socket, SOCKADDR_IN _addr);
	bool sendMsg();
	bool recvMsg();

	void Quepack(PROTOCOL p, void *data, int size);
	bool isQueue();
	bool isQueueSendSuccess(int _sentbyte);

	void pack(PROTOCOL p, void *data, int size);
	void unPack(PROTOCOL *p, void *data);
	void unProtocol(PROTOCOL *p);

	bool isSendSuccess();
	bool isRecvSuccess();

};

#endif
