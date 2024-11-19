#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <iostream>
#include <string>

using namespace std;

#define FILE_PATH L"D:/5_SEM_LABS/OS/lab09/OS09/OS09_01.txt"
#define READ_BYTES 500

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
		cerr << "Error open file" << endl;
		return FALSE;
	}
}


BOOL delRowFileTxt(LPWSTR fileName, DWORD row)
{
	char filepath[20];
	filepath[19] = '\0';
	wcstombs(filepath, fileName, 20);
	cout << "\n Delete row: " << row << "\n";

	try
	{
		HANDLE hf = CreateFile(fileName, GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hf == INVALID_HANDLE_VALUE)
		{
			CloseHandle(hf);
			throw "[ERROR] Create or open file failed";
		}

		DWORD n = NULL;
		char buf[1024];
		BOOL b;

		ZeroMemory(buf, sizeof(buf));
		b = ReadFile(hf, &buf, sizeof(buf), &n, NULL);
		if (!b)
		{
			CloseHandle(hf);
			throw ("[ERROR] Read file unsuccessful");
		}
		cout << "\nBEFORE:\n";
		cout << buf << endl;
		CloseHandle(hf);

		HANDLE hAppend = CreateFile(fileName, GENERIC_WRITE, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		char editedBuf[1024];
		ZeroMemory(editedBuf, sizeof(editedBuf));

		int line = 1;
		int j = 0;
		bool rowFound = false;
		for (int i = 0; i < n; i++)
		{
			if (line == row)
				rowFound = true;
			else
			{
				editedBuf[j] = buf[i];
				j++;
			}

			if (buf[i] == '\n')
				line++;
		}
		if (!rowFound)
		{
			CloseHandle(hAppend);
			throw ("[ERROR] Can't find this row.\n");
		}

		b = WriteFile(hAppend, editedBuf, n, &n, NULL);
		if (!b)
		{
			CloseHandle(hAppend);
			throw ("[ERROR] Write file unsuccessful\n");
		}
		cout << "\nAFTER:\n";
		cout << editedBuf << endl;
		CloseHandle(hAppend);
		cout << "\n==========================================\n";
		return true;
	}
	catch (const char* em)
	{
		cout << em << " \n";
		cout << "==========================================\n";
		return false;
	}
}


int main()
{
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);

	LPWSTR file = (LPWSTR)FILE_PATH;

	delRowFileTxt(file, 1);
	delRowFileTxt(file, 3);
	delRowFileTxt(file, 8);
	delRowFileTxt(file, 10);

	printFileTxt(file);

	return 0;
}