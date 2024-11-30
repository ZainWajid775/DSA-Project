#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

int main() {
    for (int i = 0; i <= 100; i++) {
        cout << "\rProgress: " << i << "%" << flush;  // Use '\r' to overwrite the line
        this_thread::sleep_for(chrono::milliseconds(50)); // Simulate work
    }
    cout << endl;  // Move to the next line after completion
    return 0;
}
