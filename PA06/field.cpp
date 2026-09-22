#include "field.h"
#include <stdio>
#include <stdexcept>

int getBit (int value, int position){
    //error check
    if(position < 0 || position > 31){
        //throw error
        throw std::runtime_error("entered position invalid for type int [4 bytes]");
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
        //throw error
        throw std::runtime_error("entered position invalid for type int [4 bytes]");
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
        //throw error
        throw std::runtime_error("entered position invalid for type int [4 bytes]");
    }
    unsigned int x = static_cast<unsigned int>(value);
    unsigned int mask = 1u << position;

    //invert mask then use and to set only bits of interest to zero
    x &= ~mask;

    return static_cast<int>(x);
}

int getField (int value, int indx1, int indx2, int isSigned) {
    int hi;
    int low;
    int size; //or difference

    //determining hi and low since order is not guarenteed
    if(indx1 == indx2){
        //throw cause this shouldnt exist
        throw std::runtime_error("index range min cannot match max");
    }
    if(indx1 > indx2){
        //input was in order hi, low
        hi = indx1;
        low = indx2;
        size = (hi - low) + 1;
    }
    if(indx1 < indx2){
        //input was in order low, hi
        hi = indx2;
        low = indx1;
        size = (hi - low) + 1;
    }
    if(size >= 31){
        //this will cause my run of ones alg to overflow.
        //this is therefore unsafe and will throw an error.
        throw std::runtime_error("bit overflow error (check that beginning and end index are in range for type int [4 bytes])");
    }
    unsigned int x = static_cast<unsigned int>(value);
    unsigned int mask = ((1u << size) - 1) << low; //run of size set bits starting at pos low 

    //x should now only hold the bits of interest in the least significant places
    x &= mask;
    x = x >> low;
    
    //checking for signaige and adjusting accordingly
    if(isSigned != 0){
        if(getBit(x, size - 1) != 0){

            //the bit is set, so the result should be negative
            unsigned int flip = (1u << size) - 1;

            //creates a mask of ones above the most significant bit, flipping to negative
            flip = ~flip;
            x |= flip;

            //cast and return
            return static_cast<int>(x);
        }
        else return static_cast<int>(x); //cause it is already good. Not actually sure abt this
    }
    else{
        //unsigned int so cast and return
        return static_cast<int>(x);
    }
}

int setField (int oldValue, int indx1, int indx2, int newValue) {
    
}

int fieldFits (int value, int width, int isSigned) {
    return 0;
}