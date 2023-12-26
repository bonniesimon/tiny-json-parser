#include <stdio.h>
#include <stdlib.h>

#include "file.h"

void report(int line, char *where, char *message) {
  printf("line %d | %s :   %s\n", line, where, message);
}

void error(int line, char *message) { report(line, "", message); }

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage: tiny [file.extension]\n");
    printf("Error: Insufficient arguments passed.\n");
    exit(EXIT_FAILURE);
  }

  char *file_name = argv[1];

  char *code = read_code(file_name);
  printf("%s\n", code);

  return 0;
}
