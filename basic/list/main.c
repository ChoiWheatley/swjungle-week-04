#include <assert.h>
#include <list.h>

int main(void) {
  NodePtr first = NULL;

  print_list(first);
  assert(0 == __len__(first));

  insert_left(&first, 10);
  print_list(first);
  assert(1 == __len__(first));

  insert_left(&first, 20);
  print_list(first);
  assert(2 == __len__(first));

  insert_left(&first, 30);
  print_list(first);
  assert(3 == __len__(first));

  insert_left(&first, 40);
  print_list(first);
  assert(4 == __len__(first));

  insert_left(&first, 50);
  print_list(first);
  assert(5 == __len__(first));

  pop_left(&first);
  print_list(first);
  assert(4 == __len__(first));

  pop_left(&first);
  print_list(first);
  assert(3 == __len__(first));

  pop_left(&first);
  print_list(first);
  assert(2 == __len__(first));

  pop_left(&first);
  print_list(first);
  assert(1 == __len__(first));

  pop_left(&first);
  print_list(first);
  assert(0 == __len__(first));

  pop_left(&first);
  print_list(first);
  assert(0 == __len__(first));

  free(first);
  return EXIT_SUCCESS;
}