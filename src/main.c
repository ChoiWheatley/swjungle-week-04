#include <stdio.h>

#include "rbtree.h"

int main(int argc, char *argv[]) {
  rbtree *tree = new_rbtree();
  printf("\n=== TEST BST ADD ===\n\n");
  {
    bst_insert(tree, 2);
    travel_bfs(tree, print_node);
    printf("\n");
    bst_insert(tree, 4);
    travel_bfs(tree, print_node);
    printf("\n");
    bst_insert(tree, 1);
    travel_bfs(tree, print_node);
    printf("\n");
    bst_insert(tree, 3);
    travel_bfs(tree, print_node);
    printf("\n");
    bst_insert(tree, 10);
    travel_bfs(tree, print_node);
    printf("\n");
    bst_insert(tree, 8);
    travel_bfs(tree, print_node);
    printf("\n");
    bst_insert(tree, 6);
    travel_bfs(tree, print_node);
    printf("\n");
    bst_insert(tree, 16);
    travel_bfs(tree, print_node);
    printf("\n");
    bst_insert(tree, 12);
    travel_bfs(tree, print_node);
    printf("\n");
  }
  printf("\n=== END TEST BST ADD ===\n");

  return 0;
}