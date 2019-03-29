#ifndef GLOBAL_H
#define GLOBAL_H

#pragma comment(lib, "ws2_32")
#include <WinSock2.h>
#include <stdio.h>

// ��Ŷ : [��üũ�� 4Byte][�������� 4Byte][������]
// ���ڿ� ������ [strlen(���ڿ�)+1 4Byte][���ڿ�]
enum PROTOCOL {
	EXIT = -1,
	CLIENT_JOIN_MENU_CHOICE = 0,			// ȸ������ �޴� ����			[��������][int]
	CLIENT_LOGIN_MENU_CHOICE,				// �α��� �޴� ����				[��������][int]
	CLIENT_REQ_EXIT_JOIN,					// ȸ������ ��� ����			[��������]
	CLIENT_REQ_ID_OVERLAP_CHECK,			// ȸ������ ID�ߺ�üũ ��û		[��������][int][char *]
	CLIENT_REQ_JOIN,						// ȸ������ ��û				[��������][int][char *]
	CLIENT_REQ_LOGIN,						// �α��� ��û					[��������][int][char *][int][char *]

	SERVER_JOIN,							// ȸ������ �޴� ����			[��������]
	SERVER_LOGIN,							// �α��� �޴� ����				[��������]
	SERVER_EXIT_JOIN,						// ȸ������ ��� ���			[��������]
	SERVER_ID_OVERLAP_CHECK,				// ID�ߺ� ��� ����				[��������][bool]
	SERVER_JOIN_SUCCESS,					// ȸ������ ��� �޼���			[��������]
	SERVER_LOGIN_SUCCESS,					// �α��� ���� ����				[��������][bool]

	CLIENT_REQ_CHARACTER_SLOT,				// Ŭ�� �ɸ��� ���� ��û		[��������]
	CLIENT_CHARACTER_ENTER,					// Ŭ�� �ɸ��� ����				[��������][int]
	CLIENT_CHARACTER_DELETE,				// Ŭ�� �ɸ��� ����				[��������][int]
	CLIENT_NEW_CHARACTER_MENU,				// Ŭ�� �ɸ��ͻ��� �޴�			[��������]
	CLIENT_REQ_NICK_OVERLAP_CHECK,			// Ŭ�� �г��� �ߺ�				[��������][int][char*]
	CLIENT_REQ_CHARACTER,					// Ŭ�� �ɸ��� ���� ��û		[��������][int][char*][int] : [nicknamesize][nickname][charactercode]
	CLIENT_CHARACTER_EXIT,					// Ŭ�� �ɸ��� ���� ���		[��������]
	CLIENT_LOGOUT,							// Ŭ�� �α׾ƿ�				[��������]
	CLIENT_LEAVE,							// Ŭ�� ȸ��Ż��				[��������]

	SERVER_CHARACTER_SLOT_RESULT,			// ���� �ɸ��� ���� ����		[��������]...
	SERVER_CHARACTER_ENTER_RESULT,			// ���� �ɸ��� ���Ӱ��			[��������][bool]
	SERVER_CHARACTER_ENTER_INFO,			// ���� �ɸ��� ���� ����		[DataProtocol��]
	SERVER_CHARACTER_DELETE_RESULT,			// ���� �ɸ��� ���� ���		[��������][bool]
	SERVER_CHARACTER_MENU,					// ���� �ɸ��� �޴� ���		[��������]
	//SERVER_NICK_OVERLAP_CHECK,			// ���� �г��� �ߺ� ���		[��������][bool]
	SERVER_CHARACTER_RESULT,				// ���� �ɸ��� ���� Ȯ�� ���	[��������][bool]
	SERVER_CHARACTER_EXIT_RESULT,			// ���� �ɸ��� ���� ��� ���	[��������[
	SERVER_LEAVE,							// ���� ȸ��Ż�� ���			[��������][bool]
	SERVER_LOGOUT,							// ���� �α׾ƿ� ���			[��������][bool]

