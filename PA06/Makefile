# Makefile for CS 270 field project
# Builds both testField and testAll.
#
#   make            build everything
#   make test       build and run testAll
#   make clean      delete built files

CXX      = g++
CXXFLAGS = -g -std=c++11 -Wall

EXES = testField testAll

all: $(EXES)

# Each program with a main() gets its own target.
# Both share field.o.
testField: field.o testField.o
	$(CXX) $(CXXFLAGS) $^ -o $@

testAll: field.o testAll.o
	$(CXX) $(CXXFLAGS) $^ -o $@

# Any .cpp becomes a .o. Rebuild if field.h changes.
%.o: %.cpp field.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: testAll
	./testAll

clean:
	rm -f $(EXES) *.o

package:
	@echo "Packaging up project directory ..."

.PHONY: all test clean package