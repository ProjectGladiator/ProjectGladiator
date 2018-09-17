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
public:
	static void CreateInstance();
	static CharacterManager* GetInstance();
	static void DestroyInstance();

	bool InitializeManager();
	void EndManager();

	void Character_Req_Slot();								// ���Կ�û
	void Character_Req_New_Character();						// ĳ���� ���� �޴�
	void Character_Req_Character(char* _nick, int _code);	// ĳ���� ������û(�г���,�����ڵ�)
	void Character_Choice(int _select);						// ĳ���� ���� 
	void Character_Exit();									// ĳ���� ���� ���

	bool Character_Slot(char* _buf);						// ���Կ� ĳ���� �ִ��� Ȯ��
	bool Character_Recv_Slot(char* _buf);					// ���Կ� ĳ���Ͱ� ������ ĳ���͸� ��ȯ�Ѵ�
	bool Character_Recv_Create(char* _buf);					// ĳ���� ���� ���
	bool Character_Recv_Enter(char* _buf);					// ĳ���� ���� ���

	RESULT CharacterInirRecvResult();						// 
	RESULT CharacterNewRecvResult();						// 
};

#endif