#include <stdlib.h>

typedef struct {
  size_t size;
  size_t capacity;
  char **items;
} dynamic_array;

dynamic_array *init_dynamic_array(size_t size);
void da_push(dynamic_array *da, char *value);
void da_free(dynamic_array *da);
