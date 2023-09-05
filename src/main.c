#include <assert.h>
#include <rbtree.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  {
    printf("vvv TEST INSERT vvv\nvvv\n");
    rbtree *tree = new_rbtree();
    travel_bfs(tree, print_node);
    key_t keys[] = {2, 9, 11, 32, 1, 8, 7, 5, 6, 94, 128, 31, 30, 29, 33};
    size_t len = sizeof(keys) / sizeof(key_t);
    for (size_t i = 0; i < len; ++i) {
      printf("insert(%4d): ", keys[i]);
      rbtree_insert(tree, keys[i]);
      travel_bfs(tree, print_node);
      printf("\n");
    }
    delete_rbtree(tree);
    printf("^^^\n^^^ END TEST INSERT ^^^\n");
  }

  {
    printf("vvv TEST DUPLICATE ELEMENTS INSERT vvv\nvvv\n");
    rbtree *tree = new_rbtree();
    key_t key = 10;
    size_t len = 100;
    for (size_t i = 0; i < len; ++i) {
      rbtree_insert(tree, key);
    }
    travel_bfs(tree, print_node);
    delete_rbtree(tree);
    printf("\n");
    printf("^^^\n^^^ END DUPLICATE ELEMENTS INSERT ^^^\n");
  }
}