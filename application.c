#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "functions.h"
#include "interpreter.h"
#include "properties.h"

int disable_clock, instructions_to_run, record, snapshot = 0;

void put_registers(FILE *file_pointer) {
	fprintf(file_pointer,
		"0b0000 (Program Counter): "
		"0b0001 (Flags): "
		"0b0010 (Accumulator): "
		"0b0011 (Memory 1): "
		"0b0100 (Memory 2): "
		"0b0101 (Memory 3): "
		"0b0110 (Memory 4): "
		"0b0111 (Memory 5): "
		"0b1000 (Memory 6): "
		"0b1001 (Memory 7): "
		"0b1010 (Memory 8): "
		"0b1011 (Memory 9): "
		"0b1100 (Memory 10): "
		"0b1101 (Memory 11): "
		"0b1110 (Memory 12): "
		"0b1111 (Memory 13): ",
	registers[0b0000], registers[0b0001], registers[0b0010], registers[0b0011], registers[0b0100], registers[0b0101], registers[0b0110], registers[0b0111], registers[0b1000], registers[0b1001], registers[0b1010], registers[0b1011], registers[0b1100], registers[0b1101], registers[0b1110], registers[0b1111]);
}

void apply_flags(char *flags, int *flag_indexes, char **argv) {
	size_t size = strlen(flags);

	int size_int = (int) size;
	for (int i = 0; i < size_int; i++) {
		char flag = flags[i];

		if (strchr(flags, 'h') != NULL && flags[0] == 'h') {
			perror("[ERROR] The flag '-h' can't be used at the same time with any other flag.");

			exit(1);
		} else if (char_count(flags, 'f') > 1 || char_count(flags, 'p') > 1 || char_count(flags, 'd') > 1 || char_count(flags, 'r') > 1 || char_count(flags, 'e') > 1 || char_count(flags, 'i') > 1) {
			fprintf(stderr, "[ERROR] The flag '-%c' can't be used more than once.", flag);

			exit(1);
		}

		switch (flag) {
			case 'h':
				puts("HELP:\n\n"
					 "1. Help\n"
					 "-h | Show the help text (Can't be used at the same time with any other flag.)\n\n"

					 "2. Clock Settings\n"
					 "-f <kilohertz> | Set a custom clock frequency in kHz (Can't be used at the same time with '-p' since it's the reverse of period.)\n"
					 "-p <milliseconds> | Set a custom clock period in milliseconds (Can't be used at the same time with '-f' since it's the reverse of frequency.)\n"
					 "-d | Disable the emulator clock (The interpreting speed will become hardware-dependent.)\n\n"

					 "3. Recording\n"
					 "-r | Record the changes in registers and, simultaneously, save it as a text file at 'records' directory\n"
					 "-s | After the program exits, take a snapshot of the data inside the registers and save it as a text file at 'records' directory\n\n"

					 "4. Execution Settings\n"
					 "-i <number> | Set the number of instructions to run (The program will always exit when it has reached the end of the file.)");

				break;
			case 'f':
				if (strchr(flags, 'p') != NULL) {
					perror("[ERROR] The flag '-f' can't be used at the same time with the flag '-p' since period is the reverse of frequency.\n");

					exit(1);
				}

				int flag_index = flag_indexes[((ptrdiff_t) strchr(flags, 'f') - flags) + 1];
				int parameter = argv[flag_index + 1];
				if (is_flag(flags[flag_index]) || flag_index == NULL) {
					perror("[ERROR] The flag '-f' requires a parameter that comes after it.");

					exit(1);
				} else if (!isdigit(parameter)) {
					perror("[ERROR] The parameter after the flag '-f' must be a number.");

					exit(1);
				}

				clock_period_ms = 1 / parameter;

				break;
			case 'p':
				if (strchr(flags, 'f') != NULL) {
					perror("[ERROR] The flag '-p' can't be used at the same time with the flag '-f' since frequency is the reverse of period.\n");

					exit(1);
				}

				int flag_index = flag_indexes[((ptrdiff_t) strchr(flags, 'p') - flags) + 1];
				int parameter = argv[flag_index + 2];
				if (is_flag(flags[flag_index]) || flag_index == NULL) {
					perror("[ERROR] The flag '-p' requires a parameter that comes after it.");

					exit(1);
				} else if (!isdigit(parameter)) {
					perror("[ERROR] The parameter after the flag '-p' must be a number.");

					exit(1);
				} else if (parameter <= 0) {
					perror("[ERROR] The parameter after the flag '-p' must be greater than 0.");
				}

				clock_period_ms = parameter;

				break;
			case 'd':
				if (strchr(flags, 'f') != NULL && strchr(flags, 'p')) {
					perror("[ERROR] The flags '-f' and '-p' can't be used at the same time with the flag '-d' as they're the clock settings, where '-d' disables the clock.");

					exit(1);
				}

				disable_clock = 1;

				break;
			case 'r':
				record = 1

				break;
			case 's':
				snapshot = 1

				break;
			case 'i':
				int flag_index = flag_indexes[((ptrdiff_t) strchr(flags, 'i') - flags) + 1];
				int parameter = argv[flag_index + 1];
				if (is_flag(flags[flag_index]) || flag_index == NULL) {
					perror("[ERROR] The flag '-i' requires a parameter that comes after it.");

					exit(1);
				} else if (!isnumber(parameter)) {
					perror("[ERROR] The parameter after the flag '-i' must be a number.");

					exit(1);
				} else if (parameter <= 0) {
					perror("[ERROR] The parameter after the flag '-i' must be greater than 0.");
				}

				instructions_to_run = atoi(parameter);

				break;
			default:
				fprintf(stderr, "[ERROR] Unknown flag: '-%c'.\n", flag);

				exit(1);
			}
		}
	}
}

