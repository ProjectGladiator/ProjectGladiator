#include "CharacterState.h"
#include "CharacterManager.h"

bool CharacterState::Read(User * _user)
{
	CharacterManager* charactermanager = CharacterManager::GetInstance();
	int result;

	// ���� ������Ʈ�� ���� �ٸ� ����
	switch (state)
	{
	case CharacterState::CHARACTER_INIT_RECV:
		result = charactermanager->CharacterInirRecvResult();
		if (result == RT_CHARACTER_SLOTRESULT)
		{
			state = CHARACTER_INIT_RECV;
		}
		else if(result == RT_CHARACTER_ENTERGAME_SUCCESS)
		{
			// ĳ���� ����
		}
		else if (result == RT_CHARACTER_ENTERGAME_FAIL)
		{
			state = CHARACTER_INIT_RECV;
		}
		else if(result == RT_CHARACTER_DELETE)
		{
			state = CHARACTER_INIT_RECV;
		}
		else if (result == RT_CHARACTER_ENTERCREATE)
		{
			state = CHARACTER_REQ_RECV;
		}
	case CharacterState::CHARACTER_REQ_RECV:
		result = charactermanager->CharacterNewRecvResult();
		if (result == RT_CHARACTER_CREATE_SUCCESS)
		{
			state = CHARACTER_INIT_RECV;
		}
		else if (result == RT_CHARACTER_CREATE_FAIL)
		{
			state = CHARACTER_REQ_RECV;
		}
		else if (result == RT_CHARACTER_EXIT)
		{
			state = CHARACTER_INIT_RECV;
		}
	}
	return true;
}

bool CharacterState::Write(User * _user)
{
	return false;
}
