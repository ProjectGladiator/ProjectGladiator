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
		PGAMEDATA_LEAVE_PLAYER,					// 다른유저가 게임에서 나갔을때
		PGAMEDATA_MENU_CHARACTER_SELECT,		// 캐릭터 선택화면으로
		PGAMEDATA_MENU_LOGOUT					// 로그아웃일때(타이틀로)
	};
	// 공통 프로토콜
	enum PGLOBAL {
		CONFIRM = 0
	};

}
#endif