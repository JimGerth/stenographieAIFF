#include <stdio.h>

typedef struct {
  int x, y;
} vector2D;

int main() {

  vector2D vector1 = {3, 8};

  printf("%p %p\n", &vector1.x, &vector1.y);

  return 0;
}
