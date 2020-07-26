#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "processGuard.h"

int childProcess(void* (*childFunction)(void *), void *arg, int fd[2]);
void* parentProcess(void *params, int fd[2]);

void* guard(void *params) {
  GuardParams *data = (GuardParams*) params;
  int fd[2];
  pipe(fd);

  if (!fork())
    return childProcess(data->childFunction, data->arg, fd);
  else
    return parentProcess(params, fd);
}

int childProcess(void* (*childFunction)(void *), void *arg, int fd[2]) {
  void* result = childFunction(arg);

  close(fd[0]);
  write(fd[1], result, sizeof(result));

  return result != NULL;
}

void* parentProcess(void *params, int fd[2]) {
  int stat;
  void* data;
  wait(&stat);
  printf("child ended\n");

  close(fd[1]);
  read(fd[0], data, 255);

  if(WIFEXITED(stat))
    guard(params);
  return data;
}
