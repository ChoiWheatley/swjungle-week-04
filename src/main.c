#include <stdio.h>

#include "rbtree.h"

int main(int argc, char *argv[]) {
  rbtree *tree = new_rbtree();
  printf("\n=== TEST BST ADD ===\n\n");
  {
    bst_insert(tree, 2);
    bst_insert(tree, 4);
    bst_insert(tree, 3);
    bst_insert(tree, 8);
    bst_insert(tree, 6);
    bst_insert(tree, 16);
    bst_insert(tree, 12);
  }
  printf("\n=== END TEST BST ADD ===\n");

  printf("\n=== TEST BFS ===\n\n");
  { travel_bfs(tree, print_node); }
  printf("\n=== END TEST BFS ===\n");
  return 0;
}