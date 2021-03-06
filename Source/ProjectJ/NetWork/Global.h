#ifndef GLOBAL_H
#define GLOBAL_H

#pragma comment(lib, "ws2_32")
#include <WinSock2.h>
#include <stdio.h>

// 패킷 : [전체크기 4Byte][프로토콜 4Byte][데이터]
// 문자열 데이터 [strlen(문자열)+1 4Byte][문자열]

// AND연산용 변수
#define PROTOCOL_FFFFFFFFFFFFFFFF 0xFFFFFFFFFF000000

// ----------------- 큰틀 ----------------- //
#define PROTOCOL_80 0x80											// [큰틀 - 미정]
#define PROTOCOL_40 0x40											// [큰틀 - 미정]
#define PROTOCOL_20 0x20											// [큰틀 - 미정]
#define PROTOCOL_10 0x10											// [큰틀 - 미정]

#define PROTOCOL_8 0x8												// [큰틀 - 미정]
#define PROTOCOL_INGAME 0x4											// [큰틀 - 인게임]
#define PROTOCOL_CHRACTER 0x2										// [큰틀 - 캐릭터선택화면]
#define PROTOCOL_TITLE 0x1											// [큰틀 - 타이틀]

// ----------------- 타이틀 중간틀 ----------------- //
#define PROTOCOL_LOGIN 0x100										// [중간틀 - 타이틀]

// ----------------- 캐릭터 중간틀 ----------------- //
#define PROTOCOL_CHARACER_MENU 0x100								// [중간틀 - 캐릭터선택화면]

// ----------------- 인게임 중간틀 ----------------- //			
#define PROTOCOL_INGMAE_ITEM 0x8000									// [중간틀 - 인게임] 아이템관련
#define PROTOCOL_INGMAE_MENU 0x4000									// [중간틀 - 인게임] 매뉴관련
#define PROTOCOL_INGAME_ANIMATION 0x2000							// [중간틀 - 인게임] 애니메이션 관련
#define PROTOCOL_INGAME_DUNGEON 0x1000								// [중간틀 - 인게임] 던전관련

#define PROTOCOL_INGAME_PARTY 0x800									// [중간틀 - 인게임] 파티관련
#define PROTOCOL_INGAME_CHANNEL 0x400								// [중간틀 - 인게임] 채널관련
#define PROTOCOL_INGMAE_MONSTER 0x200								// [중간틀 - 인게임] 몬스터관련
#define PROTOCOL_INGAME_CHARACER 0x100								// [중간틀 - 인게임] 캐릭터관련

// -- 서버 -- //

// 타이틀 세부틀(PROTOCOL_LOGIN) -  [서버]
#define PROTOCOL_SERVER_LOGIN_MENU_COMPARE 0x7000000				// [세부틀 - 타이틀] [프로토콜 연산용]
#define PROTOCOL_SERVER_LOGIN_MENU_COMPARE_END 0x4000000			// [세부틀 - 타이틀] [프로토콜 연산용] - 끝
#define PROTOCOL_SERVER_LOGIN_MENU_COMPARE_START 0x1000000			// [세부틀 - 타이틀] [프로토콜 연산용] - 시작

#define PROTOCOL_LOGIN_RESULT 0x4000000								// [세부틀 - 타이틀] [서버->클라] 로그인 결과
#define PROTOCOL_JOIN_RESULT 0x2000000								// [세부틀 - 타이틀] [서버->클라] 회원가입 결과
#define PROTOCOL_ID_OVERLAP_CHECK 0x1000000							// [세부틀 - 타이틀] [서버->클라] ID 중복체크 결과

// 캐릭터 세부틀(PROTOCOL_CHARACER_MENU) -  [서버]
#define PROTOCOL_SERVER_CHARACTER_MENU_COMPARE 0xF000000			// [세부틀 - 캐릭터선택화면] [프로토콜 연산용]
#define PROTOCOL_SERVER_CHARACTER_MENU_COMPARE_END 0x8000000		// [세부틀 - 캐릭터선택화면] [프로토콜 연산용] - 끝
#define PROTOCOL_SERVER_CHARACTER_MENU_COMPARE_START 0x1000000		// [세부틀 - 캐릭터선택화면] [프로토콜 연산용] - 시작

#define PROTOCOL_CHARACTER_SLOT_INFO 0x8000000						// [세부틀 - 캐릭터선택화면] [서버->클라] 캐릭터 슬롯 정보		[프로토콜]...
#define PROTOCOL_CHARACTER_ENTER_RESULT	0x4000000					// [세부틀 - 캐릭터선택화면] [서버->클라] 캐릭터 접속결과		[프로토콜][bool]
#define PROTOCOL_CHARACTER_DELETE_RESULT 0x2000000					// [세부틀 - 캐릭터선택화면] [서버->클라] 캐릭터 삭제 결과		[프로토콜][bool]
#define PROTOCOL_CHARACTER_RESULT 0x1000000							// [세부틀 - 캐릭터선택화면] [서버->클라] 캐릭터 생성 확인 결과	[프로토콜][bool]

// 인게임 세부틀(PROTOCOL_INGAME_CHARACER) - [서버] 캐릭터 관련
#define PROTOCOL_SERVER_INGAME_CHARACTER_COMPARE_END 0x4000000000	// [세부틀 - 캐릭터관련] [프로토콜 연산용] - 끝
#define PROTOCOL_SERVER_INGAME_CHARACTER_COMPARE_START 0x10000000	// [세부틀 - 캐릭터관련] [프로토콜 연산용] - 시작

