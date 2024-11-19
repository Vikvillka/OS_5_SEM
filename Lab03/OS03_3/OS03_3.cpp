#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

void PrintProcessList() {
    // ������� ������ �������� ��������� �������
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) {
        cout << "Error creating snapshot: " << GetLastError() << endl;
        return;
    }

    // �������������� ��������� ��� �������� ���������� � ��������
    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);

    // �������� ���������� � ������ ��������
    if (!Process32First(hSnapshot, &pe32)) {
        cout << "Error getting first process: " << GetLastError() << endl;
        CloseHandle(hSnapshot);
        return;
    }

    // ���������� ��� �������� � ������� ���������� � ������
    do {
        wcout << left << setw(8) << pe32.th32ProcessID
            << setw(40) << pe32.szExeFile << endl;
    } while (Process32Next(hSnapshot, &pe32));

    // ��������� ���������� ������ �������
    CloseHandle(hSnapshot);
}

int main() {
    PrintProcessList();
    return 0;
}