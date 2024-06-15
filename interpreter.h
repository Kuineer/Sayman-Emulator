#ifndef interpreter
#define interpreter

#include <math.h>
#include <stdlib.h>

#include "functions.h"
#include "properties.h"

char generate_flags(char result) {
	if (result == 0b10000)
		return (char) 0b1000;
	else if (result == 0b0000)
		return (char) 0b0100;
	else if (result < 0)
		return (char) 0b0010;
	else if (result > 0)
		return (char) 0b0001;
	else
		return 0b0000;
};

void PASS(char *a, char b) { ; }
void ASSIGN(char *a, char b) { assign_to_address(a, b); }
void NOT(char *a, char b) { // Integrate flags
	char result = !b;
	assign_to_address(a, result)

	// flags = generate_flags(result);
}
void AND(char *a, char b) { assign_to_address(a, b & *a); }
void OR(char *a, char b) { assign_to_address(a, b | *a); }
void XOR(char *a, char b) { assign_to_address(a, b ^ *a); }
void ADD(char *a, char b) { assign_to_address(a, form_nibble(b + *a)); }
void SUBTRACT(char *a, char b) { assign_to_address(a, form_nibble(b - *a)); }
void MULTIPLY(char *a, char b) { assign_to_address(a, form_nibble(b * *a)); }
void DIVIDE(char *a, char b) { assign_to_address(a, form_nibble(floor(b / *a))); }
void MODULO(char *a, char b) { assign_to_address(a, form_nibble(b % *a)); }
void EQUAL(char *a, char b) { assign_to_address(a, b == *a); }
void GREATER(char *a, char b) { assign_to_address(a, b > *a); }
void SMALLER(char *a, char b) { assign_to_address(a, b < *a); }
void RSHIFT(char *a, char b) { assign_to_address(a, form_nibble(b >> *a)); }
void LSHIFT(char *a, char b) { assign_to_address(a, form_nibble(b << *a)); }

typedef void (*function) (char*, char);

void initialize_instructions(function *instructions) {
	instructions[0b0000] = &PASS;
	instructions[0b0001] = &ASSIGN;
	instructions[0b0010] = &NOT;
	instructions[0b0011] = &AND;
	instructions[0b0100] = &OR;
	instructions[0b0101] = &XOR;
	instructions[0b0110] = &ADD;
	instructions[0b0111] = &SUBTRACT;
	instructions[0b1000] = &MULTIPLY;
	instructions[0b1001] = &DIVIDE;
	instructions[0b1010] = &MODULO;
	instructions[0b1011] = &EQUAL;
	instructions[0b1100] = &GREATER;
	instructions[0b1101] = &SMALLER;
	instructions[0b1110] = &RSHIFT;
	instructions[0b1111] = &LSHIFT;
}

void initialize_registers(char *registers) {
	registers[0b0000] = 0; // Program Counter
	registers[0b0001] = 0; // Flags (Carry, Zero, Negative, Overflow)
	registers[0b0010] = 0; // Accumulator
	registers[0b0011] = 0; // Memory 1
	registers[0b0100] = 0; // Memory 2
	registers[0b0101] = 0; // Memory 3
	registers[0b0110] = 0; // Memory 4
	registers[0b0111] = 0; // Memory 5
	registers[0b1000] = 0; // Memory 6
	registers[0b1001] = 0; // Memory 7
	registers[0b1010] = 0; // Memory 8
	registers[0b1011] = 0; // Memory 9
	registers[0b1100] = 0; // Memory 10
	registers[0b1101] = 0; // Memory 11
	registers[0b1110] = 0; // Memory 12
	registers[0b1111] = 0; // Memory 13
}

void interpret(char *instruction, function *instructions, char *registers) {
	for (int i = 0; i < instruction_length; i++)
		instructions[instruction[0]](registers[instruction[1]], instruction[2]);
}

#endif
