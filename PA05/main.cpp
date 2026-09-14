//You can edit this file to run your program and make more test cases.

#include <iostream>
#include "convert.h"

using namespace std;

int main() {
    // Base 16 (hexadecimal)
    int value = 1234;
    cout << value << " (base 10) = ";
    int2ascii(value, 16);
    cout << " (base 16)" << endl;

    string hexString = "ABCD";
    cout << hexString << " (base 16) = ";
    ascii2int(hexString.c_str(), 16);
    cout << " (base 10)" << endl;

    // Base 8 (octal)
    value = 1234;
    cout << value << " (base 10) = ";
    int2ascii(value, 8);
    cout << " (base 8)" << endl;

    string octalString = "4567";
    cout << octalString << " (base 8) = ";
    ascii2int(octalString.c_str(), 8);
    cout << " (base 10)" << endl;

    // Base 2 (binary)
    value = 1234;
    cout << value << " (base 10) = ";
    int2ascii(value, 2);
    cout << " (base 2)" << endl;

    string binaryString = "10011011";
    cout << binaryString << " (base 2) = ";
    ascii2int(binaryString.c_str(), 2);
    cout << " (base 10)" << endl;

    // Base 6 (unusual!)
    value = 1234;
    cout << value << " (base 10) = ";
    int2ascii(value, 6);
    cout << " (base 6)" << endl;

    string base6String = "4532";
    cout << base6String << " (base 6) = ";
    ascii2int(base6String.c_str(), 6);
    cout << " (base 10)" << endl;

    return 0;
}