#define PROTOCOL_INGAME_OTHERPLAYER_ATTACK_SUCCESS 0x4000000000		// [세부틀 - 캐릭터관련] [서버->클라] 다른 유저 공격성공했다
#define PROTOCOL_INGAME_ATTACK_RESULT 0x2000000000					// [세부틀 - 캐릭터관련] [서버->클라] 유저 공격 결과
#define PROTOCOL_INGAME_OTHERPLAYER_ATTACK 0x1000000000				// [세부틀 - 캐릭터관련] [서버->클라] 다른 유저 공격했다

#define PROTOCOL_INGAME_MOVE_OTHERPLAYER_END_JUMP 0x800000000		// [세부틀 - 캐릭터관련] [서버->클라] 다른 유저 점프 끝났다는 정보(착지)
#define PROTOCOL_INGAME_MOVE_OTHERPLAYER_START_JUMP 0x400000000		// [세부틀 - 캐릭터관련] [서버->클라] 다른 유저 점프 했다는 정보
#define PROTOCOL_INGAME_OTHERPLAYER_LEAVE 0x200000000				// [세부틀 - 캐릭터관련] [서버->클라] 다른 유저 나간정보
#define PROTOCOL_INGAME_OTHERPLAYER_CONNECT 0x100000000				// [세부틀 - 캐릭터관련] [서버->클라] 다른 유저 접속정보

#define PROTOCOL_INGAME_MOVE_ROTATION 0x80000000					// [세부틀 - 캐릭터관련] [서버->클라] 다른 유저 회전 정보
#define PROTOCOL_INGAME_MOVE_OTHERPLAYERINFO 0x40000000				// [세부틀 - 캐릭터관련] [서버->클라] 다른 유저 이동 정보
#define PROTOCOL_INGAME_MOVE_RESULT 0x20000000						// [세부틀 - 캐릭터관련] [서버->클라] 유저 이동 결과
#define PROTOCOL_INGAME_OTHERPLAYERLIST_INFO 0x10000000				// [세부틀 - 캐릭터관련] [서버->클라] 유저들 정보

// 인게임 세부틀(PROTOCOL_INGMAE_MONSTER) - [서버] 몬스터 관련
#define PROTOCOL_SERVER_INGAME_MONSTER_COMPARE_END 0x800000000		// [세부틀 - 몬스터관련] [프로토콜 연산용] - 끝
#define PROTOCOL_SERVER_INGAME_MONSTER_COMPARE_START 0x10000000		// [세부틀 - 몬스터관련] [프로토콜 연산용] - 시작

#define PROTOCOL_INGAME_BOSS_MONSTER_ATTACK_RESULT 0x800000000		// [세부틀 - 몬스터관련] [서버->클라] 보스몬스터 공격 결과
#define PROTOCOL_INGAME_BOSS_MONSTER_ATTACK_INFO 0x400000000		// [세부틀 - 몬스터관련] [서버->클라] 보스몬스터 공격 정보
#define PROTOCOL_INGAME_BOSS_MONSTER_MOVE 0x200000000				// [세부틀 - 몬스터관련] [서버->클라] 보스몬스터 이동정보
#define PROTOCOL_INGAME_MONSTER_SET_TARGET	0x100000000				// [세부틀 - 몬스터관련] [서버->클라] 몬스터 대상지정

#define PROTOCOL_INGAME_MONSTER_OTHER_ATTACK_RESULT 0x80000000		// [세부틀 - 몬스터관련] [서버->클라] 몬스터 다른유저 공격결과
#define PROTOCOL_INGAME_MONSTER_ATTACK_RESULT 0x40000000			// [세부틀 - 몬스터관련] [서버->클라] 몬스터 유저 공격결과
#define PROTOCOL_MONSTER_INFO 0x20000000							// [세부틀 - 몬스터관련] [서버->클라] 정보를 주는 프로토콜
#define PROTOCOL_MONSTER_MOVE_RESULT 0x10000000						// [세부틀 - 몬스터관련] [서버->클라] 몬스터 이동정보

// 인게임 세부틀(PROTOCOL_INGAME_CHANNEL) - [서버] 채널 관련
#define PROTOCOL_SERVER_INGAME_CHANNEL_COMPARE_END 0x4000000		// [세부틀 - 채널관련] [프로토콜 연산용] - 끝
#define PROTOCOL_SERVER_INGAME_CHANNEL_COMPARE_START 0x1000000		// [세부틀 - 채널관련] [프로토콜 연산용] - 시작

#define PROTOCOL_CHANNLE_USER_CHANGE 0x4000000						// [세부틀 - 채널관련] [서버->클라] 채널 이동한 유저 정보
#define PROTOCOL_CHANNLE_CHANGE_RESULT 0x2000000					// [세부틀 - 채널관련] [서버->클라] 채널 변경 결과
#define PROTOCOL_CHANNLE_INFO 0x1000000								// [세부틀 - 채널관련] [서버->클라] 채널 정보

