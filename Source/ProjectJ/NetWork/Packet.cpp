#include "Packet.h"

// ������
Packet::Packet()
{
	sendSize = 0;
	sentSize = 0;
	recvSize = 0;
	recvedSize = 0;

	ZeroMemory(&sendBuf, sizeof(sendBuf));
	ZeroMemory(&recvBuf, sizeof(recvBuf));

}

// TCPClient �����ڿ� �μ� �־���
Packet::Packet(SOCKET _socket, SOCKADDR_IN _addr): TCPClient(_socket, _addr)
{
	sendSize = 0;
	sentSize = 0;
	recvSize = 0;
	recvedSize = 0;

}

// ������ ����
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
		// ������
		sentSize += retval;
		return true;
	}
}

// ������ �ޱ�
bool Packet::recvMsg()
{
	if (recvSize == 0)				// �� ���� ���� 0 �̶��
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
			// ������ ����
			recvedSize += retval;

			// 4����Ʈ �� �޾�����
			if (recvedSize == 4)
			{
				// �� ������ ���� -> �Ʒ� if������ ������ ������ ����
				memcpy(&recvSize, ptr, sizeof(int));
				memset(ptr, 0, sizeof(recvBuf));
				recvedSize = 0;
			}
		}
	}
	if (recvSize > 0)				// �� ���� ���� 0 �ʰ����
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

// Data ��ŷ
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

	sendSize += sizeof(size);			// ���� ������
	sentSize = 0;						// ���� ������(�ʱ�ȭ)

	// ��ȣȭ
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

	temp->sendSize += sizeof(size);		// ���� ������
	temp->sentSize = 0;						// ���� ������(�ʱ�ȭ)
										// ��ȣȭ
	EncryptManager::GetInstance()->encoding(sendBuf + sizeof(PROTOCOL), sendSize);
	// ť�� �ֱ�
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

// Data ����ŷ
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

	recvSize = 0;						// �ʱ�ȭ
	recvedSize = 0;						// �ʱ�ȭ
}

void Packet::unProtocol(PROTOCOL * p)
{
	char* ptr = recvBuf;
	PROTOCOL protocol;

	EncryptManager::GetInstance()->decoding(recvBuf, recvSize);

	memcpy(&protocol, ptr, sizeof(PROTOCOL));
	*p = protocol;
}

// sendSize��ŭ ���´���
bool Packet::isSendSuccess()
{
	if (sendSize == sentSize)
		return true;
	else
		return false;
}

// recvSize��ŭ �޾Ҵ���
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