#pragma once

typedef struct GuardParams {
  void* (*childFunction)(void *);
  void *arg;
} GuardParams;

void* startGuardThread(void *params);
void* guard(void *params);