// 인게임 세부틀(PROTOCOL_INGAME_PARTY) - [서버] 파티 관련
#define PROTOCOL_SERVER_INGAME_PARTY_COMPARE_END 0x10000000000		// [세부틀 - 파티관련] [프로토콜 연산용] - 끝
#define PROTOCOL_SERVER_INGAME_PARTY_COMPARE_START 0x10000000		// [세부틀 - 파티관련] [프로토콜 연산용] - 시작

#define PROTOCOL_PARTY_USER_INFO 0x10000000000						// [세부틀 - 파티관련] [서버->클라] 파티원정보

#define PROTOCOL_PARTY_LEADER_DELEGATE_RESULT 0x8000000000			// [세부틀 - 파티관련] [서버->클라] 리더 위임 결과
#define PROTOCOL_PARTY_LEADER_DELEGATE 0x4000000000					// [세부틀 - 파티관련] [서버->클라] 리더 위임 받은 유저 정보
#define PROTOCOL_PARTY_ROOM_REMOVE_RESULT 0x2000000000				// [세부틀 - 파티관련] [서버->클라] 파티방 사라졌을때 보내는 프로토콜
#define PROTOCOL_PARTY_USER_LEAVE_RESULT 0x1000000000				// [세부틀 - 파티관련] [서버->클라] 탈퇴결과

#define PROTOCOL_PARTY_USER_LEAVE_INFO 0x800000000					// [세부틀 - 파티관련] [서버->클라] 탈퇴하는 유저 정보
#define PROTOCOL_PARTY_USER_KICK_RESULT 0x400000000					// [세부틀 - 파티관련] [서버->클라] 강퇴결과
#define PROTOCOL_PARTY_USER_KICK_INFO 0x200000000					// [세부틀 - 파티관련] [서버->클라] 강퇴당한 유저 정보
#define PROTOCOL_PARTY_USER_KICK 0x100000000						// [세부틀 - 파티관련] [서버->클라] 강퇴당한사람에게 보내는 프로토콜

#define PROTOCOL_PARTY_ROOM_ADD_USER 0x80000000						// [세부틀 - 파티관련] [서버->클라] 새로운 파티원이 들어옴
#define PROTOCOL_PARTY_ROOM_JOIN_RESULT 0x40000000					// [세부틀 - 파티관련] [서버->클라] 참여결과
#define PROTOCOL_PARTY_ROOM_INVITE_RESULT 0x20000000				// [세부틀 - 파티관련] [서버->클라] 파티 초대 결과
#define PROTOCOL_PARTY_ROOM_INVITE 0x10000000						// [세부틀 - 파티관련] [서버->클라] 파티 초대(특정유저에게)

// 인게임 세부틀(PROTOCOL_INGAME_DUNGEON) - [서버] 던전 관련
#define PROTOCOL_SERVER_INGAME_DUNGEON_COMPARE_END 0x80000000		// [세부틀 - 던전관련] [프로토콜 연산용] - 끝
#define PROTOCOL_SERVER_INGAME_DUNGEON_COMPARE_START 0x10000000		// [세부틀 - 던전관련] [프로토콜 연산용] - 시작

#define PROTOCOL_DUNGEON_STAGE_CLEAR_INFO 0x100000000				// [세부틀 - 던전관련] [서버->클라] 스테이지 클리어 정보

#define PROTOCOL_DUNGEON_STAGE_IN_RESULT 0x80000000					// [세부틀 - 던전관련] [서버->클라] 스테이지에 입장 결과
#define PROTOCOL_DUNGEON_STAGE_READY_RESULT 0x40000000				// [세부틀 - 던전관련] [서버->클라] 스테이지에 입장 준비 결과
#define PROTOCOL_DUNGEON_LEAVE_RESULT 0x20000000					// [세부틀 - 던전관련] [서버->클라] 던전 퇴장 결과
#define PROTOCOL_DUNGEON_ENTER_RESULT 0x10000000					// [세부틀 - 던전관련] [서버->클라] 던전 입장 결과

// 인게임 세부틀(PROTOCOL_INGAME_ANIMATION) - [서버] 애니메이션 관련
#define PROTOCOL_SERVER_INGAME_ANIMATION_COMPARE_END 0x4000000		// [세부틀 - 애니메이션관련] [프로토콜 연산용] - 끝
#define PROTOCOL_SERVER_INGAME_ANIMATION_COMPARE_START 0x1000000	// [세부틀 - 애니메이션관련] [프로토콜 연산용] - 시작

#define PROTOCOL_MONSTER_ANIMATION_ATTACK 0x4000000					// [세부틀 - 애니메이션관련] [서버->클라] 몬스터 애니메이션(공격)
#define PROTOCOL_MONSTER_ANIMATION 0x2000000						// [세부틀 - 애니메이션관련] [서버->클라] 몬스터 애니메이션
#define PROTOCOL_CHARACER_ANIMATION 0x1000000						// [세부틀 - 애니메이션관련] [서버->클라] 캐릭터 애니메이션

// 인게임 세부틀(PROTOCOL_INGMAE_MENU) - [서버] 매뉴 관련
#define PROTOCOL_SERVER_INGAME_MENU_COMPARE_END 0x4000000			// [세부틀 - 몬스터관련] [프로토콜 연산용] - 끝
#define PROTOCOL_SERVER_INGAME_MENU_COMPARE_START 0x1000000			// [세부틀 - 몬스터관련] [프로토콜 연산용] - 시작

