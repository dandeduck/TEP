#pragma once

typedef void* (*request_t)(void*);

void add_request(char* request, request_t** requests, Entry* request_map, size_t* size);
