#include "field.h"
#include <stdexcept>
#include <bitset> //used for debugging to print binary
#include <iostream> //used for printing in debugging
#include <cstdint> //for fixed width integer types

int getBit (int value, int position){
    //working with an unsigned int for value and mask
    unsigned int x = static_cast<unsigned int>(value);
    unsigned int mask = single(position);
    //if there is a one anywhere it means the bit of interest was a one
    if((x & mask) != 0){
        return 1;
    }
    else return 0;
}
int setBit (int value, int position){
    //working with unsigned ints but this time i need to cast back
    unsigned int x = static_cast<unsigned int>(value);
    unsigned int mask = single(position);
    //set bit of interest to 1 with binary or
    x |= mask;

    //recast and return
    return static_cast<int>(x);
}
int clearBit (int value, int position){
    unsigned int x = static_cast<unsigned int>(value);
    unsigned int mask = single(position);
    //invert mask then use and to set only bits of interest to zero
    x &= ~mask;

    return static_cast<int>(x);
}
int getField (int value, int indx1, int indx2, int isSigned) {
    int hi;
    int low;
    int size; //or difference
    
    //error checking FIRST
    if(indx1 < 0 || indx2 < 0){
        throw std::runtime_error("bit indicies cannot be less than zero!");
    }
    if(indx1 == indx2){
        size = 1; //i can just define straight up and set hi and low for later
        //doesnt matter what i use here
        hi = indx1;
        low = indx2;
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

    unsigned int x = static_cast<unsigned int>(value);
    unsigned int mask = run(size, low);
    //x should now only hold the bits of interest in the least significant places
    x &= mask;
    x = x >> low;
    
    //checking for signaige and adjusting accordingly
    if(isSigned != 0){
        if(getBit(x, size - 1) != 0){

            //the bit is set, so the result should be negative
            unsigned int flip = run(size);
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
    int hi;
    int low;
    int size; //or difference

    //error and equals checks
    if(indx1 < 0 || indx2 < 0){
        throw std::runtime_error("bit indicies cannot be less than zero!");
    }
    if(indx1 == indx2){
        size = 1;
        hi = indx1;
        low = indx2;
    }
    //determining hi and low since order is not guarenteed
    if(indx1 > indx2){
        hi = indx1;
        low = indx2;
        size = (hi - low) + 1;
    }
    if(indx1 < indx2){
        hi = indx2;
        low = indx1;
        size = (hi - low) + 1;
    }

    unsigned int oldV = static_cast<unsigned int>(oldValue);
    unsigned int newV = static_cast<unsigned int>(newValue);
    unsigned int omask = run(size, low);
    unsigned int nmask = run(size);
    omask = ~omask; //inverting mask because we want to set all bits within the field to zero
    oldV &= omask; //set all bits in field of old to zero
    newV &= nmask;
    newV = newV << low;
    oldV |= newV;

    //cast and return
    return static_cast<int>(oldV);
}
int fieldFits (int value, int width, int isSigned) {
    //first error check
    if(width > 32 || width <= 0){
        throw std::runtime_error("invalid size. Make sure it is between 1 and 32");
    }
    //signed logic
    if(isSigned != 0){
        int sMax = static_cast<int>(run(width - 1)); //largest pos
        int sMin = ~sMax; //smallest neg

        if(value <= sMax && value >= sMin){
            return 1; //value is in between
        }
        else return 0; //doesnt fit
    }
    //unsigned logic
    else {
        unsigned int unsVal = static_cast<unsigned int>(value);
        unsigned int unsMax = run(width);

        if(unsVal <= unsMax){
            return 1; //value fits
        }
        else return 0; //value doesnt fit
    }
}
//helper methods for run of ones to handle edge cases lazier
unsigned int run(int size, int start){
    //check for errors first
    if(size > 32){
        throw std::runtime_error("size overload error (runFunc). Make sure size is less than / equal to 32 [4 bytes]");
    }
    if(start < 0){
        throw std::runtime_error("bit indicies cannot be less than zero! (runFunc)");
    }
    //then handle the edge case
    if(size == 32){
        return 0xFFFFFFFF; //hex digit for straight ones
    }

    //then do the actual alg
    return ((1u << size) - 1) << start; //run of size set bits starting at pos start
}
unsigned int run(int size){
    //errors
    if(size > 32){
        throw std::runtime_error("size overload error (runFunc). Make sure size is less than / equal to 32 [4 bytes]");
    }
    //edge case
    if(size == 32){
        return 0xFFFFFFFF;
    }

    return ((1u << size) - 1); //this will start at bit index 0
}
unsigned int single(int pos){
    //error
    if(pos < 0 || pos > 31){
        throw std::runtime_error("bit indicies cannot be less than zero or greater than 31 (singleFunc)");
    }

    else return 1u << pos;
}