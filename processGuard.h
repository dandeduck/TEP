#ifndef HEADER_FILE
#define HEADER_FILE

struct GuardParams {
  void* (*childFunction) (void *);
  void *arg;
};

void guard(void* (*childFunction)(void *arg), void *arg);

#endif
