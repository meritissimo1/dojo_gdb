#include <ecoa.h>

void *flag99(void *args) {
  // PEGADINHA
  int *arg;

  arg = (int *)args;
  printf("The real flag is not here- %d\n", *arg);
  pthread_exit(NULL);
}
