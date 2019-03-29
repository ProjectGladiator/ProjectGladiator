#ifndef _DATA_PROTOCOL_H_
#define _DATA_PROTOCOL_H_

namespace DataProtocol {
	// 로그인 프로토콜
	enum PLOGINDATA {
		PLOGIN_LOGIN_RESULT = 0, 	   // 로그인 결과
		PLOGIN_IDOVERLAP_RESULT,	   // 아이디중복체크 결과
		PLOGIN_JOIN_RESULT			   // 회원가입 결과
	};
	// 캐릭터 프로토콜
	enum PCHARACTERDATA {
		PCHARACTERDATA_SLOT_INFO = 100,			// 슬롯 결과
		PCHARACTERDATA_CREATE_RESULT,			// 캐릭터 생성 결과
		PCHARACTERDATA_DELETE_RESULT,			// 캐릭터 삭제 결과
		PCHARACTERDATA_ENTER_RESULT,			// 접속 결과
		PCHARACTERDATA_ENTER_INFO				// 접속 정보
	};
	// 인게임 프로토콜
	enum PGAMEDATA {
		PGAMEDATA_PLAYER_MOVE_INFO = 200,		// 현재유저 이동 정보
		PGAMEDATA_PLAYER_OTHERMOVEINFO,			// 다른유저 이동 정보
		PGAMEDATA_PLAYER_OTHERMOVEORDER,		// 다른유저 이동 명령
		PGAMEDATA_PLAYER_OTHERROTATION,			// 다른유저 회전
		PGAMEDATA_USERLIST_USER,				// 유저 정보
		PGAMEDATA_USERLIST_EMPTY,
		PGAMEDATA_USERLIST_COUNT,				// 유저리스트 카운트
		PGAMEDATA_CHANNEL_INFO,					// 채널 정보
		PGAMEDATA_CHANNEL_REQ_CHANGE,			// 채널 이동 결과
		PGAMEDATA_LEAVE_PLAYER,					// 다른유저가 게임에서 나갔을때
		PGAMEDATA_MENU_CHARACTER_SELECT,		// 캐릭터 선택화면으로
		PGAMEDATA_MENU_LOGOUT,					// 로그아웃일때(타이틀로)
		PGAMEDATA_PARTY_INVITE,					// 파티 초대
		PGAMEDATA_PARTY_INVITE_RESULT,			// 파티 초대 결과
		PGAMEDATA_PARTY_JOIN_RESULT,			// 파티 참여 결과
		PGAMEDATA_PARTY_INFO,					// 파티 정보(파티방번호,파티원)
		PGAMEDATA_PARTY_USER_INFO,				// 파티원 정보(캐릭터정보)
		PGAMEDATA_PARTY_KICK,					// 파티 강퇴 받음 - (프로토콜만)
		PGAMEDATA_PARTY_USER_KICK_INFO,			// 파티 강퇴된 유저 정보 받음 - (캐릭터코드)
		PGAMEDATA_PARTY_USER_KICK_RESULT,		// 파티 강퇴 결과 받음 - (결과,(성공이면)유저코드)
		PGAMEDATA_PARTY_LEAVE_INFO,				// 파티 탈퇴한 유저 정보 받음 - (캐릭터코드)
		PGAMEDATA_PARTY_LEAVE_RESULT,			// 파티 탈퇴 결과 받음 - (성공실패)
		PGAMEDATA_PARTY_PARTYROOM_REMOVE,		// 파티 터짐 - (프로토콜만)
		PGAMEDATA_PARTY_LEADER_INFO,			// 새로운 파티 리더 정보 - (코드)
		PGAMEDATA_PARTY_LEADER_DELEGATE_RESULT,	// 파티 리더 위임 결과 - (결과,(성공이면)코드)
	};
	// 공통 프로토콜
	enum PGLOBAL {
		CONFIRM = 0
	};

}
#endif