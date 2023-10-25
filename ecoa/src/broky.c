#include <ecoa.h>

int main(void) {
  void *(*func[2])(void *) = {flag99, flag11};
  pthread_t thread[2];
  int nthreads;
  int i;

  nthreads = 40;
  i = 0;
  while (i < 2) {
    pthread_create(&thread[i], NULL, func[i], &nthreads);
    i++;
    nthreads++;
  }
  i = 0;
  while (i < 2) {
    pthread_join(thread[i], NULL);
    i++;
  }
  return (0);
}
