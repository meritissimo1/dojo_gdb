#ifndef ECOA_H
#define ECOA_H

#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

extern int flip;

void flag(int signal);
void flag42(void);
void *flag99(void *args);
void *flag11(void *args);

#endif
