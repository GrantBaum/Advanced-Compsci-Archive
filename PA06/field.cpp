#include "field.h"

int getBit (int value, int position){
    //error check
    if(position < 0 || position > 31){
        //dont do anything and return angry
        return -1;
    }
    //working with an unsigned int for value and mask
    unsigned int x = static_cast<unsigned int>(value);
    unsigned int mask = 1u << position;

    //if there is a one anywhere it means the bit of interest was a one
    if((x & mask) != 0){
        return 1;
    }
    else return 0;
}
int setBit (int value, int position){
    //error check
    if(position < 0 || position > 31){
        //return angry AGAIN
        return -1;
    }
    //working with unsigned ints but this time i need to cast back
    unsigned int x = static_cast<unsigned int>(value);
    unsigned int mask = 1u << position;

    //set bit of interest to 1 with binary or
    x |= mask;

    //recast and return
    return static_cast<int>(x);
}
int clearBit (int value, int position){
    //error check
    if(position < 0 || position > 31){
        //mad. upset. pissed even.
        return -1;
    }
    unsigned int x = static_cast<unsigned int>(value);
    unsigned int mask = 1u << position;

    //invert mask then use and to set only bits of interest to zero
    x &= ~mask;

    return static_cast<int>(x);
}

int getField (int value, int hi, int lo, int isSigned) {
    return 0;
}

int setField (int oldValue, int hi, int lo, int newValue) {
    return 0;
}

int fieldFits (int value, int width, int isSigned) {
    return 0;
}