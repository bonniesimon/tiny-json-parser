#include <stdio.h>
#include <stdlib.h>

#include "dynamic_array.h"

dynamic_array *init_dynamic_array(size_t size) {
  char **arr = malloc(size * sizeof(char **));

  dynamic_array *d_arr = malloc(sizeof(dynamic_array));

  d_arr->items = arr;
  d_arr->size = size;
  d_arr->capacity = 0;

  return d_arr;
}

void da_push(dynamic_array *da, char *value) {
  if (da->size == da->capacity) {
    da->size *= 2;
    da->items = realloc(da->items, da->size * sizeof(int));

    if (da->items == NULL) {
      printf("Error: Reallocation failed");
      exit(EXIT_FAILURE);
    }
  }

  da->items[da->capacity] = value;
  da->capacity++;
}

void da_free(dynamic_array *da) {
  free(da->items);
  free(da);
}
