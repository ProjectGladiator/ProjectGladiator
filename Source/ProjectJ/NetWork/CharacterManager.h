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
	bool Character_Slot(char* _buf);						// ���Կ� ĳ���� �ִ��� Ȯ��
	void Character_Recv_Slot(char* _buf);					// ���Կ� ĳ���Ͱ� ������ ĳ���͸� ��ȯ�Ѵ�.
															// ĳ���� ���� �޴�
	void Character_Req_Character(char* _nick,int _code);	// ĳ���� ������û(�г���,�����ڵ�)
	//void CharacterMenuChoice(int _select);				// ĳ���� ���� 
	void Character_Exit();									// ĳ���� ���� ���


};

#endif