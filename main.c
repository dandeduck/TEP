#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "overwrite.h"
#include "processGuard.h"

void* func(void* word);

int main(int argc, char const *argv[]) {
  // printf("total written %d\n", overwriteDirectory("/home/quacky/dev/testing_ground/", "meow"));
  printf("returned %s\n", (char*)startGuardThread(func, "thread stuff\n"));

  return 0;
}

void* func(void* word) {
  printf("%s",(char*)word);
  sleep(1);

  return "gay?";
}
