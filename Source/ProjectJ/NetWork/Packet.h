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
	void pack(UINT64 p, void *data, int size);
	void unPack(PROTOCOL *p, void *data);
	void unProtocol(PROTOCOL *p);

	// ��Ʈ���� �������� pack. _existingprotocol : ���� ��������, _additionalprotocol : �߰��� ��������
	UINT64 BitPackProtocol(UINT64 _existingprotocol, UINT64 _additionalprotocol);
	// ��Ʈ���� �������� pack. ������������, ūƲ��������, �߰�Ʋ��������, ������������
	UINT64 BitPackProtocol(UINT64 _existingprotocol, UINT64 _first_additionalprotocol, UINT64 _second_additionalprotocol, UINT64 _third_additionalprotocol);

	// ��Ʈ ���� �������� unpack
	void BitunPack(UINT64 &_p, void* _data);

	bool isSendSuccess();
	bool isRecvSuccess();

};

#endif
