// test_flt32.cpp
// Test driver for flt32.cpp
//
// Build:   g++ -std=c++11 -Wall -o test_flt32 test_flt32.cpp flt32.cpp field.cpp
// Run:     ./test_flt32            (fixed seed, same random tests every run)
//          ./test_flt32 98765      (different seed, new random tests)
//
// How it judges your answers:
//   PASS/FAIL  -> things with one clear right answer
//   INFO       -> edge cases where the "right" answer depends on your assignment
//                 spec (zero, denormals, overflow, inf, NaN). Read these yourself.

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <cstdarg>
#include <cmath>
#include <cfloat>
#include <random>
#include "flt32.h"

// ------------------------------------------------------------------ helpers

// Reinterpret bits <-> float without changing any bits.
static float toF(flt32 b) { float f; std::memcpy(&f, &b, sizeof f); return f; }
static flt32 toB(float f) { flt32 b; std::memcpy(&b, &f, sizeof b); return b; }

struct Str { char s[64]; };
static Str show(flt32 b) {
  Str out;
  std::snprintf(out.s, sizeof out.s, "0x%08X (%.9g)", (unsigned)b, toF(b));
  return out;
}

static int secPass, secFail, secPrinted, totalPass, totalFail, totalInfo;
static const int MAX_FAILS_SHOWN = 10;  // per section, so random tests don't flood

static void begin(const char* name) {
  std::printf("\n== %s ==\n", name);
  secPass = secFail = secPrinted = 0;
}
static void end() {
  std::printf("   -> %d passed, %d failed%s\n", secPass, secFail,
              secFail > secPrinted ? " (not all failures shown)" : "");
  totalPass += secPass;
  totalFail += secFail;
}
static void check(bool ok, const char* fmt, ...) {
  if (ok) { secPass++; return; }
  secFail++;
  if (secPrinted >= MAX_FAILS_SHOWN) return;
  secPrinted++;
  std::printf("   FAIL: ");
  va_list ap; va_start(ap, fmt); std::vprintf(fmt, ap); va_end(ap);
  std::printf("\n");
}
static void info(const char* fmt, ...) {
  totalInfo++;
  std::printf("   INFO: ");
  va_list ap; va_start(ap, fmt); std::vprintf(fmt, ap); va_end(ap);
  std::printf("\n");
}

// Random numbers. Fixed seed so a failure shows up again on the next run.
static std::mt19937 rng;
static int rnd(int lo, int hi) { return std::uniform_int_distribution<int>(lo, hi)(rng); }
static flt32 make(int sign, int exp, int mant) {
  return (flt32)(((uint32_t)sign << 31) | ((uint32_t)exp << 23) | (uint32_t)mant);
}
static flt32 randNormal(int expLo, int expHi) {
  return make(rnd(0, 1), rnd(expLo, expHi), rnd(0, 0x7FFFFF));
}

// Size of one unit in the last place for a float with this exponent field.
static double ulpAt(int expField) { return std::ldexp(1.0, expField - 150); }

// ------------------------------------------------------------------ sign

static void testSign() {
  begin("flt32_get_sign");
  struct { float f; int want; } t[] = {
    {1.0f, 0}, {-1.0f, 1}, {0.0f, 0}, {-0.0f, 1}, {FLT_MAX, 0}, {-FLT_MAX, 1},
    {1e-30f, 0}, {-123.456f, 1}, {INFINITY, 0}, {-INFINITY, 1}, {FLT_MIN, 0},
  };
  for (auto& c : t) {
    int got = flt32_get_sign(toB(c.f));
    check(got == c.want, "sign of %s: got %d, want %d", show(toB(c.f)).s, got, c.want);
  }
  for (int i = 0; i < 2000; i++) {
    flt32 x = (flt32)rng();
    int want = ((uint32_t)x >> 31) & 1;
    check(flt32_get_sign(x) == want, "sign of %s: got %d, want %d",
          show(x).s, flt32_get_sign(x), want);
  }
  end();
}

// ------------------------------------------------------------------ exponent

