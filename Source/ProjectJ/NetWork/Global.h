#ifndef GLOBAL_H
#define GLOBAL_H

#pragma comment(lib, "ws2_32")
#include <WinSock2.h>
#include <stdio.h>

// 패킷 : [전체크기 4Byte][프로토콜 4Byte][데이터]
// 문자열 데이터 [strlen(문자열)+1 4Byte][문자열]
enum PROTOCOL {
	EXIT = -1,
	CLIENT_LOGOUT_MENU_CHOICE = 0,			// 로그아웃 메뉴 선택			[프로토콜][int]
	CLIENT_LOGIN_MENU_CHOICE,				// 로그인 메뉴 선택				[프로토콜][int]
	CLIENT_REQ_EXIT_JOIN,					// 회원가입 취소 선택			[프로토콜]
	CLIENT_REQ_ID_OVERLAP_CHECK,			// 회원가입 ID중복체크 요청		[프로토콜][int][char *]
	CLIENT_REQ_JOIN,						// 회원가입 요청				[프로토콜][int][char *]
	CLIENT_REQ_LOGIN,						// 로그인 요청					[프로토콜][int][char *][int][char *]

	SERVER_JOIN,							// 회원가입 메뉴 선택			[프로토콜]
	SERVER_LOGIN,							// 로그인 메뉴 선택				[프로토콜]
	SERVER_EXIT_JOIN,						// 회원가입 취소 결과			[프로토콜]
	SERVER_ID_OVERLAP_CHECK,				// ID중복 결과 보냄				[프로토콜][bool]
	SERVER_JOIN_SUCCESS,					// 회원가입 결과 메세지			[프로토콜]
	SERVER_LOGIN_SUCCESS,					// 로그인 성공 여부				[프로토콜][bool]

	CLIENT_REQ_CHARACTER_SLOT,				// 클라 케릭터 슬롯 요청		[프로토콜]
	CLIENT_CHARACTER_ENTER,					// 클라 케릭터 접속				[프로토콜][int]
	CLIENT_CHARACTER_DELETE,				// 클라 케릭터 삭제				[프로토콜][int]
	CLIENT_NEW_CHARACTER_MENU,				// 클라 케릭터생성 메뉴			[프로토콜]
	CLIENT_REQ_NICK_OVERLAP_CHECK,			// 클라 닉네임 중복				[프로토콜][int][char*]
	CLIENT_REQ_CHARACTER,					// 클라 케릭터 생성 요청		[프로토콜][int][char*][int] : [nicknamesize][nickname][charactercode]
	CLIENT_CHARACTER_EXIT,					// 클라 케릭터 생성 취소		[프로토콜]
	CLIENT_LOGOUT,							// 클라 로그아웃				[프로토콜]
	CLIENT_LEAVE,							// 클라 회원탈퇴				[프로토콜]

	SERVER_CHARACTER_SLOT_RESULT,			// 서버 케릭터 슬롯 전송		[프로토콜]...
	SERVER_CHARACTER_ENTER_RESULT,			// 서버 케릭터 접속결과			[프로토콜][bool]
	SERVER_CHARACTER_ENTER_INFO,			// 서버 케릭터 접속 정보		[DataProtocol용]
	SERVER_CHARACTER_DELETE_RESULT,			// 서버 케릭터 삭제 결과		[프로토콜][bool]
	SERVER_CHARACTER_MENU,					// 서버 케릭터 메뉴 결과		[프로토콜]
	//SERVER_NICK_OVERLAP_CHECK,			// 서버 닉네임 중복 결과		[프로토콜][bool]
	SERVER_CHARACTER_RESULT,				// 서버 케릭터 생성 확인 결과	[프로토콜][bool]
	SERVER_CHARACTER_EXIT_RESULT,			// 서버 케릭터 생성 취소 결과	[프로토콜[
	SERVER_LEAVE,							// 서버 회원탈퇴 결과			[프로토콜][bool]
	SERVER_LOGOUT,							// 서버 로그아웃 결과			[프로토콜][bool]

