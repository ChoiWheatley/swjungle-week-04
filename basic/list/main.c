#include <list.h>

int main(void) {
  NodePtr first = NULL, second = NULL;
  MALLOC(first, sizeof(*first));
  MALLOC(second, sizeof(*second));

  first->data = 10;
  second->data = 20;
  first->link = second;
  second->link = NULL;

  free(first);
  free(second);
  return EXIT_SUCCESS;
}