static void testExp() {
  begin("flt32_get_exp");
  struct { float f; int want; } t[] = {
    {1.0f, 127}, {2.0f, 128}, {0.5f, 126}, {-1.0f, 127}, {3.0f, 128},
    {1024.0f, 137}, {-0.15625f, 124}, {FLT_MAX, 254}, {FLT_MIN, 1},
    {0.0f, 0}, {-0.0f, 0}, {INFINITY, 255}, {-INFINITY, 255},
  };
  for (auto& c : t) {
    int got = flt32_get_exp(toB(c.f));
    check(got == c.want, "exp of %s: got %d, want %d", show(toB(c.f)).s, got, c.want);
  }
  // Every exponent, with sign and mantissa bits all on, so neighbors can't leak in.
  for (int e = 0; e <= 255; e++) {
    flt32 a = make(0, e, 0), b = make(1, e, 0x7FFFFF);
    check(flt32_get_exp(a) == e, "exp of %s: got %d, want %d", show(a).s, flt32_get_exp(a), e);
    check(flt32_get_exp(b) == e, "exp of %s: got %d, want %d", show(b).s, flt32_get_exp(b), e);
  }
  end();
}

// ------------------------------------------------------------------ mantissa

static void testVal() {
  begin("flt32_get_val");
  struct { float f; int want; } t[] = {
    {1.0f, 0x800000}, {1.5f, 0xC00000}, {-1.75f, 0xE00000}, {2.0f, 0x800000},
    {3.0f, 0xC00000}, {0.15625f, 0xA00000}, {FLT_MAX, 0xFFFFFF}, {-FLT_MIN, 0x800000},
  };
  for (auto& c : t) {
    int got = flt32_get_val(toB(c.f));
    check(got == c.want, "val of %s: got 0x%06X, want 0x%06X", show(toB(c.f)).s, got, c.want);
  }
  // Random normals: val must be mantissa with bit 23 set, no sign/exp bits.
  for (int i = 0; i < 3000; i++) {
    int m = rnd(0, 0x7FFFFF);
    flt32 x = make(rnd(0, 1), rnd(1, 254), m);
    int want = m | 0x800000;
    check(flt32_get_val(x) == want, "val of %s: got 0x%06X, want 0x%06X",
          show(x).s, flt32_get_val(x), want);
  }
  // Spec-dependent: does zero/denormal get the hidden 1?
  info("val of +0.0         = 0x%06X  (check your spec: some want 0 here)", flt32_get_val(0));
  info("val of denormal 0x1 = 0x%06X  (denormals have NO hidden 1 in real IEEE)",
       flt32_get_val(1));
  end();
}

// ------------------------------------------------------------------ get_all

static void testGetAll() {
  begin("flt32_get_all");
  for (int i = 0; i < 2000; i++) {
    flt32 x = (i < 1000) ? randNormal(1, 254) : (flt32)rng();
    int s = -99, e = -99, v = -99;
    flt32_get_all(x, &s, &e, &v);
    check(s == flt32_get_sign(x) && e == flt32_get_exp(x) && v == flt32_get_val(x),
          "get_all on %s gave (%d,%d,0x%X) but singles give (%d,%d,0x%X)", show(x).s,
          s, e, v, flt32_get_sign(x), flt32_get_exp(x), flt32_get_val(x));
  }
  end();
}

// ------------------------------------------------------------------ left_most_1

static void testLeftMost1() {
  begin("flt32_left_most_1");
  check(flt32_left_most_1(0) == -1, "left_most_1(0): got %d, want -1", flt32_left_most_1(0));
  check(flt32_left_most_1(-1) == 31, "left_most_1(-1): got %d, want 31", flt32_left_most_1(-1));
  check(flt32_left_most_1(0x00FFFFFF) == 23, "left_most_1(0x00FFFFFF): got %d, want 23",
        flt32_left_most_1(0x00FFFFFF));
  check(flt32_left_most_1(0x00800000) == 23, "left_most_1(0x00800000): got %d, want 23",
        flt32_left_most_1(0x00800000));
  for (int i = 0; i < 32; i++) {
    int p = (int)(1u << i);
    check(flt32_left_most_1(p) == i, "left_most_1(1<<%d): got %d", i, flt32_left_most_1(p));
    // Same top bit plus random junk below it.
    unsigned below = (i == 0) ? 0u : ((unsigned)rng() & ((1u << i) - 1));
    int q = (int)((1u << i) | below);
    check(flt32_left_most_1(q) == i, "left_most_1(0x%08X): got %d, want %d",
          (unsigned)q, flt32_left_most_1(q), i);
  }
  end();
}

