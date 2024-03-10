#define INSTRUCTIONS
#ifndef INSTRUCTIONS

// Logic Gates
const int not(const int parameter);
const int and(const int parameter);
const int or(const int parameter);
const int xor(const int parameter);

// Arithmetical Instructions
const int rshift(const int parameter);
const int lshift(const int parameter);
const int add(const int parameter);
const int subtract(const int parameter);
const int multiply(const int parameter);
const int divide(const int parameter);
const int modulo(const int parameter);

// Comparison
const int compare(const int parameter);
const int greater(const int parameter);

// Utilities
const int move(const int parameter);
const int jump(const int parameter);
const int copy(const int parameter);

const void (*instructions[])(int, int);

#endif
