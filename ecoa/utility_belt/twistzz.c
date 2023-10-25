#include <ecoa.h>

void *flag11(void *args) {
  // Flag -> degaspizza
  int *arg;
  int n;

  n = 1;
  arg = (int *)args;
  printf("The real flag is here :D - %d\n", *arg);
  while (n) // you can use 'set var n=0' to break this loop
    ;
  pthread_exit(NULL);
}