// ------------------------------------------------------------------ abs / negate

static void testAbsNegate() {
  begin("flt32_abs");
  check(flt32_abs(toB(-2.5f)) == toB(2.5f), "abs(-2.5) wrong: %s", show(flt32_abs(toB(-2.5f))).s);
  check(flt32_abs(toB(2.5f)) == toB(2.5f), "abs(2.5) wrong: %s", show(flt32_abs(toB(2.5f))).s);
  check(flt32_abs(toB(-0.0f)) == 0, "abs(-0) should be +0, got %s", show(flt32_abs(toB(-0.0f))).s);
  for (int i = 0; i < 3000; i++) {
    flt32 x = (flt32)rng();
    flt32 want = (flt32)((uint32_t)x & 0x7FFFFFFFu);
    check(flt32_abs(x) == want, "abs(%s): got %s", show(x).s, show(flt32_abs(x)).s);
  }
  end();

  begin("flt32_negate");
  check(flt32_negate(0) == toB(-0.0f), "negate(+0) should be -0, got %s", show(flt32_negate(0)).s);
  check(flt32_negate(toB(3.0f)) == toB(-3.0f), "negate(3) wrong: %s", show(flt32_negate(toB(3.0f))).s);
  check(flt32_negate(toB(-3.0f)) == toB(3.0f), "negate(-3) wrong: %s", show(flt32_negate(toB(-3.0f))).s);
  for (int i = 0; i < 3000; i++) {
    flt32 x = (flt32)rng();
    flt32 want = (flt32)((uint32_t)x ^ 0x80000000u);
    check(flt32_negate(x) == want, "negate(%s): got %s", show(x).s, show(flt32_negate(x)).s);
    check(flt32_negate(flt32_negate(x)) == x, "negate twice changed %s", show(x).s);
  }
  end();
}

// ------------------------------------------------------------------ add: exact cases

