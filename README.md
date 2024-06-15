# Index

0. Index
1. Basic Information
2. The Instruction Format
3. The Instruction Set and Their Assembly Equivalents
4. The Registers and Their Assembly Equivalents
5. The Flags and Their Assembly Equivalents
6. Implementations of Operations

# Basic Information

Desired clock frequency: 1 kHz (1000 Hz)
Word Size: 4 bits (a nibble)

# The Instruction Format

opcode - operand 1 / destination - operand 2

Examples in Sayman Assembly:

000000000000 = buffer acculumator 0
011100010010 = increment register1 2
001100100100 = or register2 4

# Operation Codes and Their Assembly Equivalents

0000 buffer
0001 not
0010 and
0011 or
0100 xor
0101 lshift
0110 rshift
0111 increment
1000 decrement
1001 add
1010 subtract
1011 multiply
1100 divide
1101 compare
1110 jump
1111 move

# Registers and Their Assembly Equivalents

0000 accumulator
0001
0010
0011
0100
0101
0110
0111
1000
1001
1010
1011
1100
1101
1110
1111

# Flags and Their Assembly Equivalents

0001 pcounter
0010 carry
0100 zero
1000 overflow

# Implementations of Operations

Let a and b be operand 1 and operand 2 respectively.

0000 buffer:

a bfr b

0001 not
0010 and
0011 or
0100 xor
0101 lshift
0110 rshift
0111 increment
1000 decrement
1001 add
1010 subtract
1011 multiply
1100 divide
1101 modulo
1110 jump
1111 move
