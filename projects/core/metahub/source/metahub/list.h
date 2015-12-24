#pragma once

typedef struct List {
    int stride;
    int length;
    int capacity;
    void *data;
} List;

void list_initialize(List *list, int stride, int capacity);
void list_push(List *list, void *item);
void list_remove(List *list, void *item);
void list_free_data(List *list);
