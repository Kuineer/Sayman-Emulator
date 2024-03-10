#define INSTRUCTIONS
#ifndef INSTRUCTIONS

#include <math.h>

// Logic Gates
const int not(const int a) { return !a; };
const int and(const int a, const int b) { return a && b; };
const int or(const int a, const int b) { return a | b; };
const int xor(const int a, const int b) { return a ^ b; };

// Arithmetics
const int rshift(const int a) { return a >> 1 };
const int lshift(const int a) { return a << 1};
const int add(const int a, const int b) { return a + b };
const int subtract(const int a, const int b) { return a - b };
const int multiply(const int a, const int b) { return a * b };
const int divide(const int a, const int b) { return floor(a / b)};
const int modulo(const int a, const int b) { return a % b };

// Comparison
const int compare(const int a, const int b) { return a == b };
const int greater(const int a, const int b) { return a > b };

// Utilities
const int move(const int a, int reg) { reg = a; return 0 };
const int jump(const int a, int point) { a = point; return 0 };
const int copy(const int a, int b) { b = a; return 0 };

const void (*instructions[])(int, int) = {not, and, or, xor, rshift, lshift, add, subtract, multiply, divide, modulo, compare, greater, move, jump, copy};

#endif
