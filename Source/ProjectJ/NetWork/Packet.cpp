#include "Packet.h"

// 생성자
Packet::Packet()
{
	sendSize = 0;
	sentSize = 0;
	recvSize = 0;
	recvedSize = 0;

	ZeroMemory(&sendBuf, sizeof(sendBuf));
	ZeroMemory(&recvBuf, sizeof(recvBuf));

}

// TCPClient 생성자에 인수 넣어줌
Packet::Packet(SOCKET _socket, SOCKADDR_IN _addr): TCPClient(_socket, _addr)
{
	sendSize = 0;
	sentSize = 0;
	recvSize = 0;
	recvedSize = 0;

}

// 데이터 전송
bool Packet::sendMsg()
{
	char* ptr = sendBuf;
	int retval = send(sock, ptr + sentSize, sendSize - sentSize, 0);
	if (retval == SOCKET_ERROR)
	{
		//LogManager::GetInstance()->SetTime();
		//LogManager::GetInstance()->LogWrite("Packet::sendMsg : ERROR : send() result = SOCKET_ERROR");
		ErrorManager::GetInstance()->err_display("TCPClient send()");
		return false;
	}
	else if (retval == 0)
	{
		return false;
	}
	else
	{
		// 보낸양
		sentSize += retval;
		return true;
	}
}

// 데이터 받기
bool Packet::recvMsg()
{
	if (recvSize == 0)				// 총 받을 양이 0 이라면
	{
		char* ptr = recvBuf;
		int retval = recv(sock, ptr + recvedSize, sizeof(int) - recvedSize, 0);
		if (retval == SOCKET_ERROR)
		{
			//LogManager::GetInstance()->LogWrite("Packet::recvMsg : ERROR : recv() result = SOCKET_ERROR");
			ErrorManager::GetInstance()->err_display("Packet first_recv()");
			return false;
		}
		else if (retval == 0)
		{
			return false;
		}
		else
		{
			// 받은양 더함
			recvedSize += retval;

			// 4바이트 다 받았으면
			if (recvedSize == 4)
			{
				// 총 받을양 세팅 -> 아래 if문으로 나머지 데이터 받음
				memcpy(&recvSize, ptr, sizeof(int));
				memset(ptr, 0, sizeof(recvBuf));
				recvedSize = 0;
			}
		}
	}
	if (recvSize > 0)				// 총 받을 양이 0 초과라면
	{
		char* ptr = recvBuf;
		int retval = recv(sock, ptr + recvedSize, recvSize - recvedSize, 0);
		if (retval == SOCKET_ERROR)
		{
			//LogManager::GetInstance()->SetTime();
			//LogManager::GetInstance()->LogWrite("Packet::recvMsg : ERROR : recv() result = SOCKET_ERROR");
			ErrorManager::GetInstance()->err_display("Packet second_recv()");
			return false;
		}
		else if (retval == 0)
		{
			return false;
		}
		else
		{
			recvedSize += retval;
		}
	}
	return true;
}

// Data 패킹
void Packet::pack(PROTOCOL p, void * data, int size)
{
	memset(sendBuf, 0, sizeof(sendBuf));

	char* ptr = sendBuf;
	sendSize = sizeof(PROTOCOL) + size;

	memcpy(ptr, &sendSize, sizeof(int));
	ptr += sizeof(int);

	memcpy(ptr, &p, sizeof(PROTOCOL));
	ptr += sizeof(PROTOCOL);

	memcpy(ptr, data, size);

	sendSize += sizeof(size);			// 보낼 사이즈
	sentSize = 0;						// 보낸 사이즈(초기화)

	// 암호화
	EncryptManager::GetInstance()->encoding(sendBuf + sizeof(PROTOCOL), sendSize);
}

void Packet::Quepack(PROTOCOL p, void * data, int size)
{
	SendQueue* temp = new SendQueue();

	memset(temp->sendBuf, 0, sizeof(temp->sendBuf));
	temp->sendSize = 0;

	char* ptr = temp->sendBuf;

	temp->sendSize = sizeof(PROTOCOL) + size;

	memcpy(ptr, &sendSize, sizeof(int));
	ptr += sizeof(int);

	memcpy(ptr, &p, sizeof(PROTOCOL));
	ptr += sizeof(PROTOCOL);

	memcpy(ptr, data, size);

	temp->sendSize += sizeof(size);		// 보낼 사이즈
	temp->sentSize = 0;						// 보낸 사이즈(초기화)
										// 암호화
	EncryptManager::GetInstance()->encoding(sendBuf + sizeof(PROTOCOL), sendSize);
	// 큐에 넣기
	sendQueue.push(temp);

}

bool Packet::isQueue()
{
	// sendQue.pop();

	if (sendQueue.size() == 0)
	{
		return true;
	}

	return false;
}

bool Packet::isQueueSendSuccess(int _sentbyte)
{
	sendQueue.front()->sentSize += _sentbyte;
	if (sendQueue.front()->sentSize == sendQueue.front()->sendSize)
	{
		sendQueue.front()->sentSize = 0;
		sendQueue.front()->sendSize = 0;

		sendQueue.pop();

		return true;
	}
	return false;
}

// Data 언패킹
void Packet::unPack(PROTOCOL * p, void * data)
{
	char* ptr = recvBuf;
	PROTOCOL protocol;

	EncryptManager::GetInstance()->decoding(recvBuf, recvSize);

	memcpy(&protocol, ptr, sizeof(PROTOCOL));
	ptr += sizeof(PROTOCOL);

	memcpy(data, ptr, recvSize - sizeof(PROTOCOL));
	*p = protocol;

	// InitializeBuffer
	memcpy(recvBuf, recvBuf + recvSize, recvedSize);

	recvSize = 0;						// 초기화
	recvedSize = 0;						// 초기화
}

void Packet::unProtocol(PROTOCOL * p)
{
	char* ptr = recvBuf;
	PROTOCOL protocol;

	EncryptManager::GetInstance()->decoding(recvBuf, recvSize);

	memcpy(&protocol, ptr, sizeof(PROTOCOL));
	*p = protocol;
}

// sendSize만큼 보냈는지
bool Packet::isSendSuccess()
{
	if (sendSize == sentSize)
		return true;
	else
		return false;
}

// recvSize만큼 받았는지
bool Packet::isRecvSuccess()
{
	if (recvSize == 0)
	{
		if (recvedSize == 0)
			return true;
		else
			return false;
	}
	else
	{
		if (recvSize == recvedSize)
			return true;
		else
			return false;
	}
}