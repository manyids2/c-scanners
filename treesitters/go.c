#include "utils.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tree_sitter/api.h>

// Declare the `tree_sitter_go` function, which is
// implemented by the `tree-sitter-go` library.
TSLanguage *tree_sitter_go();

#define MAX_TOKEN_LENGTH 1024

char *token;

void print_tree(TSNode n, int indent, char *content, char *token) {
  PRINT_STR_REPEAT(" ", indent)
  if (strcmp(ts_node_type(n), "\n")) {
    printf("%30s: %3d, %3d -> ", ts_node_type(n), ts_node_start_byte(n),
           ts_node_end_byte(n));
  } else {
    printf("%30s: %3d, %3d -> ", "newline", ts_node_start_byte(n),
           ts_node_end_byte(n));
  }

  if (ts_node_child_count(n) > 0) {
    // If it has children, walk them
    for (int i = 0; i < ts_node_child_count(n); i++) {
      print_tree(ts_node_child(n, i), indent + 1, content, token);
    }
  } else {
    // Else primitive?, so print it? -- Not working
    // How to avoid memset, etc?
    // we just want to point to content at start_byte, and pring a given length
    uint32_t start_byte, end_byte, len;
    start_byte = ts_node_start_byte(n);
    end_byte = ts_node_end_byte(n);
    len = end_byte - start_byte;
    memset(token, 0, MAX_TOKEN_LENGTH * sizeof(*token));
    strncpy(token, &content[start_byte], len);
    printf("%s", token);
  }
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("USAGE: ts-go PATH\n"
           "\n"
           "  PATH: Path to file ( path to go file )\n");
    return EXIT_FAILURE;
  }
  // Create a parser.
  TSParser *parser = ts_parser_new();

  // Set the parser's language (go in this case).
  ts_parser_set_language(parser, tree_sitter_go());

  // Build a syntax tree based on source code stored in a string.
  char *content = read_entire_file(argv[1]);
  TSTree *tree = ts_parser_parse_string(parser, NULL, content, strlen(content));

  // Get root node
  TSNode root_node = ts_tree_root_node(tree);

  // Walk tree to print back content, alloc for token here
  char *token = malloc(sizeof(char) * MAX_TOKEN_LENGTH);
  print_tree(root_node, 0, content, token);
  free(token);

  // // Print the syntax tree as an S-expression.
  // char *string = ts_node_string(root_node);
  // printf("Syntax tree: %s\n", string);

  // Free all of the heap-allocated memory.
  // free(string);
  ts_tree_delete(tree);
  ts_parser_delete(parser);
  return 0;
}
