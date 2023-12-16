#include "scanners/go.h"
#include "scanners/tf-idf.h"

int main(int argc, char *argv[]) {
  if (argc == 3) {
    printf("%s: %s\n", argv[1], argv[2]);
  } else {
    printf("USAGE: c-scanners COMMAND PATH\n"
           "\n"
           "  COMMAND: Refer list below\n"
           "  PATH   : Path to file\n");
    return EXIT_FAILURE;
  }

  // Compute byte offsets of alphanumeric tokens in file
  if (!strcmp(argv[1], "print-tokens")) {
    // TODO: Later make into command line arg
    const char *token_delim = " \n\t(){}[]";
    print_tokens(argv[2], token_delim);
    // USAGE:
    //   `./c-scanners print-tokens PATH |\
    //       sed -s 1d | sort | uniq`

  } else if (!strcmp(argv[1], "go-functions")) {
    go_functions(argv[2]);
  }

  return EXIT_SUCCESS;
}
