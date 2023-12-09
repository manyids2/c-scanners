#include "utils.h"

/* Loads the entire content of file into a char* variable */
char *read_entire_file(const char *fileName) {
  FILE *fp;
  long size = 0;
  char *content;

  /* Read File to get size */
  fp = fopen(fileName, "rb");
  if (fp == NULL) {
    return "";
  }
  fseek(fp, 0L, SEEK_END);
  size = ftell(fp) + 1;
  fclose(fp);

  /* Read File for content */
  fp = fopen(fileName, "r");
  content = (char *)memset(malloc(size), '\0', size);
  fread(content, 1, size - 1, fp);
  fclose(fp);

  return content;
}
