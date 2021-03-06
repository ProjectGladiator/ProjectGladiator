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

	bool Character_Slot(char* _buf);						// 슬롯에 캐릭터 있는지 확인
	bool Character_Recv_Slot(char* _buf);					// 슬롯에 캐릭터가 있으면 캐릭터를 반환한다
	void Character_Slot_Empty(bool _check);					// 슬롯정보가 비어있다.
	bool Character_Recv_Create(char* _buf);					// 캐릭터 생성 결과
	bool Character_Recv_Enter(char* _buf);					// 캐릭터 접속 결과
	bool Character_Recv_Delete(char* _buf);					// 캐릭터 삭제 결과

public:
	static void CreateInstance();
	static CharacterManager* GetInstance();
	static void DestroyInstance();

	bool InitializeManager();
	void EndManager();

	void Character_Req_Slot();								// 슬롯정보 요청
	void Character_Req_Character(char* _nick, int _code);	// 캐릭터 생성요청(닉네임,직업코드)
	void Character_Req_Delete(int _index);					// 캐릭터 삭제요청
	void Character_Req_Enter(int _index);					// 캐릭터 선택 후 게임 시작

	RESULT CharacterInitRecvResult();						// 
	RESULT CharacterNewRecvResult();						// 
};

#endif