#include "CharacterState.h"
#include "CharacterManager.h"

bool CharacterState::Read(User * _user)
{
	CharacterManager* charactermanager = CharacterManager::GetInstance();
	int result;

	// 세부 스테이트에 따라 다른 동작
	switch (state)
	{
	case CharacterState::CHARACTER_INIT_RECV:
		result = charactermanager->CharacterInitRecvResult();
		if (result == RT_CHARACTER_SLOTRESULT)
		{
			state = CHARACTER_INIT_RECV;
		}
		else if(result == RT_CHARACTER_ENTERGAME_SUCCESS)
		{
			state = CHARACTER_INIT_RECV;
			_user->SetState(_user->getIngameState());
		}
		else if (result == RT_CHARACTER_ENTERGAME_FAIL)
		{
			state = CHARACTER_INIT_RECV;
		}
		else if(result == RT_CHARACTER_DELETE)
		{
			state = CHARACTER_INIT_RECV;
		}
		else if (result == RT_CHARACTER_CREATE_SUCCESS)
		{
			state = CHARACTER_INIT_RECV;
		}
		else if (result == RT_CHARACTER_CREATE_FAIL)
		{
			state = CHARACTER_INIT_RECV;
		}
		break;
	}
	return true;
}

bool CharacterState::Write(User * _user)
{
	return false;
}
