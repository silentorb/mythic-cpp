#include <malloc.h>
#include <memory.h>
#include "list.h"

void list_initialize(List *list, int stride, int capacity) {
  list->stride = stride;
  list->length = 0;
  list->capacity = capacity;
  list->data = capacity == 0 ? 0 : malloc(stride * capacity);
}

void list_free_data(List *list) {
  free(list->data);
  list->data = 0;
  list->length = 0;
  list->capacity = 0;
}

void list_push(List *list, void *item) {
  if (list->length == list->capacity) {
    list->capacity *= 2;
    list->data = realloc(list->data, list->stride * list->capacity);
  }
//  memcpy(list->data + list->stride * list->length++, item, list->stride);
}

void list_remove(List *list, void *item) {

}