#define PROTOCOL_OTHERPLAYER_LEAVE 0x4000000						// [세부틀 - 몬스터관련] [서버->클라] 다른 유저가 채널에서 나갔을때
#define PROTOCOL_MENU_RESULT_LOGOUT 0x2000000						// [세부틀 - 몬스터관련] [서버->클라] 로그아웃 결과
#define PROTOCOL_MENU_RESULT_CHARACTER 0x1000000					// [세부틀 - 몬스터관련] [서버->클라] 캐릭터 선택화면 결과

// 인게임 세부틀(PROTOCOL_INGMAE_ITEM) - [서버] 아이템 관련


// -- 서버 END -- //


// -- 클라 -- //

// 타이틀 세부틀(PROTOCOL_LOGIN) - [클라]
#define PROTOCOL_CLIENT_LOGIN_MENU_COMPART 0x7000000
#define PROTOCOL_CLIENT_LOGIN_MENU_COMPARE_END 0x4000000			// [세부틀 - 타이틀] [프로토콜 연산용] - 끝
#define PROTOCOL_CLIENT_LOGIN_MENU_COMPARE_START 0x1000000			// [세부틀 - 타이틀] [프로토콜 연산용] - 시작

#define PROTOCOL_REQ_LOGIN 0x4000000								// [세부틀 - 타이틀] [클라->서버] 로그인 요청
#define PROTOCOL_REQ_JOIN 0x2000000									// [세부틀 - 타이틀] [클라->서버] 회원가입 요청
#define PROTOCOL_REQ_ID_OVERLAP_CHECK 0x1000000						// [세부틀 - 타이틀] [클라->서버] ID 중복체크 요청

// 캐릭터 세부틀(PROTOCOL_CHARACER_MENU) - [클라]
#define PROTOCOL_CLIENT_CHARACTER_MENU_COMPARE 0xF000000		// [세부틀 - 캐릭터선택화면] [프로토콜 연산용] - 시작
#define PROTOCOL_CLIENT_CHARACTER_MENU_COMPARE_END 0x8000000		// [세부틀 - 캐릭터선택화면] [프로토콜 연산용] - 끝
#define PROTOCOL_CLIENT_CHARACTER_MENU_COMPARE_START 0x1000000		// [세부틀 - 캐릭터선택화면] [프로토콜 연산용] - 시작

#define PROTOCOL_REQ_CHARACTER_CREATE 0x8000000						// [세부틀 - 캐릭터선택화면] [클라->서버] 캐릭터 생성 요청
#define PROTOCOL_CHARACTER_DELETE 0x4000000							// [세부틀 - 캐릭터선택화면] [클라->서버] 캐릭터 삭제 요청
#define PROTOCOL_CHARACTER_ENTER 0x2000000							// [세부틀 - 캐릭터선택화면] [클라->서버] 캐릭터 접속 요청
#define PROTOCOL_REQ_CHARACTER_SLOT 0x1000000						// [세부틀 - 캐릭터선택화면] [클라->서버] 캐릭터 슬롯 정보 요총

// 인게임 세부틀(PROTOCOL_INGAME_CHARACER) - [클라] 캐릭터 관련
#define PROTOCOL_CLIENT_INGAME_CHARACTER_COMPARE_END 0x400000000	// [세부틀 - 캐릭터관련] [프로토콜 연산용] - 끝
#define PROTOCOL_CLIENT_INGAME_CHARACTER_COMPARE_START 0x10000000	// [세부틀 - 캐릭터관련] [프로토콜 연산용] - 시작

#define PROTOCOL_INGAME_ATTACK_SUCCESS 0x400000000					// [세부틀 - 캐릭터관련] [클라->서버] 공격했는데 몬스터랑 피격판정이난것같다.
#define PROTOCOL_INGAME_ATTACK 0x200000000							// [세부틀 - 캐릭터관련] [클라->서버] 공격했다는 정보
#define PROTOCOL_INGAME_MOVE_END_JUMP 0x100000000					// [세부틀 - 캐릭터관련] [클라->서버] 점프 끝났다는 정보(착지)

#define PROTOCOL_INGAME_MOVE_START_JUMP 0x80000000					// [세부틀 - 캐릭터관련] [클라->서버] 점프 시작했다는 정보
#define PROTOCOL_MOVE_ROTATION 0x40000000							// [세부틀 - 캐릭터관련] [클라->서버] 회전 정보
#define PROTOCOL_MOVE_REPORT 0x20000000								// [세부틀 - 캐릭터관련] [클라->서버] 이동 정보
#define PROTOCOL_REQ_OTHERPLAYERLIST 0x10000000						// [세부틀 - 캐릭터관련] [클라->서버] 다른 유저 요청

// 인게임 세부틀(PROTOCOL_INGMAE_MONSTER) - [클라] 몬스터 관련
#define PROTOCOL_CLIENT_INGAME_MONSTER_COMPARE_END 0x100000000		// [세부틀 - 몬스터관련] [프로토콜 연산용] - 끝
#define PROTOCOL_CLIENT_INGAME_MONSTER_COMPARE_START 0x10000000		// [세부틀 - 몬스터관련] [프로토콜 연산용] - 시작

#define PROTOCOL_REQ_BOSS_MONSTER_ATTACK 0x100000000				// [세부틀 - 몬스터관련] [클라->서버] 보스 몬스터 유저를 공격했다

