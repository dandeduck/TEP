#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "processGuard.h"

void guard(void* (*childFunction)(void *arg), void *arg) {
  if (!fork())
    (*childFunction)(arg);
  else {
    wait(NULL);
    guard(childFunction, arg);
  }
}
