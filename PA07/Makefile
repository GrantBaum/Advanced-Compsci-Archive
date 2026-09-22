#simple Makefile for FLOAT Assignment

# these are defined so that on a different system only these definitions
# need to change if gcc and rm are actually in different locations
# The rest of the Makefile need not change

RM   = /bin/rm
GCC  = /usr/bin/g++

CFLAGS  = -g -Wall -c -std=c++11
LDFLAGS = -g

testFlt32: field.o flt32.o testFlt32.o
	${GCC} ${LDFLAGS} -o testFlt32 field.o flt32.o testFlt32.o

flt32.o: field.h flt32.h flt32.cpp
	${GCC} ${CFLAGS} flt32.cpp

testFlt32.o: field.h flt32.h testFlt32.cpp
	${GCC} ${CFLAGS} testFlt32.cpp

clean:
	${RM} -f testFlt32.o flt32.o testFlt32