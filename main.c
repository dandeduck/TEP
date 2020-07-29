#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "overwrite.h"
#include "linear_map.h"
#include "tepsrv.h"

void* func(void* word);

int main(int argc, char const *argv[]) {
  // printf("total written %d\n", overwriteDirectory("/home/quacky/dev/testing_ground/", "meow"));
  pthread_t handle_threat;
  Entry request_map[2];
  request_map[0].key = "gay";
  request_map[0].func = func;
  request_map[1].key = "second gay";
  request_map[1].func = NULL;
  void* (**requests)(void*);

  add_request("gay", &requests, request_map);
  printf("result: %s\n", (char*) requests[0]("gay"));

  //pthread_create(&thread0, NULL, guardedFunction, arg);

  //main loop
  // while(1) {
      //recieve request
      //start
  // }

  // pthread_join(handle_threat, NULL);

  return 0;
}

void* func(void* word) {
  sleep(1);
  return word;
}
