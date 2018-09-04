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
		PCHARACTERDATA_INFO = 0	// 이동 정보
	};
	// 인게임 프로토콜
	enum PGAMEDATA {
	
	};
	// 공통 프로토콜
	enum PGLOBAL { 
		CONFIRM = 0 
	};
}
#endif