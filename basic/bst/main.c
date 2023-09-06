#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <rbtree.h>

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

  printf("\n=== TEST DFS ===\n");
  travel_dfs(tree, print_node);

  printf("\n=== END TEST DFS ===\n");

  printf("\nvvv TEST ARR vvv\n");
  size_t len = 9;
  key_t *arr = (key_t *)malloc(sizeof(key_t) * len);
  rbtree_to_array(tree, arr, len);

  printf("[");
  for (size_t i = 0; i < len; ++i) {
    printf("%d", arr[i]);
    if (i < len - 1) {
      printf(", ");
    }
  }
  printf("]\n");
  free(arr);
  printf("\n^^^ END TEST ARR ^^^\n");

  printf("\nvvv TEST LEFT ROTATION vvv\n");
  printf("BEFORE: \n");
  travel_bfs(tree, print_node);

  node_t *node2 = rbtree_find(tree, 2);
  assert(2 == node2->key);
  __rotate_left(tree, node2);

  printf("\nAFTER:\n");
  travel_bfs(tree, print_node);
  printf("\n^^^ END LEFT ROTATION ^^^\n");

  printf("\nvvv TEST RIGHT ROTATION vvv\n");
  node_t *node4 = rbtree_find(tree, 4);
  assert(4 == node4->key);
  __rotate_right(tree, node4);
  travel_bfs(tree, print_node);
  printf("\n^^^ END RIGHT ROTATION ^^^\n");

  printf("\nvvv TEST LEFT ROTATION vvv\n");
  node_t *node10 = rbtree_find(tree, 10);
  assert(10 == node10->key);
  __rotate_left(tree, node10);
  travel_bfs(tree, print_node);
  printf("\n^^^ END LEFT ROTATION ^^^\n");

  return 0;
}