	// 입찰 프로토콜
	SERVER_TENDER,							// 입찰 선택
	CLIENT_TENDER_MENU_CHOICE,				// 입찰메뉴 선택 확인
	SERVER_TENDER_CREATE,					// 입찰물품 생성 선택 
	SERVER_TENDER_PARTICIPATE,				// 입찰 참여 선택
	SERVER_BACK,							// 뒤로가기
	CLIENT_REQ_TENDER_CREATE,				// 입찰물품 생성 요청	 [프로토콜][char* 물품이름][int 가격][int 입찰자수]
	SERVER_TENDER_CREATE_RESULT,			// 입찰물품 생성 요청 결과
	CLIENT_REQ_TENDER_LIST,					// 입찰 리스트 요청
	SERVER_TENDER_LIST_RESULT,				// 입찰 리스트 요청 결과
	CLIENT_REQ_TENDER_PARTICIPATE,			// 입찰 요청
	SERVER_TENDER_PARTICIPATE_RESULT,		// 입찰 요청 결과
	SERVER_TENDER_END_RESULT,				// 입찰 종료 결과 [프로토콜][char* 메세지]

	// 인게임 프로토콜
	CLIENT_INGAME_OTHERPLAYERLIST,			// 클라 다른플레이어 리스트 요청	[프로토콜][]
	CLIENT_INGAME_MOVE_START,				// 클라 이동 시작					[프로토콜]
	CLIENT_INGAME_MOVE_REPORT,				// 클라 이동중 보고					[프로토콜]
	CLIENT_INGAME_MOVE_END,					// 클라 이동 끝					[프로토콜]
	SEVER_INGAME_MOVE_ORDER,				// 서버 이동 명령				[프로토콜][FLOAT][FLOAT][FLOAT][FLOAT : 시간]
	SEVER_INGAME_MOVE_RESULT,				// 서버 이동 결과				[프로토콜][FLOAT][FLOAT][FLOAT][FLOAT : 시간]
	SEVER_INGAME_MOVE_OTHERPLAYERINFO,			// 다른플레이어 정보			[프로토콜][FLOAT][FLOAT][FLOAT][FLOAT : 시간][닉네임사이즈][닉네임]
	SEVER_INGAME_OTHERPLAYERLIST_RESULT,	// 플레이어 리스트 			[프로토콜][INT:카운트][INT:닉네임사이즈][CHAR:닉네임][VECTOR:위치]...

	// 채팅 프로토콜
	CLIENT_REQ_CHAT_LIST,					// 현재 로그인한 회원리스트 요청 			 프로토콜만
	SERVER_CHAT_LIST_RESULT,				// 현재 로그인한 회원리스트 요청 결과 		[인원 수] [닉네임 사이즈] [닉네임]...
	CLIENT_REQ_CHAT_START,					// 채팅 요청 								[인원 수] [닉네임 사이즈] [닉네임]
	SERVER_CHAT_START_RESULT,				// 채팅 요청 결과 							[BOOL값]  ?  [방 번호] : [에러 코드] [메세지 사이즈] [메세지]
	SERVER_CHAT_MSG,						// 채팅 메세지 : 서버 --> 클라				[방 번호] [메세지 사이즈] [메세지]
	CLIENT_CHAT_MSG,						// 채팅 메세지 : 클라 --> 서버				[방 번호] [메세지 사이즈] [메세지]
	SERVER_CHAT_ENTER,						// 현재 채팅방 입장 : 서버 --> 클라			[방 번호] [닉네임 사이즈] [닉네임]
	CLIENT_CHAT_EXIT,						// 현재 채팅방 퇴장 : 클라 --> 서버			[방 번호] [닉네임 사이즈] [닉네임]
	SERVER_CHAT_EXIT						// 채팅방 퇴장 : 서버 --> 클라				[방 번호]

};

enum STATE {
	INIT_STATE, LOGIN_STATE,TENDER_STATE,JOIN_STATE,EXIT_STATE,
	LOG_IN,
	LOG_OUT,
	TENDER_INTRO,

