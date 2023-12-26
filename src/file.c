#include <stdio.h>
#include <stdlib.h>

#include "file.h"

char *read_code(char *file_name) {
  FILE *json_file = fopen(file_name, "r");

  if (json_file == NULL) {
    printf("Error: Unable to read file\n");
    exit(EXIT_FAILURE);
  }

  fseek(json_file, 0, SEEK_END);
  long file_length = ftell(json_file);
  fseek(json_file, 0, SEEK_SET);

  char *code = malloc(file_length);

  if (code == NULL) {
    printf("Error: Unable to allocate memory for code\n");
    exit(EXIT_FAILURE);
  }

  fread(code, 1, file_length, json_file);

  fclose(json_file);

  return code;
}
