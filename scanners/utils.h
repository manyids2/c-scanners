#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Loads the entire content of file into a char* variable */
char *read_entire_file(const char *fileName);

char *s_get_substring(char *line, uint64_t start, uint64_t end);
