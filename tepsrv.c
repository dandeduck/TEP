#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "linear_map.h"
#include "tepsrv.h"

void add_request(char* request, request_t** requests, Entry* request_map, size_t* size) {
  *requests = (request_t*) realloc(*requests, (*size+1) *sizeof(request_t));
  (*requests)[*size] = get_value(request_map, request);
  *size += 1;
}
