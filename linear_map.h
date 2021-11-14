#pragma once

typedef struct Entry {
  char* key;
  void* (*func)(void*);
} Entry;

void* get_value(Entry* map, char* key);
