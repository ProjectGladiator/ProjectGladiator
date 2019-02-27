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
	char* character_name;			// ĳ���� �г���
	int character_code;				// �ڵ�
	int	character_str;				// ��
	int	character_dex;				// ��
	int	character_int;				// ��
	int	character_health;			// ü��
	int	character_mana;				// ����
	int	character_attackpoint;		// ���ݷ�
	int	character_defensepoint;		// ����
	int	character_speed;			// �̼�

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