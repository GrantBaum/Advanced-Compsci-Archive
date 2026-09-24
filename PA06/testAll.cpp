// testAll.cpp
// Runs every test case for field.cpp and reports PASS or FAIL.
//
// Build:  g++ -Wall -o testAll testAll.cpp field.cpp
// Run:    ./testAll
//THIS IS AN AI GENERATED FILE. created from chat https://claude.ai/chat/aac20a7b-e94b-42aa-81f8-27bd812f7c11 on 9/24/26

#include <cstdio>
#include <exception>
#include "field.h"

static int passed = 0;
static int failed = 0;

static void check(const char* call, int got, int expected) {
    if (got == expected) {
        passed++;
    } else {
        failed++;
        printf("FAIL  %-40s got 0x%08x  expected 0x%08x\n",
               call, (unsigned)got, (unsigned)expected);
    }
}

// CHECK: the call should return `expected`.
// If it throws instead, that counts as a FAIL and the tests keep going.
#define CHECK(call, expected)                                              \
    do {                                                                   \
        try {                                                              \
            check(#call, (call), (int)(expected));                         \
        } catch (const std::exception& e) {                                \
            failed++;                                                      \
            printf("FAIL  %-40s threw: %s\n", #call, e.what());            \
        } catch (...) {                                                    \
            failed++;                                                      \
            printf("FAIL  %-40s threw an exception\n", #call);             \
        }                                                                  \
    } while (0)

// CHECK_THROWS: the call SHOULD throw. Any exception type counts as a PASS.
#define CHECK_THROWS(call)                                                 \
    do {                                                                   \
        try {                                                              \
            (void)(call);                                                  \
            failed++;                                                      \
            printf("FAIL  %-40s expected an exception, none thrown\n",     \
                   #call);                                                 \
        } catch (...) {                                                    \
            passed++;                                                      \
        }                                                                  \
    } while (0)

int main() {
    // ---------- getBit ----------
    CHECK(getBit(437, 0), 1);
    CHECK(getBit(437, 1), 0);
    CHECK(getBit(437, 2), 1);
    CHECK(getBit(437, 8), 1);
    CHECK(getBit(437, 9), 0);
    CHECK(getBit(0, 5), 0);
    CHECK(getBit(-1, 0), 1);
    CHECK(getBit(-1, 31), 1);
    CHECK(getBit((int)0x80000000u, 31), 1);
    CHECK(getBit((int)0x80000000u, 30), 0);
    CHECK(getBit(1, 31), 0);

    // ---------- setBit ----------
    CHECK(setBit(437, 0), 0x1b5);
    CHECK(setBit(437, 1), 0x1b7);
    CHECK(setBit(437, 2), 0x1b5);
    CHECK(setBit(437, 3), 0x1bd);
    CHECK(setBit(437, 9), 0x3b5);
    CHECK(setBit(0, 0), 0x1);
    CHECK(setBit(0, 31), 0x80000000u);
    CHECK(setBit(-1, 17), 0xffffffffu);

    // ---------- clearBit ----------
    CHECK(clearBit(437, 0), 0x1b4);
    CHECK(clearBit(437, 1), 0x1b5);
    CHECK(clearBit(437, 2), 0x1b1);
    CHECK(clearBit(437, 8), 0xb5);
    CHECK(clearBit(-1, 0), 0xfffffffeu);
    CHECK(clearBit(-1, 31), 0x7fffffff);
    CHECK(clearBit((int)0x80000000u, 31), 0x0);
    CHECK(clearBit(0, 5), 0x0);

    // ---------- getField ----------
    CHECK(getField(437, 2, 0, 0), 0x5);
    CHECK(getField(437, 3, 1, 0), 0x2);
    CHECK(getField(437, 4, 2, 1), 0xfffffffdu);
    CHECK(getField(437, 0, 2, 0), 0x5);
    CHECK(getField(437, 2, 4, 1), 0xfffffffdu);
    CHECK(getField(437, 4, 2, 0), 0x5);
    CHECK(getField(437, 7, 4, 0), 0xb);
    CHECK(getField(437, 7, 4, 1), 0xfffffffbu);
    CHECK(getField(437, 0, 0, 0), 0x1);
    CHECK(getField(437, 0, 0, 1), 0xffffffffu);
    CHECK(getField(437, 1, 1, 1), 0x0);
    CHECK(getField(437, 8, 0, 1), 0xffffffb5u);
    CHECK(getField(0xC400, 15, 15, 0), 0x1);
    CHECK(getField(0xC400, 14, 10, 0), 0x11);
    CHECK(getField(0xC400, 9, 0, 0), 0x0);
    CHECK(getField(0x3555, 9, 0, 0), 0x155);
    CHECK(getField(0x12345678, 11, 4, 1), 0x67);
    CHECK(getField((int)0x87654321u, 31, 24, 0), 0x87);
    CHECK(getField((int)0x87654321u, 31, 24, 1), 0xffffff87u);
    CHECK(getField((int)0x80000000u, 31, 31, 0), 0x1);
    CHECK(getField(-1, 31, 0, 0), 0xffffffffu);
    CHECK(getField(0x12345678, 31, 0, 1), 0x12345678);
    CHECK(getField(0, 10, 3, 1), 0x0);

    // ---------- setField ----------
    CHECK(setField(437, 2, 0, 5), 0x1b5);
    CHECK(setField(437, 3, 1, 6), 0x1bd);
    CHECK(setField(437, 4, 2, 7), 0x1bd);
    CHECK(setField(437, 1, 3, 6), 0x1bd);
    CHECK(setField(437, 3, 1, 0xff), 0x1bf);
    CHECK(setField(0, 3, 0, -1), 0xf);
    CHECK(setField(0, 7, 4, -2), 0xe0);
    CHECK(setField(437, 8, 0, 0), 0x0);
    CHECK(setField(-1, 7, 0, 0), 0xffffff00u);
    CHECK(setField((int)0xffffffffu, 15, 8, 0), 0xffff00ffu);
    CHECK(setField(437, 0, 0, 0), 0x1b4);
    CHECK(setField(0, 31, 31, 1), 0x80000000u);
    CHECK(setField(0x4400, 15, 15, 1), 0xc400);
    CHECK(setField(437, 31, 0, 0x12345678), 0x12345678);

    // ---------- fieldFits ----------
    CHECK(fieldFits(10, 4, 0), 1);
    CHECK(fieldFits(16, 4, 0), 0);
    CHECK(fieldFits(-8, 4, 1), 1);
    CHECK(fieldFits(15, 4, 0), 1);
    CHECK(fieldFits(0, 4, 0), 1);
    CHECK(fieldFits(7, 4, 1), 1);
    CHECK(fieldFits(8, 4, 1), 0);
    CHECK(fieldFits(-9, 4, 1), 0);
    CHECK(fieldFits(-1, 4, 1), 1);
    CHECK(fieldFits(1, 1, 0), 1);
    CHECK(fieldFits(2, 1, 0), 0);
    CHECK(fieldFits(-1, 1, 1), 1);
    CHECK(fieldFits(1, 1, 1), 0);
    CHECK(fieldFits(0x3fffffff, 31, 1), 1);
    CHECK(fieldFits(0x40000000, 31, 1), 0);
    CHECK(fieldFits(0x7fffffff, 32, 1), 1);
    CHECK(fieldFits((int)0x80000000u, 32, 1), 1);
    CHECK(fieldFits(-1, 4, 0), 0);  // not spelled out in directions, 0 is the usual answer

    // ---------- invalid input ----------
    // These are OUTSIDE what the directions allow, so throwing is fair here.
    // Keep only the ones your field.cpp actually throws on. Delete the rest.
    CHECK_THROWS(getBit(437, 32));
    CHECK_THROWS(getBit(437, -1));
    CHECK_THROWS(setBit(437, 32));
    CHECK_THROWS(clearBit(437, -1));
    CHECK_THROWS(getField(437, 32, 0, 0));
    CHECK_THROWS(getField(437, 5, -1, 0));
    CHECK_THROWS(setField(437, 32, 0, 1));
    CHECK_THROWS(fieldFits(5, 0, 0));
    CHECK_THROWS(fieldFits(5, 33, 1));

    // ---------- summary ----------
    printf("\n%d passed, %d failed\n", passed, failed);
    printf(failed == 0 ? "ALL TESTS PASS\n" : "SOME TESTS FAILED\n");
    return failed == 0 ? 0 : 1;
}