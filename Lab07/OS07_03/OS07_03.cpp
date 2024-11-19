#include <iostream>
#include <Windows.h>
#include <ctime>

using namespace std;

HANDLE printTimer;  
HANDLE closeTimer; 
volatile bool printFlag = false;  

DWORD WINAPI printTimerWatcher(LPVOID lpParam) {
    while (true) {
        WaitForSingleObject(printTimer, INFINITE);
        printFlag = true;  
    }
    return 0;
}

DWORD WINAPI closeTimerWatcher(LPVOID lpParam) {
    WaitForSingleObject(closeTimer, INFINITE);
    return 0;
}

int main() {
   
    printTimer = CreateWaitableTimer(NULL, FALSE, NULL);
    closeTimer = CreateWaitableTimer(NULL, FALSE, NULL);

    
    LARGE_INTEGER printInterval;
    printInterval.QuadPart = -30000000LL; 
    SetWaitableTimer(printTimer, &printInterval, 3000, NULL, NULL, FALSE);

   
    LARGE_INTEGER closeTimeout;
    closeTimeout.QuadPart = -150000000LL;
    SetWaitableTimer(closeTimer, &closeTimeout, 0, NULL, NULL, FALSE);

   
    HANDLE printThread = CreateThread(NULL, 0, printTimerWatcher, NULL, 0, NULL);
    HANDLE closeThread = CreateThread(NULL, 0, closeTimerWatcher, NULL, 0, NULL);

    int counter = 0;
    clock_t start = clock();
    while (true) {
        counter++; 

       
        if (printFlag) {
            cout << "Iterations: " << counter << endl;
            printFlag = false;  
        }

        if ((clock() - start) / CLOCKS_PER_SEC >= 15) {
            cout << "Final Iterations: " << counter << endl;
            break;  
        }
    }

    WaitForSingleObject(printThread, INFINITE);
    WaitForSingleObject(closeThread, INFINITE);
    CloseHandle(printThread);
    CloseHandle(closeThread);
    CloseHandle(printTimer);
    CloseHandle(closeTimer);

    return 0;
}