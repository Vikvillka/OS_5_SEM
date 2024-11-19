#include <iostream>
#include <Windows.h>

using namespace std;

#define KB (1024)
#define MB (1024 * KB)
#define PG (4 * KB)


void saymem()
{
    MEMORYSTATUS ms;
    GlobalMemoryStatus(&ms);
    cout << "����� ����������� ������:     " << ms.dwTotalVirtual / KB << " KB\n";
    cout << "�������� ����������� ������:  " << ms.dwAvailVirtual / KB << " KB\n\n";
}


/*
    � - 194(10) - C2(16)
    � - 251(10) - FB(16)
    � - 247(10) - F7(16)

    �������� �2 = 194


    FBF = (15 * 16^2) + (11 * 16^1) + (15 * 16^0) = 4031

    �������� FBF = 4031(10) = 0xFBF
*/

int main()
{
    setlocale(LC_ALL, "ru");
    int pages = 256;
    int countItems = pages * PG / sizeof(int);
    SYSTEM_INFO system_info;
    GetSystemInfo(&system_info);

    cout << "\t    ���������� � �������\n";
    saymem();

    LPVOID xmemaddr = VirtualAlloc(NULL, pages * PG, MEM_COMMIT, PAGE_READWRITE);  
    cout << "\t�������� " << pages * PG / 1024 << " KB ����. ������\n";
    saymem();

    int* arr = (int*)xmemaddr;
    for (int i = 0; i < countItems; i++)
        arr[i] = i;

    int* byte = arr + 194 * 1024 + 4031;
    cout << "------  �������� ������ � �����: " << *byte << "  ------\n";

    VirtualFree(xmemaddr, NULL, MEM_RELEASE) ? cout << "\t����������� ������ �����������\n" : cout << "\t����������� ������ �� �����������\n";
    saymem();
}