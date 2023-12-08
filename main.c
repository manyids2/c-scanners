#include "scanners/go.h"

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

  if (!strcmp(argv[1], "go-functions")) {
    go_functions(argv[2]);
  }

  return EXIT_SUCCESS;
}