// These sums are exactly representable AND lose no bits during alignment,
// so a truncating adder must match the hardware bit for bit.
static void testAddExact() {
  begin("flt32_add: hand-picked exact cases");
  struct { float a, b; } t[] = {
    {1, 1}, {1, 2}, {2, 1}, {1.5f, 2.25f}, {3, -1}, {-3, 1}, {-1, -2},
    {1, -1}, {-1, 1}, {0, 5}, {5, 0}, {-0.0f, 5}, {5, -0.0f}, {0, 0},
    {0, -7.25f}, {0.25f, 0.5f}, {100, -0.5f}, {1, -0.75f}, {1.5f, 1.5f},
    {1e10f, 1e10f}, {-1e-10f, -1e-10f}, {8388608.0f, 1}, {16777215.0f, -16777214.0f},
    {0.1f, 0.1f}, {1.99999988f, 1.99999988f}, {1024, -1023.5f}, {65536, -1},
    {1e30f, 1}, {1, 1e30f}, {1, 1e-10f}, {-1e-10f, 1}, {FLT_MIN, FLT_MIN},
    {0.75f, -1}, {-0.375f, 0.125f}, {1048576.0f, -0.5f},
  };
  for (auto& c : t) {
    flt32 got = flt32_add(toB(c.a), toB(c.b));
    flt32 want = toB(c.a + c.b);
    check(got == want, "%g + %g: got %s, want %s", c.a, c.b, show(got).s, show(want).s);
  }
  end();

  begin("flt32_add: x + x == 2x (random)");
  for (int i = 0; i < 3000; i++) {
    flt32 x = randNormal(1, 253);
    flt32 got = flt32_add(x, x), want = toB(toF(x) * 2.0f);
    check(got == want, "x+x for x=%s: got %s, want %s", show(x).s, show(got).s, show(want).s);
  }
  end();

  begin("flt32_add: x + (-x) == +0 (random)");
  for (int i = 0; i < 3000; i++) {
    flt32 x = randNormal(1, 254);
    flt32 got = flt32_add(x, flt32_negate(x));
    check(got == 0, "x + -x for x=%s: got %s, want +0", show(x).s, show(got).s);
  }
  end();

  begin("flt32_add: integer sums (random, always exact)");
  for (int i = 0; i < 5000; i++) {
    int a = rnd(-(1 << 23), 1 << 23), b = rnd(-(1 << 23), 1 << 23);
    flt32 got = flt32_add(toB((float)a), toB((float)b));
    flt32 want = toB((float)(a + b));
    check(got == want, "%d + %d: got %s, want %s", a, b, show(got).s, show(want).s);
  }
  end();

  begin("flt32_add: commutative, add(x,y) == add(y,x)");
  for (int i = 0; i < 5000; i++) {
    flt32 x = randNormal(60, 190), y = randNormal(60, 190);
    flt32 xy = flt32_add(x, y), yx = flt32_add(y, x);
    check(xy == yx, "x=%s y=%s: x+y=%s, y+x=%s", show(x).s, show(y).s, show(xy).s, show(yx).s);
  }
  end();

  begin("flt32_add: huge exponent gap returns the bigger one");
  for (int i = 0; i < 2000; i++) {
    int ebig = rnd(60, 254);
    flt32 big = make(rnd(0, 1), ebig, rnd(0, 0x7FFFFF));
    flt32 small = make(rnd(0, 1), rnd(1, ebig - 32 > 1 ? ebig - 32 : 1), rnd(0, 0x7FFFFF));
    if (flt32_get_exp(big) - flt32_get_exp(small) < 32) continue;
    check(flt32_add(big, small) == big, "big=%s small=%s: got %s",
          show(big).s, show(small).s, show(flt32_add(big, small)).s);
    check(flt32_add(small, big) == big, "small=%s big=%s: got %s",
          show(small).s, show(big).s, show(flt32_add(small, big)).s);
  }
  end();
}

// ------------------------------------------------------------------ add: fuzz vs exact math

// Compares against the exact sum computed in double. With an exponent gap
// of 24 or less, double holds the exact answer, so this is a true reference.
//
// Your adder truncates (no guard bits, no rounding), so it won't always match
// hardware. These checks test the error bounds a truncating adder must meet:
//   same signs:     result <= exact (in magnitude), off by less than 2 ulps
//   opposite signs: off by at most 2 ulps of the BIGGER input
static void testAddFuzz() {
  begin("flt32_add: random fuzz vs exact math");
  int exactMatches = 0, total = 0;
  double worstSameSignUlps = 0;
  for (int i = 0; i < 20000; i++) {
    int ex = rnd(100, 150);
    int ey = ex + rnd(-24, 24);
    flt32 x = make(rnd(0, 1), ex, rnd(0, 0x7FFFFF));
    flt32 y = make(rnd(0, 1), ey, rnd(0, 0x7FFFFF));
    double exact = (double)toF(x) + (double)toF(y);
    flt32 r = flt32_add(x, y);
    double got = (double)toF(r);
    total++;
    if (r == toB(toF(x) + toF(y))) exactMatches++;

    if (exact == 0.0) {
      check(r == 0, "x=%s y=%s should cancel to +0, got %s", show(x).s, show(y).s, show(r).s);
      continue;
    }
    bool wantNeg = exact < 0;
    check((flt32_get_sign(r) == 1) == wantNeg, "x=%s y=%s: wrong sign, got %s, exact %.17g",
          show(x).s, show(y).s, show(r).s, exact);

    bool sameSign = flt32_get_sign(x) == flt32_get_sign(y);
    if (sameSign) {
      double err = std::fabs(exact) - std::fabs(got);  // should be >= 0
      double u = ulpAt(flt32_get_exp(r));
      if (err / u > worstSameSignUlps) worstSameSignUlps = err / u;
      check(err >= 0 && err < 2 * u,
            "x=%s y=%s: got %.17g, exact %.17g (error %.3g ulps; truncation must round toward 0)",
            show(x).s, show(y).s, got, exact, err / u);
    } else {
      int ebig = flt32_get_exp(x) > flt32_get_exp(y) ? flt32_get_exp(x) : flt32_get_exp(y);
      double err = std::fabs(exact - got);
      check(err <= 2 * ulpAt(ebig), "x=%s y=%s: got %.17g, exact %.17g (error too big)",
            show(x).s, show(y).s, got, exact);
    }
  }
  end();
  info("matched hardware bit-for-bit on %d / %d random sums (hardware rounds, you truncate)",
       exactMatches, total);
  info("worst same-sign error: %.3f ulps (must stay under 2)", worstSameSignUlps);
}

