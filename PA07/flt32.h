#ifndef __FLT32_H__
#define __FLT32_H__
#define flt32 int

int flt32_get_sign (flt32 x);
int flt32_get_exp (flt32 x);
int flt32_get_val (flt32 x);
void flt32_get_all(flt32 x, int* sign, int*exp, int* val);
int flt32_left_most_1 (int value);
flt32 flt32_abs (flt32 x);
flt32 flt32_negate (flt32 x);
flt32 flt32_add (flt32 x, flt32 y);
flt32 flt32_sub (flt32 x, flt32 y);

#endif