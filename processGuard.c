#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "processGuard.h"

void guard(GuardParams *params) {
  if (!fork())
    (*params->childFunction)(params->arg);
  else {
    wait(NULL);
    guard(params);
  }
}
