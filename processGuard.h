#pragma once

typedef struct GuardParams {
  void *(*childFunction) (void *);
  void *arg;
} GuardParams;

void guard(GuardParams *params);
