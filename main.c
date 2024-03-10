#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "instructions/instructions.h"

char **split_every(const char** input, int n) {
	int len = strlen(input);
	int numSubstrings = (len + n - 1) / n;

	char **substrings = (char**)malloc(numSubstrings * sizeof(char*));
	if (substrings == NULL) {
		fprintf(stderr, "Memory allocation failed.");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < numSubstrings; i++) {
		substrings[i] = (char*)malloc((n+1) * sizeof(char));
		if (substrings == NULL) {
                	fprintf(stderr, "Memory allocation failed.");
                	exit(EXIT_FAILURE);
        	};
		strncpy(substrings[i], input + i * n, n);
		substrings[i][n] = '\n';
	};

	return substrings;
};

int main() {
	while (1) {
		char scan[13];
		printf("Send: ");
		scanf("%s", &scan);

		const char **received = split_every(scan, 3);
		const int instruction = atoi(received[0]);
		const int o1 = atoi(received[1]);
		const int o2 = atoi(received[2]);

		instructions[instruction](o1, o2);
	};

	return 0;
};
