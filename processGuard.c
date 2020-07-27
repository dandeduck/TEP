#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "processGuard.h"

void* startGuardThread(void* (*guardedFunction)(void *), void *arg) {
  pthread_t thread0;
  void* returned;

  pthread_create(&thread0, NULL, guardedFunction, arg);
  pthread_join(thread0, &returned);

  if(!returned)
    return startGuardThread(guardedFunction, arg);
  return returned;
}
