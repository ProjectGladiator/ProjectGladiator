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

	void Character_Req_Slot();								// 슬롯요청
	void Character_Req_New_Character();						// 캐릭터 생성 메뉴
	void Character_Req_Character(char* _nick, int _code);	// 캐릭터 생성요청(닉네임,직업코드)
	void Character_Choice(int _select);						// 캐릭터 선택 
	void Character_Exit();									// 캐릭터 생성 취소

	bool Character_Slot(char* _buf);						// 슬롯에 캐릭터 있는지 확인
	bool Character_Recv_Slot(char* _buf);					// 슬롯에 캐릭터가 있으면 캐릭터를 반환한다
	bool Character_Recv_Create(char* _buf);					// 캐릭터 생성 결과
	bool Character_Recv_Enter(char* _buf);					// 캐릭터 접속 결과

	RESULT CharacterInirRecvResult();						// 
	RESULT CharacterNewRecvResult();						// 
};

#endif