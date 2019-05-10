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
	int sendSize;				// 총 보낼 양
	int sentSize;				// 보낸 양
	int recvSize;				// 총 받을 양
	int recvedSize;				// 받은 양
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
	void pack(UINT64 p, void *data, int size);
	void unPack(PROTOCOL *p, void *data);
	void unProtocol(PROTOCOL *p);

	// 비트연산 프로토콜 pack. _existingprotocol : 기존 프로토콜, _additionalprotocol : 추가할 프로토콜
	UINT64 BitPackProtocol(UINT64 _existingprotocol, UINT64 _additionalprotocol);
	// 비트연산 프로토콜 pack. 기존프로토콜, 큰틀프로토콜, 중간틀프로토콜, 세부프로토콜
	UINT64 BitPackProtocol(UINT64 _existingprotocol, UINT64 _first_additionalprotocol, UINT64 _second_additionalprotocol, UINT64 _third_additionalprotocol);

	// 비트 연산 프로토콜 unpack
	void BitunPack(UINT64 &_p, void* _data);

	bool isSendSuccess();
	bool isRecvSuccess();

};

#endif