// ------------------------------------------------------------------ sub

static void testSub() {
  begin("flt32_sub");
  struct { float a, b; } t[] = {
    {5, 3}, {3, 5}, {-5, -3}, {1, 0.25f}, {0, 4}, {4, 0}, {1.5f, -1.5f},
    {7.5f, 7.5f}, {-2, -2}, {1, 1e30f}, {1024, 0.5f},
  };
  for (auto& c : t) {
    flt32 got = flt32_sub(toB(c.a), toB(c.b));
    flt32 want = toB(c.a - c.b);
    check(got == want, "%g - %g: got %s, want %s", c.a, c.b, show(got).s, show(want).s);
  }
  for (int i = 0; i < 3000; i++) {
    flt32 x = randNormal(60, 190), y = randNormal(60, 190);
    check(flt32_sub(x, y) == flt32_add(x, flt32_negate(y)),
          "sub(%s, %s) != add(x, -y)", show(x).s, show(y).s);
    check(flt32_sub(x, x) == 0, "x - x for x=%s: got %s", show(x).s, show(flt32_sub(x, x)).s);
  }
  for (int i = 0; i < 3000; i++) {
    int a = rnd(-(1 << 23), 1 << 23), b = rnd(-(1 << 23), 1 << 23);
    flt32 got = flt32_sub(toB((float)a), toB((float)b));
    flt32 want = toB((float)(a - b));
    check(got == want, "%d - %d: got %s, want %s", a, b, show(got).s, show(want).s);
  }
  end();
}

// ------------------------------------------------------------------ edge cases (INFO only)

static void edge(const char* label, float a, float b) {
  flt32 got = flt32_add(toB(a), toB(b));
  info("%-28s you: %-28s hardware: %s", label, show(got).s, show(toB(a + b)).s);
}

static void testEdges() {
  std::printf("\n== edge cases (assignment-dependent, read these yourself) ==\n");
  edge("-0 + -0", -0.0f, -0.0f);
  edge("FLT_MAX + FLT_MAX (overflow)", FLT_MAX, FLT_MAX);
  edge("FLT_MAX + FLT_MAX/2", FLT_MAX, FLT_MAX / 2);
  edge("inf + 1", INFINITY, 1);
  edge("NaN + 1", NAN, 1);
  edge("1.5*FLT_MIN - FLT_MIN (underflow)", 1.5f * FLT_MIN, -FLT_MIN);
  edge("FLT_MIN - FLT_MIN/2", FLT_MIN, -FLT_MIN / 2);
  edge("denorm + denorm", toF(0x00000010), toF(0x00000020));
  edge("1 + denorm", 1, toF(0x00000001));
}

// ------------------------------------------------------------------ main

int main(int argc, char** argv) {
  unsigned seed = (argc > 1) ? (unsigned)std::strtoul(argv[1], nullptr, 10) : 12345u;
  rng.seed(seed);
  std::printf("flt32 tests, seed %u\n", seed);

  testSign();
  testExp();
  testVal();
  testGetAll();
  testLeftMost1();
  testAbsNegate();
  testAddExact();
  testAddFuzz();
  testSub();
  testEdges();

  std::printf("\n==========================================\n");
  std::printf("TOTAL: %d passed, %d failed, %d info lines\n", totalPass, totalFail, totalInfo);
  std::printf(totalFail == 0 ? "ALL CHECKS PASSED\n" : "SOME CHECKS FAILED\n");
  return totalFail == 0 ? 0 : 1;
}