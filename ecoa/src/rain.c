#include <ecoa.h>

int main(void) {
  int pid;

  pid = fork();
  if (pid == 0)
    flag42();
  else
    printf("Dad!\n");
  return (0);
}
