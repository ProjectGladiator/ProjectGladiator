#ifndef _STORAGE_DATATYPE_H_
#define _STORAGE_DATATYPE_H_

struct CharacterSlot
{
	char name[255];
	int level;
	char nick[NICKNAMESIZE];
	int charavercode;
	~CharacterSlot()
	{

	}
};

struct CharacterInfo
{
	char code[CHARACTERCODESIZE];
	int job_code;
	char nick[NICKNAMESIZE];
	float xyz[3];
	float rot_xyz[3];
};

struct OtherCharacterInfo
{
	char code[CHARACTERCODESIZE];
	float xyz[3];
};

class Character
{
private:
public:
	char* character_name;			// 캐릭터 닉네임
	int character_code;				// 코드
	int	character_str;				// 힘
	int	character_dex;				// 민
	int	character_int;				// 지
	int	character_health;			// 체력
	int	character_mana;				// 마나
	int	character_attackpoint;		// 공격력
	int	character_defensepoint;		// 방어력
	int	character_speed;			// 이속

	void SetCharacter_Name(char* _character_name)
	{
		int len = strlen(_character_name);
		char* name = new char[len + 1];
		memset(name, 0, len + 1);
		strcpy_s(name, len + 1, _character_name);
		character_name = name;
	}

	~Character() { delete[]character_name; }
};

#endif