#include <iostream>
#include <windows.h>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

#define FILE_PATH L"D:/5_SEM_LABS/OS/lab09/OS09/OS09_01.txt"
#define DIRECTORY_PATH L"D:/5_SEM_LABS/OS/lab09/OS09/"

DWORD getLineCount(LPWSTR fileName) {
    ifstream file(fileName);
    DWORD lineCount = 0;
    string line;
    while (getline(file, line)) {
        lineCount++;
    }
    return lineCount;
}

void watchFile(LPWSTR fileName, DWORD mlsec) {
    HANDLE hDir = CreateFile(
        DIRECTORY_PATH,
        FILE_LIST_DIRECTORY,
        FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
        NULL,
        OPEN_EXISTING,
        FILE_FLAG_BACKUP_SEMANTICS,
        NULL
    );

    if (hDir == INVALID_HANDLE_VALUE) {
        cerr << "Error opening directory handle." << endl;
        return;
    }

    DWORD startTime = GetTickCount();
    DWORD initialLineCount = getLineCount(fileName);
    cout << "Initial line count: " << initialLineCount << endl;

    char buffer[1024];
    DWORD bytesReturned;

    while (true) {
        if (GetTickCount() - startTime >= mlsec) {
            cout << "Timer expired." << endl;
            break;
        }

        if (ReadDirectoryChangesW(
            hDir,
            &buffer,
            sizeof(buffer),
            FALSE,
            FILE_NOTIFY_CHANGE_SIZE | FILE_NOTIFY_CHANGE_LAST_WRITE,
            &bytesReturned,
            NULL,
            NULL
        )) {
            FILE_NOTIFY_INFORMATION* pNotify = (FILE_NOTIFY_INFORMATION*)buffer;

            do {
                if (pNotify->Action == FILE_ACTION_MODIFIED) {
                    DWORD newLineCount = getLineCount(fileName);
                    if (newLineCount != initialLineCount) {
                        cout << "Line count changed: " << newLineCount << endl;
                        initialLineCount = newLineCount;
                    }
                }
                pNotify = pNotify->NextEntryOffset ? (FILE_NOTIFY_INFORMATION*)((char*)pNotify + pNotify->NextEntryOffset) : NULL;
            } while (pNotify);
        }

        Sleep(100); 
    }

    CloseHandle(hDir);
}

int main() {
    LPWSTR fileName = (LPWSTR)FILE_PATH;
    DWORD monitorTime = 10000;

    watchFile(fileName, monitorTime);

    return 0;
}