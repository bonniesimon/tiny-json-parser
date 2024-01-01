#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dynamic_array.h"
#include "file.h"

void report(int line, char *where, char *message) {
  printf("line %d | %s :   %s\n", line, where, message);
}

void error(int line, char *message) { report(line, "", message); }

typedef struct {
  int line_number;
  char *code;
  char *cursor;
} Lexer;

void skip_whitespace(char *cursor) {
  while (*cursor == ' ')
    cursor++;
}

void lex_key_value(char **cursor, dynamic_array *da) {
  char *key_start = malloc(sizeof(char));
  if (key_start == NULL) {
    printf("Error: key_start not allocated.\n");
    exit(EXIT_FAILURE);
  }

  key_start = *cursor;

  while (**cursor != '\"') {
    *cursor = *cursor + 1;
  }

  int len = *cursor - key_start;

  char *key = malloc(len * sizeof(char *));
  strncpy(key, key_start, len);

  da_push(da, key);
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage: tiny [file.extension]\n");
    printf("Error: Insufficient arguments passed.\n");
    exit(EXIT_FAILURE);
  }

  char *file_name = argv[1];

  Lexer lexer = {0};

  lexer.code = read_from_file(file_name);
  dynamic_array *da = init_dynamic_array(256);

  lexer.line_number = 1;
  lexer.cursor = lexer.code;

  while (*lexer.cursor != '\0') {
    skip_whitespace(lexer.cursor);

    switch (*lexer.cursor) {
    case '{':
      da_push(da, "{");
      break;
    case '}':
      da_push(da, "}");
      break;
    case '\"':
      da_push(da, "\"");
      lexer.cursor++;
      lex_key_value(&lexer.cursor, da);
      da_push(da, "\"");
      break;
    case '\n':
      lexer.line_number++;
      break;
    case ':':
      da_push(da, ":");
      break;
    }

    lexer.cursor++;
  }

  for (size_t i = 0; i < da->capacity; i++) {
    printf("%s\n", da->items[i]);

    // if (i == 0)
    //   printf("[");

    // printf(" %s ", da->items[i]);

    // if (i == da->capacity - 1) {
    //   printf("]");
    // } else {
    //   printf(",");
    // }
  }

  da_free(da);
  return 0;
}
