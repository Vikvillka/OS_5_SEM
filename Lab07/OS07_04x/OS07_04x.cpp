#include <iostream>
#include <chrono>
#include <thread>
#include <windows.h>

using namespace std;
using namespace chrono;

bool isPrime(int num) {
    if (num <= 1) return false;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    int duration = (argc > 1) ? atoi(argv[1]) : 60;
    auto start = steady_clock::now();
    int count = 0;
    int number = 2;

    while (true) {
        if (isPrime(number)) {
            cout << "Simple number: " << number << endl;
            count++;
        }
        number++;

        auto now = steady_clock::now();
        auto elapsed = duration_cast<seconds>(now - start).count();
        if (elapsed >= duration) {
            break;
        }

        this_thread::sleep_for(milliseconds(100));
    }

    cout << "Child process finished. Simple numbers: " << count << endl;

   
    return 0;
}