	// ���� ��������
	SERVER_TENDER,							// ���� ����
	CLIENT_TENDER_MENU_CHOICE,				// �����޴� ���� Ȯ��
	SERVER_TENDER_CREATE,					// ������ǰ ���� ���� 
	SERVER_TENDER_PARTICIPATE,				// ���� ���� ����
	SERVER_BACK,							// �ڷΰ���
	CLIENT_REQ_TENDER_CREATE,				// ������ǰ ���� ��û	 [��������][char* ��ǰ�̸�][int ����][int �����ڼ�]
	SERVER_TENDER_CREATE_RESULT,			// ������ǰ ���� ��û ���
	CLIENT_REQ_TENDER_LIST,					// ���� ����Ʈ ��û
	SERVER_TENDER_LIST_RESULT,				// ���� ����Ʈ ��û ���
	CLIENT_REQ_TENDER_PARTICIPATE,			// ���� ��û
	SERVER_TENDER_PARTICIPATE_RESULT,		// ���� ��û ���
	SERVER_TENDER_END_RESULT,				// ���� ���� ��� [��������][char* �޼���]

	// �ΰ��� ��������
	CLIENT_INGAME_OTHERPLAYERLIST,			// Ŭ�� �ٸ��÷��̾� ����Ʈ ��û	[��������][]
	CLIENT_INGAME_MOVE_START,				// Ŭ�� �̵� ����					[��������]
	CLIENT_INGAME_MOVE_REPORT,				// Ŭ�� �̵��� ����					[��������]
	CLIENT_INGAME_MOVE_END,					// Ŭ�� �̵� ��						[��������]
	CLIENT_INGAME_MOVE_ROTATION,			// Ŭ�� ȸ��
	SERVER_INGAME_MOVE_ORDER,				// ���� �̵� ���					[��������][FLOAT][FLOAT][FLOAT][FLOAT : �ð�]
	SERVER_INGAME_MOVE_RESULT,				// ���� �̵� ���					[��������][FLOAT][FLOAT][FLOAT][FLOAT : �ð�]
	SERVER_INGAME_MOVE_OTHERPLAYERINFO,		// �ٸ��÷��̾� ����				[��������][FLOAT][FLOAT][FLOAT][FLOAT : �ð�][�г��ӻ�����][�г���]
	SERVER_INGAME_MOVE_ROTATION,			// Ŭ�� ȸ��
	SERVER_INGAME_OTHERPLAYERLIST_RESULT,	// �÷��̾� ����Ʈ 					[��������][INT:ī��Ʈ][INT:�г��ӻ�����][CHAR:�г���][VECTOR:��ġ]...
	SERVER_INGAME_OTHERPLAYER_CONNECT,		// ������ �÷��̾� ����

	CLIENT_INGAME_MENU_REQ_CHARACTER,		// Ŭ�� ĳ���� ����ȭ������ ��û
	CLIENT_INGAME_MENU_REQ_LOGOUT,			// Ŭ�� �α׾ƿ�
	CLIENT_INGAME_MENU_EXIT,				// Ŭ�� ��������
	SERVER_INGAME_MENU_RESULT_CHARACTER,	// ���� ĳ���� ����ȭ�� ���
	SERVER_INGAME_MENU_RESULT_LOGOUT,		// ���� �α׾ƿ� ���
	SERVER_INGAME_OTHERPLAYER_LEAVE,		// ���� �ٸ� ������ �ΰ��ӿ��� ������

	CLIENT_INGAME_CHANNEL_INFO,				// Ŭ�� ä�� ���� ��û
	CLIENT_INGAME_CHANNEL_CHANGE,			// Ŭ�� ä�� �̵� ��û
	SERVER_INGAME_CHANNLE_INFO_RESULT,		// ���� ä�� ���� ���
	SERVER_INGAME_CHANNLE_CHANGE_RESULT,	// ���� ä�� �̵� ��û ���
	SERVER_INGAME_CHANNLE_USER_CHANGE,		// ���� ä�� �̵� ��û�� �� ���� �̵��ߴٰ� �뺸

	CLIENT_INGAME_PARTY_ROOM_JOIN,				// Ŭ�� ��Ƽ ���� ��û
	CLIENT_INGAME_PARTY_ROOM_INVITE,			// Ŭ�� ��Ƽ �ʴ� ��û
	CLIENT_INGAME_PARTY_ROOM_ANSWER_INVITE,		// Ŭ�� ��Ƽ �ʴ� ����
	CLIENT_INGAME_PARTY_USER_KICK,				// Ŭ�� ��Ƽ�� ���� ��û
	CLIENT_INGAME_PARTY_USER_LEAVE,				// Ŭ�� ��Ƽ Ż�� ��û
	CLIENT_INGAME_PARTY_LEADER_DELEGATE,		// Ŭ�� ��Ƽ�� ����

