#ifndef _STORAGE_DATATYPE_H_
#define _STORAGE_DATATYPE_H_

struct CharacterSlot
{
	char name[255];
	int level;
	char nick[255];
	int charavercode;
	~CharacterSlot()
	{

	}
};

struct CharacterInfo
{

};

#endif