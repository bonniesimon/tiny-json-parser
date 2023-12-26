#include <stdio.h>
#include <stdlib.h>

#include "dynamic_array.h"
#include "file.h"

void report(int line, char *where, char *message) {
  printf("line %d | %s :   %s\n", line, where, message);
}

void error(int line, char *message) { report(line, "", message); }

void skip_whitespace(char *cursor) {
  while (*cursor == ' ')
    cursor++;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage: tiny [file.extension]\n");
    printf("Error: Insufficient arguments passed.\n");
    exit(EXIT_FAILURE);
  }

  char *file_name = argv[1];

  char *code = read_from_file(file_name);
  dynamic_array *da = init_dynamic_array(256);

  int line_number = 1;
  char *cursor = code;
  // printf("%d\t", line_number);

  while (*cursor != '\0') {
    skip_whitespace(cursor);

    switch (*cursor) {
    case '{':
      da_push(da, "{");
      break;
    case '}':
      da_push(da, "}");
      break;
    case '\"':
      da_push(da, "\"");
      break;
    case '\n':
      line_number++;
      // printf("%d\t", line_number);
      break;
    }

    cursor++;
  }

  for (size_t i = 0; i < da->capacity; i++) {
    printf("%s", da->items[i]);
  }

  da_free(da);
  return 0;
}