	CLOSE = -1,
	RECV_LOGOUT_MENU_CHOICE = 0,
	RECV_LOGIN_MENU_CHOICE,
	SEND_JOIN,
	RECV_REQ_ID_OVERLAP_CHECK,
	SEND_ID_OVERLAP_CHECK,
	RECV_REQ_JOIN,
	SEND_JOIN_SUCCESS,
	SEND_LOGIN,
	RECV_REQ_LOGIN,
	SEND_LOGIN_SUCCESS,
	SEND_LOGIN_FAILED,
	SEND_LEAVE,
	SEND_LOGOUT,

	SEND_TENDER, //입찰 선택
	RECV_TENDER_MENU_CHOICE, //입찰메뉴 선택 확인
	SEND_TENDER_CREATE, //입찰물품 생성 선택 
	SEND_TENDER_PARTICIPATE, //입찰 참여 선택
	SEND_BACK, //뒤로가기
	RECV_REQ_TENDER_CREATE,	 //입찰물품 생성 요청	 [프로토콜][char* 물품이름][int 가격][int 입찰자수]
	SEND_TENDER_CREATE_RESULT, //입찰물품 생성 요청 결과
	RECV_REQ_TENDER_LIST, //입찰 리스트 요청
	SEND_TENDER_LIST_RESULT, //입찰 리스트 요청 결과
	RECV_REQ_TENDER_PARTICIPATE, //입찰 요청
	SEND_TENDER_PARTICIPATE_RESULT, //입찰 요청 결과
	SEND_TENDER_END_RESULT //입찰 종료 결과 [프로토콜][char* 메세지]
};

enum RESULT { 
	// 로그인매니저 결과
	RT_LOGINMENU = 100, 		   // 로그인 매뉴
	RT_JOINMENU, 				   // 회원가입 매뉴
	RT_MEMBER_LEAVE, 			   // 
	RT_LOGOUT, 					   // 
	RT_USER_DISCONNECT,			   // 
	RT_ID_OVERLAP_SUCCESS, 		   // ID 중복 체크 결과 중복없을때
	RT_ID_OVERLAP_FAIL, 		   // ID 중복 체크 결과 중복있을때
	RT_JOIN_MENU_EXIT,			   // 회원가입 취소 일때
	RT_JOIN, 					   // 회원가입 성공일때
	RT_JOIN_FAIL, 				   // 회원가입 실패일때
	RT_LOGIN, 					   // 로그인 성공일때
	RT_LOGINFAIL,				   // 로그인 실패일때

	// 캐릭터매니저 결과
	RT_CHARACTER_SLOTRESULT = 200,		// 캐릭터 슬롯결과
	RT_CHARACTER_ENTERGAME_SUCCESS,		// 게임 접속 성공
	RT_CHARACTER_ENTERGAME_FAIL,		// 게임 접속 실패
	RT_CHARACTER_DELETE,				// 캐릭터 삭제
	RT_CHARACTER_ENTERCREATE, 			// 캐릭터 생성 화면으로 이동
	RT_CHARACTER_CREATE,				// 캐릭터 생성 
	RT_CHARACTER_CREATE_SUCCESS,		// 캐릭터 생성 성공
	RT_CHARACTER_CREATE_FAIL,			// 캐릭터 생성 실패
	RT_CHARACTER_NICKOVERLAP_TRUE,		// 닉네임 중복
	RT_CHARACTER_EXIT,					// 생성 취소

	// 인게임매니저 결과
	RT_INGAME_MOVE = 300,				// 이동
	RT_INGAME_OTHERPLAYER_INFO,			// 다른 플레이어 정보
	RT_INGAME_OTHERPLAYER_LIST			// 다른 플레이어 리스트
};

#define USERCOUNT 200
#define CLIENTCOUNT 255
#define SERVERPORT 12345
#define BUFSIZE 512
#define IDSIZE 30
#define NICKNAMESIZE 20
#define CHARACTERCODESIZE 30
#define PRODUCT_NAMESIZE 50
#define ENCRYPT_KEY 951324896
#define SERVERIP "127.0.0.1"
//define SERVERIP "192.168.0.154"	// 402ip 호연노트북
//define SERVERIP "192.168.0.154"	// 402ip 호연노트북
//#define SERVERIP "192.168.123.181"
//#define SERVERIP "182.227.211.86"

#endif   
