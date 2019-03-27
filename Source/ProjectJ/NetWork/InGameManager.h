#ifndef _INGAME_MANAGER_H_
#define _INGAME_MANAGER_H_

#include "Global.h"
#include "User.h"

class InGameManager
{
private:
	static InGameManager* Instance;

	InGameManager();
	~InGameManager();

	bool InGame_Recv_UserList(char* _buf);								// 현재 접속중인 유저리스트 받음
	void InGame_Recv_ConnectUserInfo(char* _buf);						// 접속한 다른 유저정보 받음
	bool InGame_Recv_MoveResult(char* _buf);							// 이동 결과
	void InGame_Recv_OtherUserMoveInfo(char* _buf, int _protocol);		// 다른 유저 이동 정보
	void InGame_Recv_OtherUserRotation(char* _buf);						// 다른 유저 회전 정보
	void InGame_Recv_OtherUserLeave(char* _buf);						// 다른 유저 나간정보
	void InGame_Recv_ChannelInfo(char* _buf);							// 채널 정보
	void InGame_Recv_CharacterSelect();									// 캐릭터 선택화면으로 받았을때
	void InGame_Recv_Logout();											// 로그아웃 받았을때
	void InGame_Recv_ChannelChange(char* _buf);							// 채널이동 결과

	void InGame_Recv_Invite(char* _buf);								// 파티 초대 받음
	void InGame_Recv_Invite_Result(char* _buf);							// 파티 초대 결과받음
	void InGame_Recv_Join_Result(char* _buf);							// 파티 참여 결과
	void InGame_Recv_Party_User_Info(char* _buf);						// 파티 유저 추가
public:
	static void CreateInstance();
	static InGameManager* GetInstance();
	static void DestroyInstance();

	bool MangerInitialize();
	void EndManager();

	void InGame_Req_UserList();										    // 현재 접속중인 유저리스트 요청
	void InGame_Req_Move(float _px, float _py, float _pz);			    // 이동요청 서버에 전송
	void InGame_Req_Rotation(float _rx, float _ry, float _rz);		    // 회전정보 서버에 전송
	void InGame_Req_ChannelInfo();									    // 채널 정보 요청
	void InGame_Req_ChannelChange(int _channelnum);					    // 채널 이동 요청
	void InGame_Req_Menu_Character();								    // 캐릭터 선택화면으로 요청
	void InGame_Req_Menu_Title();									    // 로그아웃 요청
	// 게임종료 요청 서버에 전송

	void InGame_Req_Party_Invite(char* _code);												// 파티 초대 요청
	void InGame_Req_Party_Invite_Result(bool _result, char* _code, int _partyroomnum);		// 파티 초대 응답
	RESULT InGameInitRecvResult(User* _user);			// 인게임 
};

#endif
