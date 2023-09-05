#include <assert.h>
#include <rbtree.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  const key_t keys[] = {2, 9, 11, 32, 1, 8, 7, 5, 6, 94, 128, 31, 30, 29, 33};
  size_t len = sizeof(keys) / sizeof(key_t);
  rbtree *tree = new_rbtree();
  {
    printf("vvv TEST INSERT vvv\nvvv\n");
    travel_bfs(tree, print_node);
    for (size_t i = 0; i < len; ++i) {
      printf("insert(%4d): ", keys[i]);
      rbtree_insert(tree, keys[i]);
      travel_bfs(tree, print_node);
      printf("\n");
    }
    printf("^^^\n^^^ END TEST INSERT ^^^\n");
  }
  {
    printf("vvv TEST SORT vvv\nvvv\n");
    key_t submit[100] = {0};
    key_t answer[100] = {};
    memcpy(answer, keys, len * sizeof(key_t));
    rbtree_to_array(tree, submit, len);
    qsort(answer, len, sizeof(key_t), key_comp);
    assert(answer[0] == submit[0]);
    assert(answer[0] == rbtree_min(tree)->key);
    assert(answer[len - 1] == submit[len - 1]);
    assert(answer[len - 1] == rbtree_max(tree)->key);
    printf("OK >_o*\n");
    printf("^^^\n^^^ END TEST SORT ^^^\n");
  }
  delete_rbtree(tree);

  tree = new_rbtree();
  {
    printf("vvv TEST DUPLICATE ELEMENTS INSERT vvv\nvvv\n");
    key_t key = 10;
    size_t len = 100;
    for (size_t i = 0; i < len; ++i) {
      rbtree_insert(tree, key);
    }
    travel_bfs(tree, print_node);
    printf("\n");
    printf("^^^\n^^^ END DUPLICATE ELEMENTS INSERT ^^^\n");
  }
  delete_rbtree(tree);

  tree = new_rbtree();
  {
    printf("vvv TEST DELETE vvv\nvvv\n");
    for (size_t i = 0; i < len; ++i) {
      rbtree_insert(tree, keys[i]);
    }
    printf("Before: ");
    travel_bfs(tree, print_node);
    printf("\n");

    for (size_t i = 0; i < len; ++i) {
      key_t elem = keys[len - i - 1];
      key_t erased = rbtree_erase(tree, rbtree_find(tree, elem));
      assert(elem == erased);
      printf("after delete(%d): ", elem);
      travel_bfs(tree, print_node);
      printf("\n");
    }
    printf("\n^^^\n^^^ END DELETE ^^^\n");
  }
  delete_rbtree(tree);
}