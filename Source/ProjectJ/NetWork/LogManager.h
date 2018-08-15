#pragma once
#ifndef _LOG_MANAGER_
#define _LOG_MANAGER_

#include "Global.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class LogManager
{
private:
	static LogManager* Instance;

	SYSTEMTIME time;

	LogManager();
	~LogManager();
public:
	static void CreateInstance();
	static LogManager* GetInstance();
	static void DestroyInstance();

	bool InitializeManager();
	void EndManager();

	void SetTime();
	void LogWrite(char* _msg);
	void LogRead();
};

#endif // !_LOG_MANAGER_
