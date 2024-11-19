#include <Windows.h>
#include <iostream>
#include <string>

using namespace std;

#define FILE_PATH L"D:/5_SEM_LABS/OS/lab09/OS09/OS09_01.txt"
#define READ_BYTES 300

string getFileName(wchar_t* filePath)
{
    wstring ws(filePath);
    string filename(ws.begin(), ws.end());
    const size_t last_slash_idx = filename.find_last_of("\\/");
    if (string::npos != last_slash_idx)
        filename.erase(0, last_slash_idx + 1);
    return filename;
}

LPCWSTR getFileType(HANDLE file)
{
    switch (GetFileType(file))
    {
    case FILE_TYPE_UNKNOWN:
        return L"FILE_TYPE_UNKNOWN";
    case FILE_TYPE_DISK:
        return L"FILE_TYPE_DISK";
    case FILE_TYPE_CHAR:
        return L"FILE_TYPE_CHAR";
    case FILE_TYPE_PIPE:
        return L"FILE_TYPE_PIPE";
    case FILE_TYPE_REMOTE:
        return L"FILE_TYPE_REMOTE";
    default:
        return L"[ERROR]: WRITE FILE TYPE";
    }
}

BOOL printFileInfo(LPWSTR path)
{
    HANDLE file = CreateFile(
        path,
        GENERIC_READ,
        NULL,
        NULL,
        OPEN_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    SYSTEMTIME sysTime;
    FILETIME localTime;
    BY_HANDLE_FILE_INFORMATION fi;
    BOOL fResult = GetFileInformationByHandle(file, &fi);
    if (fResult)
    {
        cout << "File name:\t" << getFileName((wchar_t*)FILE_PATH);
        wcout << "\nFile type:\t" << getFileType(file);
        cout << "\nFile size:\t" << fi.nFileSizeLow << " bytes";
        FileTimeToLocalFileTime(&fi.ftCreationTime, &localTime);
        FileTimeToSystemTime(&localTime, &sysTime);
        printf("\nCreate time:\t%02d.%02d.%04d %02dh %02dm %02ds", sysTime.wDay, sysTime.wMonth, sysTime.wYear, sysTime.wHour % 24, sysTime.wMinute, sysTime.wSecond);
        FileTimeToLocalFileTime(&fi.ftLastWriteTime, &localTime);
        FileTimeToSystemTime(&localTime, &sysTime);
        printf("\nUpdate time:\t%02d.%02d.%04d %02dh %02dm %02ds", sysTime.wDay, sysTime.wMonth, sysTime.wYear, sysTime.wHour % 24, sysTime.wMinute, sysTime.wSecond);
    }
    CloseHandle(file);
    return true;
}

BOOL printFileTxt(LPCWSTR path)
{
    HANDLE file = CreateFile(
        path,
        GENERIC_READ,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (file != INVALID_HANDLE_VALUE) {
       
        char buffer[1024];
        DWORD bytesRead;
        while (ReadFile(file, buffer, sizeof(buffer) - 1, &bytesRead, NULL) && bytesRead > 0) {
            buffer[bytesRead] = '\0';
            cout << buffer;
        }

        CloseHandle(file);
        return TRUE;
    }
    else {
        cerr << "[ERROR]: open file" << endl;
        return FALSE;
    }
}

int main()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    LPWSTR path = (LPWSTR)FILE_PATH;
   
    printFileInfo(path);
    cout <<'\n' << endl;
   
    printFileTxt(path);
    

    return 0;
}