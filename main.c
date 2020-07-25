#include <stdio.h>
#include <stdlib.h>
#include "overwrite.h"

int main(int argc, char const *argv[]) {
  printf("total written %d\n", overwriteDirectory("/home/quacky/dev/testing_ground/", "meow"));

  return 0;
}
