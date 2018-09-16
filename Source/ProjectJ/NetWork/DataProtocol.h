#ifndef _DATA_PROTOCOL_H_
#define _DATA_PROTOCOL_H_

namespace DataProtocol {
	// �α��� ��������
	enum PLOGINDATA { 
		PLOGIN_LOGIN_RESULT = 0, 	   // �α��� ���
		PLOGIN_IDOVERLAP_RESULT,	   // ���̵��ߺ�üũ ���
		PLOGIN_JOIN_RESULT			   // ȸ������ ���
	};
	// ĳ���� ��������
	enum PCHARACTERDATA {
		PCHARACTERDATA_INFO = 0,		// �̵� ����
		PCHARACTERDATA_SLOT_INFO,		// ���� ���
		PCHARACTERDATA_CREATE_RESULT	// ĳ���� ���� ���
	};
	// �ΰ��� ��������
	enum PGAMEDATA {
		PGAMEDATA_PLAYER_MOVE_INFO = 0
	};
	// ���� ��������
	enum PGLOBAL { 
		CONFIRM = 0 
	};
}
#endif