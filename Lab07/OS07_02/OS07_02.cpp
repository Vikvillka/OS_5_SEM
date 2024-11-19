#include <Windows.h>
#include <iostream>
#include <ctime>

using namespace std;

int main()
{
	clock_t start = clock();
	int k = 0;
	bool flag5 = true, flag10 = true;

	while (true)
	{
		k++;
		if ((clock() - start) / CLOCKS_PER_SEC == 5 && flag5) {
			cout << "After 5s: " << k << '\n';
			flag5 = false;
			cout << "---------------------------------" << '\n';
		}
		if ((clock() - start) / CLOCKS_PER_SEC == 10 && flag10) {
			cout << "After 10s: " << k << '\n';
			flag10 = false;
			cout << "---------------------------------" << '\n';
		}
		if ((clock() - start) / CLOCKS_PER_SEC == 15) {
			cout << "After 15s: " << k << '\n';
			cout << "---------------------------------" << '\n';
			break;
		}
	}

	return 0;
}