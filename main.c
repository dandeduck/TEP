#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>
#include "overwrite.h"
#include "processGuard.h"

void guard(void (*childFunction)(void *args), void *args);

void func(char* word) {
  printf("%s",word);
}

int main(int argc, char const *argv[]) {
  // printf("total written %d\n", overwriteDirectory("/home/quacky/dev/testing_ground/", "meow"));
  pthread_t thread0;
  struct GuardParams params;
  // void **parameters = malloc(sizeof(&func)*2);
  // (*parameters)[0] = &func;
  // (*parameters)[1] = "dick\n";
  pthread_create(&thread0, NULL, &guard, &func);

  return 0;
}
