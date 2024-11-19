#include <iostream>
#include <Windows.h>
using namespace std;

int main(){
	STARTUPINFO si1; // создание структуры процесса
	PROCESS_INFORMATION pi1;
	STARTUPINFO si2;
	PROCESS_INFORMATION pi2;
	ZeroMemory(&si1, sizeof(si1)); // установка в ноль и указание размера
	ZeroMemory(&si2, sizeof(si2));
	si1.cb = sizeof(si1);
	si2.cb = sizeof(si2);
	ZeroMemory(&pi1, sizeof(pi1));
	ZeroMemory(&pi2, sizeof(pi2));

	BOOL bRes1 = CreateProcessW(
		L"D:\\5_SEM_LABS\\OS\\Lab03\\Debug\\OS03_2_1.exe",
		NULL,        //lpCommandLine:    параметры коммандной строки
		NULL,        // lpProcessAttributes: может ли возвращаемый дескриптор быть унаследован дочерними процессами (null - нельзя наследовать)
		NULL,        // lpThreadAttributes:  может ли возвращаемый дескриптор быть унаследован дочерними потоками (null - нельзя наследовать)
		FALSE,        // bInheritHandles:    true - каждый возвращаемый дескриптор наследуется дочерним процессом; false - не наследуется
		CREATE_NEW_CONSOLE, // dwCreationFlags:    флаги, управляющие приоритетом и параметрами процесса; конкретно этот создает новый инстанс консоли
		NULL,        // lpEnvironment:    блок конфигурации нового процесса (пары ключ-значение); если null, то конфигурация наследуется от родителя
		NULL,        // lpCurrentDirectory:  полный путь дочернего процесса; если null, то процесс создается в каталоге родительского процесса
		&si1,        // lpStartupInfo:    структура STARTUPINFO (внешний вид окна)
		&pi1        // lpProcessInfo:    структура PROCESS_INFORMATION (дескрипторы процесса и первичного потока)
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
//    STARTUPINFO si1;                // структура для определения внешнего вида окна для нового процесса  (ширина и высота окна, его смещение, заголовок)
//    STARTUPINFO si2;
//   
//    PROCESS_INFORMATION pi1;            // структура с инфой о созданном процессе и его первичном потоке
//    PROCESS_INFORMATION pi2;
//    ZeroMemory(&si1, sizeof(STARTUPINFO));      // обнуление памяти STARTUPINFO
//    ZeroMemory(&si2, sizeof(STARTUPINFO));
//    
//    si1.cb = sizeof(STARTUPINFO);          // явное указание размера структуры si в байтах
//    si1.dwFlags = STARTF_USEFILLATTRIBUTE;      // флаг для возможности работы dwFillAttribute
//    si1.dwFillAttribute = (DWORD)FOREGROUND_GREEN;  // параметр цвета текста
//    si1.lpReserved = NULL;              // lpReserved рекомендуется установить в null перед передачей si в CreateProcess
//    si2.cb = sizeof(STARTUPINFO);
//    si2.dwFlags = STARTF_USEFILLATTRIBUTE;
//    si2.dwFillAttribute = (DWORD)FOREGROUND_RED;
//    si1.lpReserved = NULL;
//
//
//    if (CreateProcess(
//        OS03_02_1,      // lpApplicationName:  имя исполняемого модуля - exe иди другой тип (MS-DOS или OS/2)
//        NULL,        // lpCommandLine:    параметры коммандной строки
//        NULL,        // lpProcessAttributes: может ли возвращаемый дескриптор быть унаследован дочерними процессами (null - нельзя наследовать)
//        NULL,        // lpThreadAttributes:  может ли возвращаемый дескриптор быть унаследован дочерними потоками (null - нельзя наследовать)
//        FALSE,        // bInheritHandles:    true - каждый возвращаемый дескриптор наследуется дочерним процессом; false - не наследуется
//        CREATE_NEW_CONSOLE, // dwCreationFlags:    флаги, управляющие приоритетом и параметрами процесса; конкретно этот создает новый инстанс консоли
//        NULL,        // lpEnvironment:    блок конфигурации нового процесса (пары ключ-значение); если null, то конфигурация наследуется от родителя
//        NULL,        // lpCurrentDirectory:  полный путь дочернего процесса; если null, то процесс создается в каталоге родительского процесса
//        &si1,        // lpStartupInfo:    структура STARTUPINFO (внешний вид окна)
//        &pi1))        // lpProcessInfo:    структура PROCESS_INFORMATION (дескрипторы процесса и первичного потока)
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
//    WaitForSingleObject(pi1.hProcess, INFINITE);  // бесконечно будет ожидаться завершение программы до момента, 
//    WaitForSingleObject(pi2.hProcess, INFINITE);  // пока оба дочерних процесса не пошлют сигнал о завершении работы
//    CloseHandle(pi1.hThread);  // CloseHandle закрывает дескрипторы в структуре PROCESS_INFORMATION
//    CloseHandle(pi2.hThread);
//    CloseHandle(pi1.hProcess);  // Явно закрываются первичный поток и процесс
//    CloseHandle(pi2.hProcess);
//    return 0;
//}
//
//
//// CMD: tasklist /FI "IMAGENAME eq OS03_02*"
