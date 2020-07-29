#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "linear_map.h"
#include "tepsrv.h"

void add_request(char* request, void* (***requests)(void*), Entry* request_map) {
  *requests = (void* (**)(void*)) realloc(*requests, sizeof(*requests)+sizeof(**requests));
  (*requests)[sizeof(**requests)/sizeof(*requests) - 1] = get_value(request_map, request);
}
