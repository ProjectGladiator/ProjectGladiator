#include "InGameState.h"
#include "CharacterManager.h"
#include "InGameManager.h"

bool InGameState::Read(User * _user)
{
	InGameManager* ingamemanger = InGameManager::GetInstance();
	//CharacterManager* charactermanager = CharacterManager::GetInstance();
	int result;

	// 세부 스테이트에 따라 다른 동작
	switch (state)
	{
	case InGameState::INGAME_INIT_RECV:
		result = ingamemanger->GetInstance()->InGameInitRecvResult(_user);
		if (result == RT_INGAME_MOVE)
		{
			state = INGAME_INIT_RECV;
		}
		else if (result == RT_INGAME_OTHERPLAYER_INFO)
		{
			state = INGAME_INIT_RECV;
		}
		else if (result == RT_INGAME_OTHERPLAYER_LIST)
		{
			state = INGAME_INIT_RECV;
		}
		else if (result = RT_INGAME_CHANNEL_INFO)
		{
			state = INGAME_INIT_RECV;
		}
		else if (result == RT_INGAME_OTHERPLAYER_LEAVE)
		{
			state = INGAME_INIT_RECV;
		}
		
		break;
	}
	return true;
}

bool InGameState::Write(User * _user)
{
	return false;
}