#define PROTOCOL_BOSS_MONSTER_MOVE 0x80000000						// [세부틀 - 몬스터관련] [클라->서버] 보스 몬스터 이동
#define PROTOCOL_REQ_MONSTER_ATTACK 0x40000000						// [세부틀 - 몬스터관련] [클라->서버] 몬스터 유저를 공격했다
#define PROTOCOL_MONSTER_MOVE 0x20000000							// [세부틀 - 몬스터관련] [클라->서버] 몬스터 이동
#define PROTOCOL_REQ_MONSTER_INFO 0x10000000						// [세부틀 - 몬스터관련] [클라->서버] 몬스터 정보 요청

// 인게임 세부틀(PROTOCOL_INGAME_CHANNEL) - [클라] 채널 관련
#define PROTOCOL_CLIENT_INGAME_CHANNEL_COMPARE_END 0x2000000		// [세부틀 - 채널관련] [프로토콜 연산용] - 끝
#define PROTOCOL_CLIENT_INGAME_CHANNEL_COMPARE_START 0x1000000		// [세부틀 - 채널관련] [프로토콜 연산용] - 시작

#define PROTOCOL_REQ_CHANNEL_CHANGE 0x2000000						// [세부틀 - 채널관련] [클라->서버] 채널 이동 요청
#define PROTOCOL_REQ_CHANNEL_INFO 0x1000000							// [세부틀 - 채널관련] [클라->서버] 채널 정보 요청

// 인게임 세부틀(PROTOCOL_INGAME_PARTY) - [클라] 파티 관련
#define PROTOCOL_CLIENT_INGAME_PARTY_COMPARE_END 0x100000000		// [세부틀 - 파티관련] [프로토콜 연산용] - 끝
#define PROTOCOL_CLIENT_INGAME_PARTY_COMPARE_START 0x10000000		// [세부틀 - 파티관련] [프로토콜 연산용] - 시작

#define PROTOCOL_REQ_LEADER_DELEGATE 0x100000000					// [세부틀 - 파티관련] [클라->서버] 파티장 위임 요청

#define PROTOCOL_REQ_USER_LEAVE 0x80000000							// [세부틀 - 파티관련] [클라->서버] 파티 탈퇴 요청
#define PROTOCOL_REQ_USER_KICK 0x40000000							// [세부틀 - 파티관련] [클라->서버] 파티원 강퇴 요청
#define PROTOCOL_PARTY_ROOM_ANSWER_INVITE 0x20000000				// [세부틀 - 파티관련] [클라->서버] 파티 초대 응답
#define PROTOCOL_REQ_PARTY_ROOM_INVITE 0x10000000					// [세부틀 - 파티관련] [클라->서버] 파티 초대 요청

// 인게임 세부틀(PROTOCOL_INGAME_DUNGEON) - [클라] 던전 관련
#define PROTOCOL_CLIENT_INGAME_DUNGEON_COMPARE_END 0x100000000		// [세부틀 - 던전관련] [프로토콜 연산용] - 끝
#define PROTOCOL_CLIENT_INGAME_DUNGEON_COMPARE_START 0x10000000		// [세부틀 - 던전관련] [프로토콜 연산용] - 시작

#define PROTOCOL_DUNGEON_CLEAR_CHOICE 0x100000000					// [세부틀 - 던전관련] [클라->서버] 스테이지 클리어 후 메뉴 선택(다음스테이지 준비, 파티탈퇴(마을로가기))

#define PROTOCOL_DUNGEON_STAGE_IN 0x80000000						// [세부틀 - 던전관련] [클라->서버] 스테이지 입장 요청(파티 리더)
#define PROTOCOL_DUNGEON_STAGE_READY_INFO 0x40000000				// [세부틀 - 던전관련] [클라->서버] 스테이지 입장 준비(파티원)
#define PROTOCOL_REQ_DUNGEON_LEAVE 0x20000000						// [세부틀 - 던전관련] [클라->서버] 던전 나가기 요청
#define PROTOCOL_REQ_DUNGEON_ENTER 0x10000000						// [세부틀 - 던전관련] [클라->서버] 던전 입장 요청

// 인게임 세부틀(PROTOCOL_INGAME_ANIMATION) - [클라] 애니메이션 관련
#define PROTOCOL_CLIENT_INGAME_ANIMATION_COMPARE_END 0x4000000		// [세부틀 - 애니메이션관련] [프로토콜 연산용] - 끝
#define PROTOCOL_CLIENT_INGAME_ANIMATION_COMPARE_START 0x1000000	// [세부틀 - 애니메이션관련] [프로토콜 연산용] - 시작

#define PROTOCOL_CLIENT_MONSTER_ANIMATION_ATTACK 0x4000000			// [세부틀 - 애니메이션관련] [클라->서버] 몬스터 애니메이션(공격)
#define PROTOCOL_CLIENT_MONSTER_ANIMATION 0x2000000					// [세부틀 - 애니메이션관련] [클라->서버] 몬스터 애니메이션
#define PROTOCOL_CLIENT_CHARACER_ANIMATION 0x1000000				 // [세부틀 - 애니메이션관련] [클라->서버] 캐릭터 애니메이션

