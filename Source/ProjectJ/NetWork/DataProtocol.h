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
		PCHARACTERDATA_INFO = 0	// �̵� ����
	};
	// �ΰ��� ��������
	enum PGAMEDATA {
	
	};
	// ���� ��������
	enum PGLOBAL { 
		CONFIRM = 0 
	};
}
#endif