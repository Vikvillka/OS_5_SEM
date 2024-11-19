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
    cout << "Объем виртуальной памяти:     " << ms.dwTotalVirtual / KB << " KB\n";
    cout << "Доступно виртуальной памяти:  " << ms.dwAvailVirtual / KB << " KB\n\n";
}


/*
    Б - 194(10) - C2(16)
    ы - 251(10) - FB(16)
    ч - 247(10) - F7(16)

    Страница с2 = 194


    FBF = (15 * 16^2) + (11 * 16^1) + (15 * 16^0) = 4031

    Смещение FBF = 4031(10) = 0xFBF
*/

int main()
{
    setlocale(LC_ALL, "ru");
    int pages = 256;
    int countItems = pages * PG / sizeof(int);
    SYSTEM_INFO system_info;
    GetSystemInfo(&system_info);

    cout << "\t    Изначально в системе\n";
    saymem();

    LPVOID xmemaddr = VirtualAlloc(NULL, pages * PG, MEM_COMMIT, PAGE_READWRITE);  
    cout << "\tВыделено " << pages * PG / 1024 << " KB вирт. памяти\n";
    saymem();

    int* arr = (int*)xmemaddr;
    for (int i = 0; i < countItems; i++)
        arr[i] = i;

    int* byte = arr + 194 * 1024 + 4031;
    cout << "------  Значение памяти в байте: " << *byte << "  ------\n";

    VirtualFree(xmemaddr, NULL, MEM_RELEASE) ? cout << "\tВиртуальная память освобождена\n" : cout << "\tВиртуальная память не освобождена\n";
    saymem();
}