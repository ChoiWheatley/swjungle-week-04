#include <list.h>

int main(void) {
  NodePtr first = NULL;

  print_list(first);

  insert_left(&first, 10);
  print_list(first);

  insert_left(&first, 20);
  print_list(first);

  insert_left(&first, 30);
  print_list(first);

  insert_left(&first, 40);
  print_list(first);

  insert_left(&first, 50);
  print_list(first);

  pop_left(&first);
  print_list(first);

  pop_left(&first);
  print_list(first);

  pop_left(&first);
  print_list(first);

  pop_left(&first);
  print_list(first);

  pop_left(&first);
  print_list(first);

  pop_left(&first);
  print_list(first);

  free(first);
  return EXIT_SUCCESS;
}