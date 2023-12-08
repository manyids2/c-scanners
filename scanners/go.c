#include "go.h"
#include <stdio.h>
#include <string.h>

// /home/x/fd/code/go/go-tufte/markdown/markdown.go

void go_functions(char *path) {
  char *content = read_entire_file(path);
  const char *line_delim = "\n";
  const char *token_delim = " \t";

  int in_function = 0;

  // Basic parsing of lines and words
  char *end_content;
  char *line = strtok_r(content, line_delim, &end_content);
  while (line != NULL) {
    char *end_token;
    char *token = strtok_r(line, token_delim, &end_token);
    // We want first token to mark start of function
    while (token != NULL) {
      if (!strcmp(token, "func")) {
        in_function = 1; // Next search for end bracket, till then print
      }
      if (in_function) {
        if (!strcmp(token, "{")) {
          in_function = 0;
          printf("\n");
        } else {
          printf("%s ", token);
        }
      }
      token = strtok_r(NULL, token_delim, &end_token);
    }
    line = strtok_r(NULL, line_delim, &end_content);
  }
}
