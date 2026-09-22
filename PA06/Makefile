# Makefile template for CS 270

# List of files
C_SRCS		= field.cpp testField.cpp
C_OBJS		= field.o testField.o
C_HEADERS	= field.h

OBJS		= ${C_OBJS} 
EXE	        = testField

# Compiler and loader commands and flags
GCC		= g++
GCC_FLAGS	= -g -std=c++11 -Wall -c
LD_FLAGS	= -g -std=c++11 -Wall

# Compile .c files to .o files
.cpp.o:
	$(GCC) $(GCC_FLAGS) $<

# Target is the executable
default: $(OBJS)	
	$(GCC) $(LD_FLAGS) $(OBJS) -o $(EXE)

# Recompile C objects if headers change
${C_OBJS}:      ${C_HEADERS}

# Clean up the directory
clean:
	-rm -f testField 

# Package the directory
package:
	@echo "Packaging up project directory ..."