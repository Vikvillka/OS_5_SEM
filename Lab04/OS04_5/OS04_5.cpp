#include <iostream>
#include <Windows.h>

using namespace std;

DWORD pid = NULL;
bool running_T2 = true;

DWORD WINAPI ChildThread_T1()
{
	DWORD tid = GetCurrentThreadId();

	for (short i = 1; i <= 50; ++i)
	{
		cout << i << ". PID = " << pid << "\t\t[CHILD-1]   TID = " << tid << "\n";
		Sleep(1000);
	}
	return 0;
}


DWORD WINAPI ChildThread_T2()
{
	DWORD tid = GetCurrentThreadId();
	for (short i = 1; i <= 125 && running_T2; ++i) 
	{
		cout << i << ". PID = " << pid << "\t\t[CHILD-2]   TID = " << tid << "\n";
		Sleep(1000);
	}
	return 0;
}


int main()
{
	pid = GetCurrentProcessId();
	DWORD parentId = GetCurrentThreadId();
	DWORD childId_T1 = NULL;
	DWORD childId_T2 = NULL;
	HANDLE handleClild_T1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ChildThread_T1, NULL, NULL, &childId_T1);
	HANDLE handleClild_T2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ChildThread_T2, NULL, NULL, &childId_T2);

	for (short i = 1; i <= 100; ++i)
	{
		if (i == 5) 
			running_T2 = false; 

		cout << i << ". PID = " << pid << "\t\t[PARENT]    TID = " << parentId << "\n";
		Sleep(1000);
	}

	WaitForSingleObject(handleClild_T1, INFINITE);
	WaitForSingleObject(handleClild_T2, INFINITE);

	CloseHandle(handleClild_T1);
	CloseHandle(handleClild_T2);
	system("pause");
	return 0;
}