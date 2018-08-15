#ifndef ERROR_MANAGER_H
#define ERROR_MANAGER_H

#include "Global.h"

class ErrorManager
{
private:
	static ErrorManager* Instance;

	ErrorManager();
	~ErrorManager();

public:
	static void CreateInstance();
	static ErrorManager* GetInstance();
	static void DestroyInstance();
	
	bool InitializeManager();
	void EndManager();

	void err_quit(const char *msg);
	void err_display(const char *msg);
};

#endif
