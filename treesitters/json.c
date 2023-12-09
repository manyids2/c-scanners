#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tree_sitter/api.h>
#include "utils.h"

// Declare the `tree_sitter_json` function, which is
// implemented by the `tree-sitter-json` library.
TSLanguage *tree_sitter_json();

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("USAGE: ts-json PATH\n"
           "\n"
           "  PATH: Path to file ( path to json file )\n");
    return EXIT_FAILURE;
  }
  // Create a parser.
  TSParser *parser = ts_parser_new();

  // Set the parser's language (JSON in this case).
  ts_parser_set_language(parser, tree_sitter_json());

  // Build a syntax tree based on source code stored in a string.
  char *source_code = read_entire_file(argv[1]);
  TSTree *tree =
      ts_parser_parse_string(parser, NULL, source_code, strlen(source_code));

  // Print the syntax tree as an S-expression.
  TSNode root_node = ts_tree_root_node(tree);
  char *string = ts_node_string(root_node);
  printf("Syntax tree: %s\n", string);

  // Free all of the heap-allocated memory.
  free(string);
  ts_tree_delete(tree);
  ts_parser_delete(parser);
  return 0;
}