// 인게임 세부틀(PROTOCOL_INGMAE_MENU) - [클라] 매뉴 관련
#define PROTOCOL_CLIENT_INGAME_MENU_COMPARE_END 0x4000000			// [세부틀 - 매뉴관련] [프로토콜 연산용] - 끝
#define PROTOCOL_CLIENT_INGAME_MENU_COMPARE_START 0x1000000			// [세부틀 - 매뉴관련] [프로토콜 연산용] - 시작

#define PROTOCOL_MENU_EXIT 0x4000000								// [세부틀 - 매뉴관련] [클라->서버] 종료
#define PROTOCOL_MENU_REQ_LOGOUT 0x2000000							// [세부틀 - 매뉴관련] [클라->서버] 로그아웃 요청
#define PROTOCOL_MENU_REQ_CHARACTER 0x1000000						// [세부틀 - 매뉴관련] [클라->서버] 캐릭터 선택화면으로 요청

// 인게임 세부틀(PROTOCOL_INGMAE_ITEM) - [클라] 아이템 관련


enum PROTOCOL {
	EXIT = -1,
	CLIENT_JOIN_MENU_CHOICE = 0,				// 회원가입 메뉴 선택			[프로토콜][int]
	CLIENT_LOGIN_MENU_CHOICE,					// 로그인 메뉴 선택				[프로토콜][int]
	CLIENT_REQ_EXIT_JOIN,						// 회원가입 취소 선택			[프로토콜]
	CLIENT_REQ_ID_OVERLAP_CHECK,				// 회원가입 ID중복체크 요청		[프로토콜][int][char *]
	CLIENT_REQ_JOIN,							// 회원가입 요청				[프로토콜][int][char *]
	CLIENT_REQ_LOGIN,							// 로그인 요청					[프로토콜][int][char *][int][char *]

	SERVER_JOIN,								// 회원가입 메뉴 선택			[프로토콜]
	SERVER_LOGIN,								// 로그인 메뉴 선택				[프로토콜]
	SERVER_EXIT_JOIN,							// 회원가입 취소 결과			[프로토콜]
	SERVER_ID_OVERLAP_CHECK,					// ID중복 결과 보냄				[프로토콜][bool]
	SERVER_JOIN_SUCCESS,						// 회원가입 결과 메세지			[프로토콜]
	SERVER_LOGIN_SUCCESS,						// 로그인 성공 여부				[프로토콜][bool]

	CLIENT_REQ_CHARACTER_SLOT,					// 클라 케릭터 슬롯 요청		[프로토콜]
	CLIENT_CHARACTER_ENTER,						// 클라 케릭터 접속				[프로토콜][int]
	CLIENT_CHARACTER_DELETE,					// 클라 케릭터 삭제				[프로토콜][int]
	CLIENT_NEW_CHARACTER_MENU,					// 클라 케릭터생성 메뉴			[프로토콜]
	CLIENT_REQ_NICK_OVERLAP_CHECK,				// 클라 닉네임 중복				[프로토콜][int][char*]
	CLIENT_REQ_CHARACTER,						// 클라 케릭터 생성 요청		[프로토콜][int][char*][int] : [nicknamesize][nickname][charactercode]
	CLIENT_CHARACTER_EXIT,						// 클라 케릭터 생성 취소		[프로토콜]
	CLIENT_LOGOUT,								// 클라 로그아웃				[프로토콜]
	CLIENT_LEAVE,								// 클라 회원탈퇴				[프로토콜]

	SERVER_CHARACTER_SLOT_RESULT,				// 서버 케릭터 슬롯 전송		[프로토콜]...
	SERVER_CHARACTER_ENTER_RESULT,				// 서버 케릭터 접속결과			[프로토콜][bool]
	SERVER_CHARACTER_ENTER_INFO,				// 서버 케릭터 접속 정보		[DataProtocol용]
	SERVER_CHARACTER_DELETE_RESULT,				// 서버 케릭터 삭제 결과		[프로토콜][bool]
	SERVER_CHARACTER_MENU,						// 서버 케릭터 메뉴 결과		[프로토콜]
	//SERVER_NICK_OVERLAP_CHECK,				// 서버 닉네임 중복 결과		[프로토콜][bool]
	SERVER_CHARACTER_RESULT,					// 서버 케릭터 생성 확인 결과	[프로토콜][bool]
	SERVER_CHARACTER_EXIT_RESULT,				// 서버 케릭터 생성 취소 결과	[프로토콜[
	SERVER_LEAVE,								// 서버 회원탈퇴 결과			[프로토콜][bool]
	SERVER_LOGOUT,								// 서버 로그아웃 결과			[프로토콜][bool]

	// 입찰 프로토콜
	SERVER_TENDER,								// 입찰 선택
	CLIENT_TENDER_MENU_CHOICE,					// 입찰메뉴 선택 확인
	SERVER_TENDER_CREATE,						// 입찰물품 생성 선택 
	SERVER_TENDER_PARTICIPATE,					// 입찰 참여 선택
	SERVER_BACK,								// 뒤로가기
	CLIENT_REQ_TENDER_CREATE,					// 입찰물품 생성 요청	 [프로토콜][char* 물품이름][int 가격][int 입찰자수]
	SERVER_TENDER_CREATE_RESULT,				// 입찰물품 생성 요청 결과
	CLIENT_REQ_TENDER_LIST,						// 입찰 리스트 요청
	SERVER_TENDER_LIST_RESULT,					// 입찰 리스트 요청 결과
	CLIENT_REQ_TENDER_PARTICIPATE,				// 입찰 요청
	SERVER_TENDER_PARTICIPATE_RESULT,			// 입찰 요청 결과
	SERVER_TENDER_END_RESULT,					// 입찰 종료 결과 [프로토콜][char* 메세지]

