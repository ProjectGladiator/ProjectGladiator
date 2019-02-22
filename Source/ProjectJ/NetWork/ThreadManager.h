#ifndef THREAD_MANAGER_H
#define THREAD_MANAGER_H
#include "Global.h"
#include <list>
using namespace std;

struct ThreadData
{
	// 스레드 핸들, 스레드 함수 네임
	HANDLE thread;
	void* data;
};

class ThreadManager
{

private:
	static ThreadManager* Instance;
	list<ThreadData*> threadInfo;
	list<ThreadData*>::iterator save;

	ThreadManager();
	~ThreadManager();

public:
	static void CreateInstance();
	static ThreadManager* GetInstance();
	static void DestroyInstance();

	bool InitializeManager();
	void EndManager();

	HANDLE addThread(LPTHREAD_START_ROUTINE routine, LPVOID data, LPVOID _pthis);
	void removeThread(HANDLE thread);
	static DWORD WINAPI ThreadProcess(LPVOID arg);
	static DWORD WINAPI RecvProcess(LPVOID arg);
	void* getData(DWORD threadID);
	void startSearch();
	bool searchData(ThreadData*& data);

};

#endif
