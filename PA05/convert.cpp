#include <iostream>
#include <string>
#include <unordered_map> //required for unordered map (hashmap)
#include <algorithm> //required for reverse
#include <cmath> //required for abs

const std::unordered_map<char, int> chars = {
    {'0', 0}, {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5}, {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9},
    {'A', 10}, {'B', 11}, {'C', 12}, {'D', 13}, {'E', 14}, {'F', 15}
};
const std::unordered_map<int, char> ints = {
    {0, '0'}, {1, '1'}, {2, '2'}, {3, '3'}, {4, '4'}, {5, '5'}, {6, '6'}, {7, '7'}, {8, '8'}, {9, '9'},
    {10, 'A'}, {11, 'B'}, {12, 'C'}, {13, 'D'}, {14, 'E'}, {15, 'F'}
};

int char2int(char digit){
    //if char is entered not in hashmap
    if(chars.find(digit) == chars.end()){
        return -1;
    }
    //returns the other element of the pair
    else return chars.at(digit);
}
char int2char(int digit){
    //if digit is not in hashmap
    if(ints.find(digit) == ints.end()){
        return 'X';
    }
    //returns other element of the pair
    else return ints.at(digit);
}
void int2ascii(int value, int base){
    //tracker vars
    bool isNeg = false;
    std::string str = "";

    if (value == 0) {
        std::cout << "0" << std::endl; //edge case of only 0
        return;
    }
    //handling for negatives
    if(value < 0){
        isNeg = true;
        value = std::abs(value);
    }
    while(value > 0){
        str += int2char(value % base);
        value /= base;
    }
    //adding back negative sign to the string if applicable
    if(isNeg){
        str += "-";
    }

    // Reverse the string in-place
    std::reverse(str.begin(), str.end());
    std::cout << str;

}
void ascii2int(const std::string &ascii, int base){

    //tracking vars
    bool isNeg = false;
    int tracker = 0;
    size_t startIndex = 0;

    if(ascii.front() == '-'){
        isNeg = true; 
        startIndex = 1; //start the loop at index 1 to skip the '-'
    }

    //process only the actual digit characters
    for(size_t i = startIndex; i < ascii.length(); ++i){
        int digitValue = char2int(ascii[i]);

         tracker = (tracker * base) + digitValue;
    }
    if(isNeg){
        tracker *= -1; //flip back to neg if applicable
    }

        std::cout << tracker;
}