	SERVER_INGAME_PARTY_ROOM_INVITE,			// ���� ��Ƽ �ʴ�(Ư����������)
	SERVER_INGAME_PARTY_ROOM_INVITE_RESULT,		// ���� ��Ƽ �ʴ� ���
	SERVER_INGAME_PARTY_ROOM_JOIN_RESULT,		// ���� ��Ƽ ���� ���
	SERVER_INGAME_PARTY_ROOM_ADD_USER,			// ���� ���ο� ��Ƽ���� ����
	SERVER_INGAME_PARTY_USER_KICK,				// ���� ��Ƽ ������ѻ������ ������ ��������
	SERVER_INGAME_PARTY_USER_KICK_INFO,			// ���� ��Ƽ ������ߴٴ����� �������� 
	SERVER_INGAME_PARTY_USER_KICK_RESULT,		// ���� ��Ƽ ������
	SERVER_INGAME_PARTY_USER_LEAVE_INFO,		// ���� ��Ƽ Ż���ϴ� ���� ����
	SERVER_INGAME_PARTY_USER_LEAVE_RESULT,		// ���� ��Ƽ Ż����
	SERVER_INGAME_PARTY_ROOM_REMOVE_RESULT,		// ���� ��Ƽ�� ���Ľ� �����ִ� �������� ������ ��������
	SERVER_INGAME_PARTY_LEADER_DELEGATE,		// ���� ��Ƽ�� ���� ���� ���� ����
	SERVER_INGAME_PARTY_LEADER_DELEGATE_RESULT,	// ���� ��Ƽ�� ���� ���
	SERVER_INGAME_PARTY_USER_INFO,				// ���� ��Ƽ������(��Ƽ������,�г���,HP,MP)

	// ä�� ��������
	CLIENT_REQ_CHAT_LIST,					// ���� �α����� ȸ������Ʈ ��û 			 �������ݸ�
	SERVER_CHAT_LIST_RESULT,				// ���� �α����� ȸ������Ʈ ��û ��� 		[�ο� ��] [�г��� ������] [�г���]...
	CLIENT_REQ_CHAT_START,					// ä�� ��û 								[�ο� ��] [�г��� ������] [�г���]
	SERVER_CHAT_START_RESULT,				// ä�� ��û ��� 							[BOOL��]  ?  [�� ��ȣ] : [���� �ڵ�] [�޼��� ������] [�޼���]
	SERVER_CHAT_MSG,						// ä�� �޼��� : ���� --> Ŭ��				[�� ��ȣ] [�޼��� ������] [�޼���]
	CLIENT_CHAT_MSG,						// ä�� �޼��� : Ŭ�� --> ����				[�� ��ȣ] [�޼��� ������] [�޼���]
	SERVER_CHAT_ENTER,						// ���� ä�ù� ���� : ���� --> Ŭ��			[�� ��ȣ] [�г��� ������] [�г���]
	CLIENT_CHAT_EXIT,						// ���� ä�ù� ���� : Ŭ�� --> ����			[�� ��ȣ] [�г��� ������] [�г���]
	SERVER_CHAT_EXIT						// ä�ù� ���� : ���� --> Ŭ��				[�� ��ȣ]

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

	SEND_TENDER, //���� ����
	RECV_TENDER_MENU_CHOICE, //�����޴� ���� Ȯ��
	SEND_TENDER_CREATE, //������ǰ ���� ���� 
	SEND_TENDER_PARTICIPATE, //���� ���� ����
	SEND_BACK, //�ڷΰ���
	RECV_REQ_TENDER_CREATE,	 //������ǰ ���� ��û	 [��������][char* ��ǰ�̸�][int ����][int �����ڼ�]
	SEND_TENDER_CREATE_RESULT, //������ǰ ���� ��û ���
	RECV_REQ_TENDER_LIST, //���� ����Ʈ ��û
	SEND_TENDER_LIST_RESULT, //���� ����Ʈ ��û ���
	RECV_REQ_TENDER_PARTICIPATE, //���� ��û
	SEND_TENDER_PARTICIPATE_RESULT, //���� ��û ���
	SEND_TENDER_END_RESULT //���� ���� ��� [��������][char* �޼���]
};

