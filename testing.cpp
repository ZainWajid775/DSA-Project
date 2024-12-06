#include <iostream>
#include <string>

using namespace std;

int main() {
    string str1 = "Hello";
    string str2 = "World";
    string separator = ", "; // Separator between the two strings

    // Joining the strings with the separator
    string result = str1 + separator + str2;

    cout << result << endl;  // Output: Hello, World

    return 0;
}