	// 인게임 프로토콜
	CLIENT_INGAME_OTHERPLAYERLIST,				// 클라 다른플레이어 리스트 요청	[프로토콜][]
	CLIENT_INGAME_MOVE_START,					// 클라 이동 시작					[프로토콜]
	CLIENT_INGAME_MOVE_REPORT,					// 클라 이동중 보고					[프로토콜]
	CLIENT_INGAME_MOVE_END,						// 클라 이동 끝						[프로토콜]
	CLIENT_INGAME_MOVE_ROTATION,				// 클라 회전
	SERVER_INGAME_MOVE_ORDER,					// 서버 이동 명령					[프로토콜][FLOAT][FLOAT][FLOAT][FLOAT : 시간]
	SERVER_INGAME_MOVE_RESULT,					// 서버 이동 결과					[프로토콜][FLOAT][FLOAT][FLOAT][FLOAT : 시간]
	SERVER_INGAME_MOVE_OTHERPLAYERINFO,			// 다른플레이어 정보				[프로토콜][FLOAT][FLOAT][FLOAT][FLOAT : 시간][닉네임사이즈][닉네임]
	SERVER_INGAME_MOVE_ROTATION,				// 클라 회전
	SERVER_INGAME_OTHERPLAYERLIST_RESULT,		// 플레이어 리스트 					[프로토콜][INT:카운트][INT:닉네임사이즈][CHAR:닉네임][VECTOR:위치]...
	SERVER_INGAME_OTHERPLAYER_CONNECT,			// 접속한 플레이어 정보

	// 인게임 매뉴
	CLIENT_INGAME_MENU_REQ_CHARACTER,			// 클라 캐릭터 선택화면으로 요청
	CLIENT_INGAME_MENU_REQ_LOGOUT,				// 클라 로그아웃
	CLIENT_INGAME_MENU_EXIT,					// 클라 게임종료
	SERVER_INGAME_MENU_RESULT_CHARACTER,		// 서버 캐릭터 선택화면 결과
	SERVER_INGAME_MENU_RESULT_LOGOUT,			// 서버 로그아웃 결과
	SERVER_INGAME_OTHERPLAYER_LEAVE,			// 서버 다른 유저가 채널에서 나갔을때

	// 인게임 채널
	CLIENT_INGAME_CHANNEL_INFO,					// 클라 채널 정보 요청
	CLIENT_INGAME_CHANNEL_CHANGE,				// 클라 채널 이동 요청
	SERVER_INGAME_CHANNLE_INFO_RESULT,			// 서버 채널 정보 결과
	SERVER_INGAME_CHANNLE_CHANGE_RESULT,		// 서버 채널 이동 요청 결과
	SERVER_INGAME_CHANNLE_USER_CHANGE,			// 서버 채널 이동 요청시 그 유저 이동했다고 통보

	// 인게임 파티
	CLIENT_INGAME_PARTY_ROOM_JOIN,				// 클라 파티 참여 요청
	CLIENT_INGAME_PARTY_ROOM_INVITE,			// 클라 파티 초대 요청
	CLIENT_INGAME_PARTY_ROOM_ANSWER_INVITE,		// 클라 파티 초대 응답
	CLIENT_INGAME_PARTY_USER_KICK,				// 클라 파티원 강퇴 요청
	CLIENT_INGAME_PARTY_USER_LEAVE,				// 클라 파티 탈퇴 요청
	CLIENT_INGAME_PARTY_LEADER_DELEGATE,		// 클라 파티장 위임

	SERVER_INGAME_PARTY_ROOM_INVITE,			// 서버 파티 초대(특정유저에게)
	SERVER_INGAME_PARTY_ROOM_INVITE_RESULT,		// 서버 파티 초대 결과
	SERVER_INGAME_PARTY_ROOM_JOIN_RESULT,		// 서버 파티 참여 결과
	SERVER_INGAME_PARTY_ROOM_ADD_USER,			// 서버 새로운 파티원이 들어옴
	SERVER_INGAME_PARTY_USER_KICK,				// 서버 파티 강퇴당한사람에게 보내는 프로토콜
	SERVER_INGAME_PARTY_USER_KICK_INFO,			// 서버 파티 강퇴당했다는정보 프로토콜 
	SERVER_INGAME_PARTY_USER_KICK_RESULT,		// 서버 파티 강퇴결과
	SERVER_INGAME_PARTY_USER_LEAVE_INFO,		// 서버 파티 탈퇴하는 유저 정보
	SERVER_INGAME_PARTY_USER_LEAVE_RESULT,		// 서버 파티 탈퇴결과
	SERVER_INGAME_PARTY_ROOM_REMOVE_RESULT,		// 서버 파티방 폭파시 속해있는 유저한테 보내는 프로토콜
	SERVER_INGAME_PARTY_LEADER_DELEGATE,		// 서버 파티장 위임 받은 유저 정보
	SERVER_INGAME_PARTY_LEADER_DELEGATE_RESULT,	// 서버 파티장 위임 결과
	SERVER_INGAME_PARTY_USER_INFO,				// 서버 파티원정보(파티원숫자,닉네임,HP,MP)

