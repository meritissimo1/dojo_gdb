#include <ecoa.h>

int flip = 0;

int main(void) {
  printf("You can use 'refresh' to clean this prompt.");
  signal(SIGINT, flag);

  while (!0) {
    if (flip) {
      break;
    }
  }
  return (0);
}
