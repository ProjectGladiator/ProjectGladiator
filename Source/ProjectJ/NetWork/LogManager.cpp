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

	ofstream w_log("Log.txt", ios::out);
	
	//if (w_log.is_open() == false)
	//{
	//	w_log.open("Log.txt", ofstream::app);
	//}
	//else
	//{
	//	w_log.open("Log.txt", ofstream::app);
	//}

	SetTime();
	char buf[12];
	sprintf(buf, "[%d:%d:%d]", time.wHour, time.wMinute, time.wSecond);
	w_log << buf << ":" << _msg << endl;

	w_log.close();
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
	
	while (!r_log.eof())	//�� ���������� ����
	{
		r_log >> temp;
		cout << temp << endl;
	}

	r_log.close();
}
