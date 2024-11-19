#include <iostream>
#include <ctime>
#include <windows.h>

using namespace std;

int main() {
    const wchar_t* childProcessPath = L"D:\\5_SEM_LABS\\OS\\Lab07\\x64\\Debug\\OS07_04x.exe";

    STARTUPINFO si1 = { sizeof(si1) };
    PROCESS_INFORMATION pi1;
    wchar_t args1[] = L"OS07_04x.exe 60";

    if (!CreateProcessW(childProcessPath, args1, nullptr, nullptr, FALSE, CREATE_NEW_CONSOLE, nullptr, nullptr, &si1, &pi1)) {
        cerr << "Error in child process 1: " << GetLastError() << endl;
        return 1;
    }
    clock_t startTime1 = clock();  

    STARTUPINFO si2 = { sizeof(si2) };
    PROCESS_INFORMATION pi2;
    wchar_t args2[] = L"OS07_04x.exe 120";

    if (!CreateProcessW(childProcessPath, args2, nullptr, nullptr, FALSE, CREATE_NEW_CONSOLE, nullptr, nullptr, &si2, &pi2)) {
        cerr << "Error in child process 2: " << GetLastError() << endl;
        return 1;
    }
    clock_t startTime2 = clock(); 

    WaitForSingleObject(pi1.hProcess, INFINITE);
    clock_t endTime1 = clock();  

    WaitForSingleObject(pi2.hProcess, INFINITE);
    clock_t endTime2 = clock();

    double duration1 = double(endTime1 - startTime1) / CLOCKS_PER_SEC;
    cout << "Child process 1 finished. Time taken: " << duration1 << " seconds." << endl;

    double duration2 = double(endTime2 - startTime2) / CLOCKS_PER_SEC;
    cout << "Child process 2 finished. Time taken: " << duration2 << " seconds." << endl;
    CloseHandle(pi1.hProcess);
    CloseHandle(pi1.hThread);
    CloseHandle(pi2.hProcess);
    CloseHandle(pi2.hThread);

    cout << "All processes are over." << endl;
    return 0;
}