#include "InGameState.h"
#include "CharacterManager.h"

bool InGameState::Read(User * _user)
{
	CharacterManager* charactermanager = CharacterManager::GetInstance();
	int result;

	// ���� ������Ʈ�� ���� �ٸ� ����
	switch (state)
	{
	case InGameState::INGAME_INIT_RECV:
		/*result = charactermanager->
		break;*/
	}
	return true;
}

bool InGameState::Write(User * _user)
{
	return false;
}
