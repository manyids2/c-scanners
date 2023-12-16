#include "utils.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

void print_tokens(char *path, const char *token_delim) {
  char *content = read_entire_file(path);
  char *end_token;
  char *token = strtok_r(content, token_delim, &end_token);
  while (token != NULL) {
    // TODO: Cannot count bytes skipped!! - so can only store refs to docs, not
    // byte positions :(
    int useful = 1;
    int len = strlen(token);
    for (int i = 0; i < len; i++) {
      if (!isalnum(token[i])) {
        useful = 0;
      }
    }
    if (useful) {
      printf("%s\n", token);
    }
    token = strtok_r(NULL, token_delim, &end_token);
  }
}
