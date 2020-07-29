#pragma once

void add_request(char* request, void* (***requests)(void*), Entry* request_map, size_t* size);
