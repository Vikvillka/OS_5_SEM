#include <iostream>
#include <Windows.h>
using namespace std;

int main(){
	STARTUPINFO si1; // �������� ��������� ��������
	PROCESS_INFORMATION pi1;
	STARTUPINFO si2;
	PROCESS_INFORMATION pi2;
	ZeroMemory(&si1, sizeof(si1)); // ��������� � ���� � �������� �������
	ZeroMemory(&si2, sizeof(si2));
	si1.cb = sizeof(si1);
	si2.cb = sizeof(si2);
	ZeroMemory(&pi1, sizeof(pi1));
	ZeroMemory(&pi2, sizeof(pi2));

	BOOL bRes1 = CreateProcessW(
		L"D:\\5_SEM_LABS\\OS\\Lab03\\Debug\\OS03_2_1.exe",
		NULL,        //lpCommandLine:    ��������� ���������� ������
		NULL,        // lpProcessAttributes: ����� �� ������������ ���������� ���� ����������� ��������� ���������� (null - ������ �����������)
		NULL,        // lpThreadAttributes:  ����� �� ������������ ���������� ���� ����������� ��������� �������� (null - ������ �����������)
		FALSE,        // bInheritHandles:    true - ������ ������������ ���������� ����������� �������� ���������; false - �� �����������
		CREATE_NEW_CONSOLE, // dwCreationFlags:    �����, ����������� ����������� � ����������� ��������; ��������� ���� ������� ����� ������� �������
		NULL,        // lpEnvironment:    ���� ������������ ������ �������� (���� ����-��������); ���� null, �� ������������ ����������� �� ��������
		NULL,        // lpCurrentDirectory:  ������ ���� ��������� ��������; ���� null, �� ������� ��������� � �������� ������������� ��������
		&si1,        // lpStartupInfo:    ��������� STARTUPINFO (������� ��� ����)
		&pi1        // lpProcessInfo:    ��������� PROCESS_INFORMATION (����������� �������� � ���������� ������)
	);
	BOOL bRes2 = CreateProcessW(
		L"D:\\5_SEM_LABS\\OS\\Lab03\\Debug\\OS03_2_2.exe",
		NULL,
		NULL,
		NULL,
		FALSE,
		CREATE_NEW_CONSOLE,  
		NULL,
		NULL,
		&si2,
		&pi2
	);

	for (short i = 1; i <= 100; ++i)
		    {
		        cout << i << ". PID = " << GetCurrentProcessId() << "\n";
		        Sleep(1000);
		    }

	if (!bRes1 || !bRes2)
		printf("Error %d\n", GetLastError());

	WaitForSingleObject(pi1.hProcess, INFINITE);
	WaitForSingleObject(pi2.hProcess, INFINITE);

	CloseHandle(pi1.hProcess);
	CloseHandle(pi1.hThread);
	CloseHandle(pi2.hProcess);
	CloseHandle(pi2.hThread);
}



//#include <iostream>
//#include <Windows.h>
//using namespace std;
//
//int main()
//{
//    cout << "====================  OS03_02  ====================\n\n";
//    
//
//    LPCWSTR OS03_02_1 = L"D:\\5_SEM_LABS\\OS\\Lab03\\Debug\\OS03_2_1.exe";
//    LPCWSTR OS03_02_2 = L"D:\\5_SEM_LABS\\OS\\Lab03\\Debug\\OS03_2_2.exe";
//   
//    STARTUPINFO si1;                // ��������� ��� ����������� �������� ���� ���� ��� ������ ��������  (������ � ������ ����, ��� ��������, ���������)
//    STARTUPINFO si2;
//   
//    PROCESS_INFORMATION pi1;            // ��������� � ����� � ��������� �������� � ��� ��������� ������
//    PROCESS_INFORMATION pi2;
//    ZeroMemory(&si1, sizeof(STARTUPINFO));      // ��������� ������ STARTUPINFO
//    ZeroMemory(&si2, sizeof(STARTUPINFO));
//    
//    si1.cb = sizeof(STARTUPINFO);          // ����� �������� ������� ��������� si � ������
//    si1.dwFlags = STARTF_USEFILLATTRIBUTE;      // ���� ��� ����������� ������ dwFillAttribute
//    si1.dwFillAttribute = (DWORD)FOREGROUND_GREEN;  // �������� ����� ������
//    si1.lpReserved = NULL;              // lpReserved ������������� ���������� � null ����� ��������� si � CreateProcess
//    si2.cb = sizeof(STARTUPINFO);
//    si2.dwFlags = STARTF_USEFILLATTRIBUTE;
//    si2.dwFillAttribute = (DWORD)FOREGROUND_RED;
//    si1.lpReserved = NULL;
//
//
//    if (CreateProcess(
//        OS03_02_1,      // lpApplicationName:  ��� ������������ ������ - exe ��� ������ ��� (MS-DOS ��� OS/2)
//        NULL,        // lpCommandLine:    ��������� ���������� ������
//        NULL,        // lpProcessAttributes: ����� �� ������������ ���������� ���� ����������� ��������� ���������� (null - ������ �����������)
//        NULL,        // lpThreadAttributes:  ����� �� ������������ ���������� ���� ����������� ��������� �������� (null - ������ �����������)
//        FALSE,        // bInheritHandles:    true - ������ ������������ ���������� ����������� �������� ���������; false - �� �����������
//        CREATE_NEW_CONSOLE, // dwCreationFlags:    �����, ����������� ����������� � ����������� ��������; ��������� ���� ������� ����� ������� �������
//        NULL,        // lpEnvironment:    ���� ������������ ������ �������� (���� ����-��������); ���� null, �� ������������ ����������� �� ��������
//        NULL,        // lpCurrentDirectory:  ������ ���� ��������� ��������; ���� null, �� ������� ��������� � �������� ������������� ��������
//        &si1,        // lpStartupInfo:    ��������� STARTUPINFO (������� ��� ����)
//        &pi1))        // lpProcessInfo:    ��������� PROCESS_INFORMATION (����������� �������� � ���������� ������)
//        cout << "[OK] Process OS03_2_1 was created.\n";
//    else cout << "[ERROR] Process OS03_2_1 was not created.\n";
//
//
//    if (CreateProcess(OS03_02_2, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si2, &pi2))
//        cout << "[OK] Process OS03_2_2 was created.\n\n";
//    else cout << "[ERROR] Process OS03_2_2 was not created.\n\n";
//
//
//    for (short i = 1; i <= 100; ++i)
//    {
//        cout << i << ". PID = " << GetCurrentProcessId() << "\n";
//        Sleep(1000);
//    }
//
//
//    WaitForSingleObject(pi1.hProcess, INFINITE);  // ���������� ����� ��������� ���������� ��������� �� �������, 
//    WaitForSingleObject(pi2.hProcess, INFINITE);  // ���� ��� �������� �������� �� ������ ������ � ���������� ������
//    CloseHandle(pi1.hThread);  // CloseHandle ��������� ����������� � ��������� PROCESS_INFORMATION
//    CloseHandle(pi2.hThread);
//    CloseHandle(pi1.hProcess);  // ���� ����������� ��������� ����� � �������
//    CloseHandle(pi2.hProcess);
//    return 0;
//}
//
//
//// CMD: tasklist /FI "IMAGENAME eq OS03_02*"
