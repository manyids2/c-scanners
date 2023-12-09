#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Loads the entire content of file into a char* variable */
char *read_entire_file(const char *fileName);

/* MACROS */

#define PRINT_STR_REPEAT(str, times)                                           \
  {                                                                            \
    for (int i = 0; i < times; ++i)                                            \
      printf("%s", str);                                                       \
    puts("");                                                                  \
  }
