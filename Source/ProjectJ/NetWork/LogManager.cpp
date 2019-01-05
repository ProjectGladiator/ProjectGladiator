#include "LogManager.h"

LogManager* LogManager::Instance = nullptr;

LogManager::LogManager()
{

}
LogManager::~LogManager()
{

}

void LogManager::CreateInstance()
{
	if (Instance == nullptr)
	{
		Instance = new LogManager();
	}
}

LogManager * LogManager::GetInstance()
{
	return Instance;
}

void LogManager::DestroyInstance()
{
	if (Instance != nullptr)
	{
		delete Instance;
		Instance = nullptr;
	}
}

bool LogManager::InitializeManager()
{
	return true;
}

void LogManager::EndManager()
{

}

void LogManager::SetTime()
{
	GetLocalTime(&time);
}

void LogManager::LogWrite(char* _msg)
{

	ofstream w_log("Log.txt");

	//w_log.open("Log.txt", ofstream::app);
	if (w_log.is_open())
	{
		SetTime();
		char buf[12];
		sprintf(buf, "[%d:%d:%d]", time.wHour, time.wMinute, time.wSecond);
		w_log << buf << ":" << _msg << endl;

		w_log.close();
	}
	else
	{
		//w_log.open("Log.txt", ofstream::app);
	}
}

void LogManager::LogRead()
{
	fstream r_log;
	char temp[BUFSIZE];

	if (r_log.is_open())
	{
		return;
	}
	else
	{
		r_log.open("Log.txt", fstream::in);
	}
	
	while (!r_log.eof())	//다 읽을때까지 돌음
	{
		r_log >> temp;
		cout << temp << endl;
	}

	r_log.close();
}
