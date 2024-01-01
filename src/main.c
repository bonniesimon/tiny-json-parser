#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dynamic_array.h"
#include "file.h"

typedef struct {
  int line_number;
  char *code;
  char *cursor;
} Lexer;

void report(int line, char *where, char *message) {
  printf("line %d | %s :   %s\n", line, where, message);
}

void error(int line, char *message) { report(line, "", message); }

void skip_whitespace(char **cursor) {
  while (**cursor == ' ')
    (*cursor)++;
}

// We need to parse the key and value in here. This should be
// lex_key_and_value
void lex_key_or_value(char **cursor, dynamic_array *da) {
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

dynamic_array *lex(Lexer *lexer) {
  dynamic_array *da = init_dynamic_array(256);

  while (*(lexer->cursor) != '\0') {
    skip_whitespace(&lexer->cursor);

    if (*lexer->cursor == '{') {
      da_push(da, "{");
      lexer->cursor++;
    } else if (*(lexer->cursor) == '}') {
      da_push(da, "}");
      lexer->cursor++;
    } else if (*lexer->cursor == '\"') {
      da_push(da, "\"");
      lexer->cursor++;
      lex_key_or_value(&lexer->cursor, da);
      da_push(da, "\"");
      lexer->cursor++;
    } else if (*lexer->cursor == '\n') {
      lexer->line_number++;
      lexer->cursor++;
    } else if (*lexer->cursor == ':') {
      da_push(da, ":");
      lexer->cursor++;
      // Finding comma should be done inside lex_key_and_value.
    } else if (*lexer->cursor == ',') {
      da_push(da, ",");
      lexer->cursor++;
    } else {
      // pass
    }
  }

  return da;
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
  lexer.line_number = 1;
  lexer.cursor = lexer.code;

  dynamic_array *lex_result = lex(&lexer);

  da_pretty_print(lex_result);
  da_free(lex_result);
  return 0;
}
