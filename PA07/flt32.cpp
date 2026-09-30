#include "field.h"
#include "flt32.h"

//im gonna use these for my add function because theyre the only masks I will need
#define SIGN_BYTE_MASK 0x80000000
#define EXPONENT_BYTE_MASK 0x7F800000
#define MANTISSA_BYTE_MASK 0x007FFFFF

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
  if(getBit(x, 31) != 0){
    return clearBit(x, 31); //negative, so negating turns pos
  }
  else return setBit(x, 31); //pos, so negating turns neg
}

flt32 flt32_add (flt32 x, flt32 y) {
	
  unsigned int sign = flt32 & SIGN_BYTE_MASK;
  unsigned int exp = flt32 & EXPONENT_BYTE_MASK;
  unsigned int mantissa = flt32 & MANTISSA_BYTE_MASK;
//get number in binary form
	//@QUESTION can i get a decimal in the flt32 type? How does it handle that?
//find leftmost one of mantissa and truncate everything to the left (as i approaches 0 from 22)
//@TODO can i make an alg that gives me the exponent based on what i truncate? I feel like I should be able to
//normalize mantissas based on larger exponent
//truncate anything that is outside the specificity
//binary and mantissas
//add the exponent (larger of the two) and sign bit to the front
	return 0; //not actually. Return what i get as a flt32;
	
}
flt32 flt32_sub (flt32 x, flt32 y) {
  return 0;
}
