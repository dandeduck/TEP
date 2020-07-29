#include <string.h>
#include "linear_map.h"

void* get_value(Entry* map, char* key) {
  for (size_t i = 0; i < sizeof(map); ++i)
    if(!strcmp(map[i].key, key))
      return map[i].func;
  return NULL;
}
