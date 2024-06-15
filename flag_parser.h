#ifndef flag_parser
#define flag_parser

#include <stdlib.h>
#include <string.h>

char *parse_flags(int argc, char **argv) {
	char *d = (char*) malloc(argc + 1);
	for (int i = 0; i < argc; i++)
		if (strcmp(argv[i][0], '-') == 0)
			strcpy(d[i], argv[i][1]);

	size_t size = strlen(d);

	d[size + 1] = '\0';

	d = realloc(d, size + 1);
	

	return d;
}

int *parse_flag_indexes(int argc, char **argv) {
	int *d = (int*) malloc(sizeof(int) * (argc + 1));
	for (int i = 0; i < argc; i++)
		if (strcmp(argv[i][0], '-') == 0 && strlen(argv[i]) == 2)
			d[i] = i;

	return d;
}

int is_flag(char *argument) {
	char *d = (char*) malloc(sizeof(char) * (strlen(argument) + 1));

	return (strcmp(argv[i][0], '-') == 0 && strlen(argv[i]) == 2) ? 1 : 0;
}

#endif
