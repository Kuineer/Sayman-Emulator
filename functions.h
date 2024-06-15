#ifndef functions
#define functions

#include <stdint.h>
#include <stdlib.h>

#include "properties.h"

struct bit_limiter {
	char nibble : word_size;
};

char form_nibble(char number) {
	struct bit_limiter result = { number };
	return result.nibble;
}

void assign_to_address(char *address, char value) {
	int *destination = (int*)(intptr_t) address;
	*destination = value;
}

char *byte_to_nibble_array(char *array) { // Add residual nibble handling.
	size_t elements_count = sizeof(array) / sizeof(char);

	char *d = (char*) malloc(sizeof(char) * elements_count);
	for (int i = 1; (i - 1) >> 1 < elements_count; i += 2) {
		char sample = array[i];

		char header = sample >> 4;
		char footer = sample - (header << 4);

		d[(i - 1) >> 1] = header << (8 + footer);
	}

	return d;
}

int char_count(const char *string, char token) {
	int count = 0;
	while (*string != '\0') {
		count += *string++ == token;
	}

	return count;
}

#endif
