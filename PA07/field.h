#ifndef __FIELD_H__
#define __FIELD_H__
#include <stdbool.h>

int getBit (int value, int position);
int setBit (int value, int position);
int clearBit (int value, int position);
int getField (int value, int hi, int lo, int isSigned);
int setField (int oldValue, int hi, int lo, int newValue);
int fieldFits (int value, int width, int isSigned);

#endif