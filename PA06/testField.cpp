#include <iostream>
#include <cstdlib>
#include <cstring>
#include "field.h"

void printBinaryMSB(int value, int msb) {
    while (msb >= 0) {
        std::cout << ((value & (1 << msb)) ? '1' : '0');
        if (msb && ((msb & 0x3) == 0))
            std::cout << '-';
        msb--;
    }
}

void printBinary(int value) {
    printBinaryMSB(value, 31);
}

static void usage() {
    std::cout << "Usage: testField bin value" << std::endl;
    std::cout << "       testField getBit value position" << std::endl;
    std::cout << "       testField setBit value position" << std::endl;
    std::cout << "       testField clearBit value position" << std::endl;
    std::cout << "       testField fits value width isSigned" << std::endl;
    std::cout << "       testField get value hi lo isSigned" << std::endl;
    std::cout << "       testField set value hi lo newValue" << std::endl;
    std::exit(1);
}

static void printResult(int result) {
    std::cout << "dec: " << result << " hex: 0x" << std::hex << result << " bin: ";
    printBinary(result);
    std::cout << std::dec << std::endl;
}

int main(int argc, char* argv[]) {
    char* junk;
    int value, new_val, result, position, hi, lo, isSigned, width;

    if (argc < 3)
        usage();

    char* op = argv[1];

    if ((std::strcmp(op, "bin") == 0) && (argc == 3)) {
        printResult(static_cast<int>(std::strtol(argv[2], &junk, 0)));
    }

    else if ((std::strcmp(op, "getBit") == 0) && (argc == 4)) {
        value = static_cast<int>(std::strtol(argv[2], &junk, 0));
        position = static_cast<int>(std::strtol(argv[3], &junk, 0));
        std::cout << "getBit " << position << " from 0x" << std::hex << value << " = " << getBit(value, position) << std::dec << std::endl;
    }

    else if ((std::strcmp(op, "setBit") == 0) && (argc == 4)) {
        value = static_cast<int>(std::strtol(argv[2], &junk, 0));
        position = static_cast<int>(std::strtol(argv[3], &junk, 0));
        result = setBit(value, position);
        std::cout << "setBit " << position << " in 0x" << std::hex << value << " = 0x" << result << std::dec << std::endl;
    }

    else if ((std::strcmp(op, "clearBit") == 0) && (argc == 4)) {
        value = static_cast<int>(std::strtol(argv[2], &junk, 0));
        position = static_cast<int>(std::strtol(argv[3], &junk, 0));
        result = clearBit(value, position);
        std::cout << "clearBit " << position << " in 0x" << std::hex << value << " = 0x" << result << std::dec << std::endl;
    }

    else if ((std::strcmp(op, "fits") == 0) && (argc == 5)) {
        value = static_cast<int>(std::strtol(argv[2], &junk, 0));
        width = static_cast<int>(std::strtol(argv[3], &junk, 0));
        isSigned = static_cast<int>(std::strtol(argv[4], &junk, 0));
        result = fieldFits(value, width, isSigned);
        std::cout << "fieldFits: " << value << " into " << width << " bits (signed " << isSigned << ") = " << result << std::endl;
    }

    else if ((std::strcmp(op, "get") == 0) && (argc == 6)) {
        value = static_cast<int>(std::strtol(argv[2], &junk, 0));
        hi = static_cast<int>(std::strtol(argv[3], &junk, 0));
        lo = static_cast<int>(std::strtol(argv[4], &junk, 0));
        isSigned = static_cast<int>(std::strtol(argv[5], &junk, 0));
        result = getField(value, hi, lo, isSigned);
        std::cout << "getField: get bits " << lo << ":" << hi << " from 0x" << std::hex << value << " (signed " << isSigned << ") = 0x" << result << std::dec << std::endl;
    }

    else if ((std::strcmp(op, "set") == 0) && (argc == 6)) {
        value = static_cast<int>(std::strtol(argv[2], &junk, 0));
        hi = static_cast<int>(std::strtol(argv[3], &junk, 0));
        lo = static_cast<int>(std::strtol(argv[4], &junk, 0));
        new_val = static_cast<int>(std::strtol(argv[5], &junk, 0));
        result = setField(value, hi, lo, new_val);
        std::cout << "setField: set bits " << lo << ":" << hi << " in 0x" << std::hex << value << " to 0x" << new_val << " = 0x" << result << std::dec << std::endl;
    }

    else
        usage();

    return 0;
}