#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "linear_map.h"
#include "tepsrv.h"

void add_request(char* request, void* (***requests)(void*), Entry* request_map, size_t* size) {
  *requests = (void* (**)(void*)) realloc(*requests, *size+sizeof(**requests));
  (*requests)[*size] = get_value(request_map, request);
  *size += 1;
}