	// 던전 프로토콜
	CLIENT_INGAME_DUNGEON_ENTER,				// 클라 던전 입장
	CLIENT_INGAME_DUNGEON_LEAVE,				// 클라 던전 퇴장
	CLIENT_INGAME_DUNGEON_STAGE_IN,				// 클라 던전 스테이지에 입장하겠다는 프로토콜(리더가보냄)

	SERVER_INGAME_DUNGEON_ENTER_RESULT,			// 서버 던전 입장 결과
	SERVER_INGAME_DUNGEON_LEAVE_RESULT,			// 서버 던전 퇴장 결과
	SERVER_INGAME_DUNGEON_STAGE_IN_REULST,		// 서버 던전 스테이지에 입장결과

	// 몬스터 프로토콜
	CLIENT_INGAME_MONSTER_INFO,					// 클라 몬스터 정보 요청
	CLIENT_INGAME_MONSTER_MOVE,					// 클라 파티리더가 몬스터 이동정보를 보낸다

	SERVER_INGAME_MONSTER_INFO,					// 서버 몬스터 정보를 주는 프로토콜
	SERVER_INGAME_MONSTER_MOVE_RESULT,			// 서버 몬스터 이동정보

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
	INIT_STATE, LOGIN_STATE, TENDER_STATE, JOIN_STATE, EXIT_STATE,
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
	RT_DEFAULT = 0,
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
	RT_INGAME_OTHERPLAYER_LIST,			// 다른 플레이어 리스트
	RT_INGAME_CHANNEL_INFO,				// 채널 정보
	RT_INGAME_CHANNEL_CHANGE,			// 채널 이동
	RT_INGAME_OTHERPLAYER_LEAVE,		// 다른 유저가 나갔을때
	RT_INGAME_MENU_CHARACTER,			// 캐릭터 선택화면
	RT_INGAME_MENU_LOGOUT,				// 로그아웃
	RT_INGAME_MENU_EXIT,				// 종료
	RT_INGAME_PARTY_INVITE,				// 파티 초대
	RT_INGAME_PARTY_INVITE_RESULT,		// 파티 초대 결과
	RT_INGAME_PARTY_JOIN_RESULT,		// 파티 참여 결과
	RT_INGAME_PARTY_ADD_USER,			// 파티원 증가
	RT_INGAME_PARTY_KICK,				// 파티 강퇴
	RT_INGAME_PARTY_KICK_USER_INFO,		// 파티 당한 유저의 정보를 받았을때
	RT_INGAME_PARTY_KICK_RESULT,		// 파티 강퇴 결과
	RT_INGAME_PARTY_LEAVE_INFO,			// 탈퇴하는 유저정보
	RT_INGAME_PARTY_LEAVE_RESULT,		// 탈퇴 결과
	RT_INGAME_PARTY_ROOM_REMOVE,		// 파티방 폭파시
	RT_INGAME_PARTY_LEADER_DELEGATE,
	RT_INGAME_PARTY_LEADER_DELEGATE_RESULT,
	RT_INGAME_DUNGEON_ENTER_RESULT,			// 던전 입장 결과
	RT_INGAME_DUNGEON_LEAVE_RESULT,			// 던전 퇴장 결과
	RT_INGAME_DUNGEON_STAGE_READY_RESULT,	// 스테이지 입장 결과
	RT_INGAME_DUNGEON_STAGE_ENTER_RESULT,	// 스테이지 입장 결과
	RT_INGAME_MONSTER_INFO_RESULT,			// 몬스터 정보 결과
	RT_INGAME_MONSTER_MOVE_INFO_RESULT,		// 몬스터 이동정보 결과
	RT_INGAME_USER_UNDERATTACK_RESULT,		// 유저 공격 결과
	RT_INGAME_OTHERUSER_UNDERATTACK_RESULT,	// 다른 유저 공격 결과
	RT_INGAME_MONSTER_TARGET_RESULT			// 몬스터 타겟 결과
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
//#define SERVERIP "127.0.0.1"
//#define SERVERIP "192.168.0.141"	// 402ip 영준 그램노트북
//#define SERVERIP "192.168.0.136"	// 202ip 영준 그램노트북
//#define SERVERIP "192.168.0.134"	// 202ip 호연노트북
//#define SERVERIP "192.168.0.154"	// 402ip 호연노트북
//#define SERVERIP "192.168.0.166"	// 302ip 호연노트북
//#define SERVERIP "192.168.43.58"	// 호연핫스팟 호연노트북
//#define SERVERIP "172.30.35.30"	// KT Free Wifi 호연노트북
//#define SERVERIP "192.168.43.180"	// 호연핫스팟 영준그램노트북
//#define SERVERIP "192.168.7.15"	// consult room 호연노트북
#define SERVERIP "192.168.0.192"	// 404 호연노트북
//#define SERVERIP "127.0.43.180"
//#define SERVERIP "192.168.123.181"
//#define SERVERIP "182.227.211.86"
//#define SERVERIP "192.168.0.134"
//#define SERVERIP "192.168.17.26"

#endif
