#include "field.h"
#include "flt32.h"

//im gonna use these for my add function because theyre the only masks I will need
#define EXPONENT_BYTE_MASK 0x7F800000
#define MANTISSA_BYTE_MASK 0x007FFFFF
#define HIDDEN_1  0x00800000 //this is for the implied one that goes into the mant

int flt32_get_sign (flt32 x) {
  return getBit(x, 31); //returns most significant bit
}
int flt32_get_exp (flt32 x) {
  return getField(x, 23, 30, 0); //exponent bits, unsigned
}
int flt32_get_val (flt32 x) {
  unsigned int newV = static_cast<unsigned int>(getField(x, 0, 22, 0)); //0-22 unsigned
  newV = setBit(newV, 23); //setting implied one
  return newV;
}
void flt32_get_all(flt32 x, int* sign, int*exp, int* val) {
  *sign = flt32_get_sign(x);
	*exp = flt32_get_exp(x);
	*val = flt32_get_val(x);
}
int flt32_left_most_1 (int value) {
  //4 lines instead of ten. get out cannonicaled.
  for(int i = 31; i >= 0; i--){
    if(getBit(value, i) == 1){
      return i;
    }
  }
  return -1; //if we make it out of the loop the number was zero
}
flt32 flt32_abs (flt32 x) {
  return clearBit(x, 31); //clears sign bit
}
flt32 flt32_negate (flt32 x) {
  if(getBit(x, 31) != 0) return clearBit(x, 31); //negative, so negating turns pos
  else return setBit(x, 31); //pos, so negating turns neg
}

flt32 flt32_add (flt32 x, flt32 y) {
	
  //seperate the pieces
  int x_sign = getBit(x, 31);
  int y_sign = getBit(y, 31);
  // Comparing and subtracting exponents works the same with it.
  int x_exp = getField(x, 30, 23, 0);
  int y_exp = getField(y, 30, 23, 0);
  // Same idea for bits 22 down to 0. Also unsigned.
  int x_val = getField(x, 22, 0, 0);
  int y_val = getField(y, 22, 0, 0);

  //zero check in bits
  if(x_exp == 0 && x_val == 0) return y;
  if(y_exp == 0 && y_val == 0) return x;
  //add implied one
  x_val = setBit(x_val, 23);
  y_val = setBit(y_val, 23);

  int exp;  //the answer's exponent (may change)
    if (x_exp >= y_exp) {
        int diff = x_exp - y_exp;
        if (!fieldFits(diff, 5, 0)) return x;  //fieldFits(diff, 5, 0) asks: does diff fit in 5 unsigned bits? 5 bits can hold 0 to 31. Those are the only shift amounts C promises to handle
        y_val >>= diff;  // bits that fall off are gone (truncation)
        exp = x_exp;
    } else {
        // Same thing, but y has the bigger exponent.
        int diff = y_exp - x_exp;
        if (!fieldFits(diff, 5, 0)) return y;
        x_val >>= diff;
        exp = y_exp;
    }

    //signs
    if (x_sign) x_val = -x_val;
    if (y_sign) y_val = -y_val;
    int sum = x_val + y_val; //this will do binary addition so im not cheating

    //if they canceled out exactly, the answer is zero.
    if (sum == 0) return 0;
    //if sum is negative, remember that in sign, then flip sum positive.
    int sign = 0;
    if (sum < 0) {
        sign = 1;
        sum = -sum;
    }

    //renormalize
    int shift = flt32_left_most_1(sum) - 23;
    if (shift > 0) {
        sum >>= shift; //more truncation happens here
    } else {
        sum <<= -shift; //-shift is 0 or positive here
    }
    exp += shift; //works both ways since shift can be negative
    sum = clearBit(sum, 23); //drop implied one

    flt32 result = 0;
    result = setField(result, 22, 0, sum);    //mantissa into bits 22-0
    result = setField(result, 30, 23, exp);   //exponent into bits 30-23

    // If the answer is negative, turn on bit 31.
    if (sign) result = setBit(result, 31);

    return result;

}
flt32 flt32_sub (flt32 x, flt32 y) {
  return flt32_add(x, flt32_negate(y));
}
