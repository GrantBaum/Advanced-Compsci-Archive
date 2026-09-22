#include "field.h"
#include "flt32.h"

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
  return -1;
}
flt32 flt32_abs (flt32 x) {
  return 0;
}
flt32 flt32_negate (flt32 x) {
  return 0;
}
flt32 flt32_add (flt32 x, flt32 y) {
  return 0;
}
flt32 flt32_sub (flt32 x, flt32 y) {
  return 0;
}