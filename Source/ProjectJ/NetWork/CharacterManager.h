#ifndef _CHARACTER_MANAGER_H_
#define _CHARACTER_MANAGER_H_

#include "Global.h"
#include "User.h"

class CharacterManager
{
private:
	static CharacterManager* Instance;

	CharacterManager();
	~CharacterManager();

	bool Character_Slot(char* _buf);						// ���Կ� ĳ���� �ִ��� Ȯ��
	bool Character_Recv_Slot(char* _buf);					// ���Կ� ĳ���Ͱ� ������ ĳ���͸� ��ȯ�Ѵ�
	void Character_Slot_Empty(bool _check);					// ���������� ����ִ�.
	bool Character_Recv_Create(char* _buf);					// ĳ���� ���� ���
	bool Character_Recv_Enter(char* _buf);					// ĳ���� ���� ���
	bool Character_Recv_Delete(char* _buf);					// ĳ���� ���� ���

public:
	static void CreateInstance();
	static CharacterManager* GetInstance();
	static void DestroyInstance();

	bool InitializeManager();
	void EndManager();

	void Character_Req_Slot();								// �������� ��û
	void Character_Req_Character(char* _nick, int _code);	// ĳ���� ������û(�г���,�����ڵ�)
	void Character_Req_Delete(int _index);					// ĳ���� ������û
	void Character_Req_Enter(int _index);					// ĳ���� ���� �� ���� ����

	RESULT CharacterInitRecvResult();						// 
	RESULT CharacterNewRecvResult();						// 
};

#endif