enum RESULT { 
	// �α��θŴ��� ���
	RT_LOGINMENU = 100, 		   // �α��� �Ŵ�
	RT_JOINMENU, 				   // ȸ������ �Ŵ�
	RT_MEMBER_LEAVE, 			   // 
	RT_LOGOUT, 					   // 
	RT_USER_DISCONNECT,			   // 
	RT_ID_OVERLAP_SUCCESS, 		   // ID �ߺ� üũ ��� �ߺ�������
	RT_ID_OVERLAP_FAIL, 		   // ID �ߺ� üũ ��� �ߺ�������
	RT_JOIN_MENU_EXIT,			   // ȸ������ ��� �϶�
	RT_JOIN, 					   // ȸ������ �����϶�
	RT_JOIN_FAIL, 				   // ȸ������ �����϶�
	RT_LOGIN, 					   // �α��� �����϶�
	RT_LOGINFAIL,				   // �α��� �����϶�

	// ĳ���͸Ŵ��� ���
	RT_CHARACTER_SLOTRESULT = 200,		// ĳ���� ���԰��
	RT_CHARACTER_ENTERGAME_SUCCESS,		// ���� ���� ����
	RT_CHARACTER_ENTERGAME_FAIL,		// ���� ���� ����
	RT_CHARACTER_DELETE,				// ĳ���� ����
	RT_CHARACTER_ENTERCREATE, 			// ĳ���� ���� ȭ������ �̵�
	RT_CHARACTER_CREATE,				// ĳ���� ���� 
	RT_CHARACTER_CREATE_SUCCESS,		// ĳ���� ���� ����
	RT_CHARACTER_CREATE_FAIL,			// ĳ���� ���� ����
	RT_CHARACTER_NICKOVERLAP_TRUE,		// �г��� �ߺ�
	RT_CHARACTER_EXIT,					// ���� ���

	// �ΰ��ӸŴ��� ���
	RT_INGAME_MOVE = 300,				// �̵�
	RT_INGAME_OTHERPLAYER_INFO,			// �ٸ� �÷��̾� ����
	RT_INGAME_OTHERPLAYER_LIST,			// �ٸ� �÷��̾� ����Ʈ
	RT_INGAME_CHANNEL_INFO,				// ä�� ����
	RT_INGAME_CHANNEL_CHANGE,			// ä�� �̵�
	RT_INGAME_OTHERPLAYER_LEAVE,		// �ٸ� ������ ��������
	RT_INGAME_MENU_CHARACTER,			// ĳ���� ����ȭ��
	RT_INGAME_MENU_LOGOUT,				// �α׾ƿ�
	RT_INGAME_MENU_EXIT,				// ����
	RT_INGAME_PARTY_INVITE,				// ��Ƽ �ʴ�
	RT_INGAME_PARTY_INVITE_RESULT,		// ��Ƽ �ʴ� ���
	RT_INGAME_PARTY_JOIN_RESULT,		// ��Ƽ ���� ���
	RT_INGAME_PARTY_ADD_USER,			// ��Ƽ�� ����
	RT_INGAME_PARTY_KICK,				// ��Ƽ ����
	RT_INGAME_PARTY_KICK_USER_INFO,		// ��Ƽ ���� ������ ������ �޾�����
	RT_INGAME_PARTY_KICK_RESULT,		// ��Ƽ ���� ���
	RT_INGAME_PARTY_LEAVE_INFO,			// Ż���ϴ� ��������
	RT_INGAME_PARTY_LEAVE_RESULT,		// Ż�� ���
	RT_INGAME_PARTY_ROOM_REMOVE			// ��Ƽ�� ���Ľ�

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
//#define SERVERIP "192.168.0.141"	// 402ip ���� �׷���Ʈ��
//#define SERVERIP "192.168.0.136"	// 202ip ���� �׷���Ʈ��
//#define SERVERIP "192.168.0.134"	// 202ip ȣ����Ʈ��
//#define SERVERIP "192.168.0.154"	// 402ip ȣ����Ʈ��
//#define SERVERIP "192.168.0.166"	// 302ip ȣ����Ʈ��
#define SERVERIP "192.168.43.58"	// ȣ���ֽ��� ȣ����Ʈ��
//#define SERVERIP "172.30.35.30"	// KT Free Wifi ȣ����Ʈ��
//#define SERVERIP "192.168.43.180"	// ȣ���ֽ��� ���ر׷���Ʈ��
//#define SERVERIP "127.0.43.180"
//#define SERVERIP "192.168.123.181"
//#define SERVERIP "182.227.211.86"
//#define SERVERIP "192.168.0.134"

#endif
