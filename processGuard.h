#pragma once

void* startGuardThread(void* (*guardedFunction)(void *), void *arg);