int main(int argc, char **argv) { // Add flags, especially resource usage-oriented,  and a advanced flag parser.
	if (argc != 2) {
		perror("[ERROR] Insufficient or too many arguments. The emulator needs an argument that specifies a binary file path.\n");

		exit(1);
	}

	char *flags = malloc(sizeof(char*) * argc);
	char *flag_indexes = malloc(sizeof(char*) * argc);
	apply_flags(flags, flag_indexes, argv);
	free(flags);
	free(flag_indexes);

	FILE *mc = fopen(argv[1], "rb");
	if (mc == NULL) {
		fprintf(stderr, "[ERROR] Can't open file: %s, please make sure that a file with that name exists and the emulator has enough permissions to open it.\n", argv[1]);

		exit(1);
	}

	fseek(mc, 0, SEEK_END);
	size_t file_size = ftell(mc);
	rewind(mc);

	char *buffer = (char*) malloc(file_size);
	if (buffer == NULL) {
		perror("[ERROR] Can't allocate enough memory to read the specified file.\n");

		exit(1);
	}

	size_t bytes_read = fread(buffer, 1, file_size, mc);
	if (bytes_read != file_size) {
		perror("[ERROR] Can't copy the specified file into the memory. Please make sure that there is enough space in memory.\n");

		exit(1);
	}

	size_t array_size = floor(file_size / instruction_length)

	function *instructions = (char*) malloc(array_size);
	memcpy(instructions, bytes_to_nibble_array(buffer), array_size);

	instructions = (function*) realloc(instructions, sizeof(function) * instruction_count);
	char *registers = (char*) malloc(register_count);

	initialize_instructions(instructions);
	initialize_registers(registers);

	if (instructions_to_run == 0)
		instructions_to_run = array_size;

	for (int i = 0; i < instructions_to_run; i++) {
		interpret(instructions[i], instructions, registers);

		if (record) {
			FILE *file_pointer = fopen("Records.log", "a");
			put_registers(file_pointer);

		}

		usleep(clock_period_ms);

		registers[0b0000] = !registers[0b0000];
		ADD(&registers[0b0000], 1);
	}

	if (snapshot) {
		FILE *file_pointer = fopen("Snapshots.log", "a");
		put_registers(file_pointer);
	}

    free(instructions);
    free(registers);

	fclose(mc);
	free(buffer);

	return 0;
}
