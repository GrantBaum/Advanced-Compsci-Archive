#include <iostream>
#include <string>
#include <unordered_map>

const std::unordered_map<char, int> hash = {
    {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5}, {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9},
    {'A', 10}, {'B', 11}, {'C', 12}, {'D', 13}, {'E', 14}, {'F', 15}
}

// char2int
int char2int(char digit)
{
    if(!hash.contains(digit)){
        return -1;
    }
    else return hash.at(digit);
}

// int2char
char int2char(int digit)
{
    if(!hash.contains(digit)){
        return 'X';
    }
    else return hash.at(digit);
}

// Convert integer to string in specified base and print
// 2 <= base <= 16
void int2ascii(int value, int base)
{
    return;
}

// Convert string in specified base to integer and print
// 2 <= base <= 16
void ascii2int(const std::string &ascii, int base)
{
    return;
}