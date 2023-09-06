#include <assert.h>
#include <len.h>
#include <rbtree.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const key_t keys[] = {2, 9, 11, 32, 1, 8, 7, 5, 6, 94, 128, 31, 30, 29, 33};
const size_t len = sizeof(keys) / sizeof(key_t);

void test_insert() {
  rbtree *tree = new_rbtree();
  printf("vvv %s vvv\nvvv\n", __func__);
  travel_bfs(tree, print_node);
  for (size_t i = 0; i < len; ++i) {
    printf("insert(%4d): ", keys[i]);
    rbtree_insert(tree, keys[i]);
    travel_bfs(tree, print_node);
    printf("\n");
  }
  printf("^^^\n^^^ END %s ^^^\n", __func__);
  delete_rbtree(tree);
}

void test_sort() {
  rbtree *tree = new_rbtree();
  for (size_t i = 0; i < len; ++i) {
    key_t elem = keys[i];
    rbtree_insert(tree, elem);
  }
  printf("vvv %s vvv\nvvv\n", __func__);

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

  printf("^^^\n^^^ END %s ^^^\n", __func__);
  delete_rbtree(tree);
}

void test_duplicates() {
  rbtree *tree = new_rbtree();
  printf("vvv TEST DUPLICATE ELEMENTS INSERT vvv\nvvv\n");
  key_t key = 10;
  size_t len = 100;
  for (size_t i = 0; i < len; ++i) {
    rbtree_insert(tree, key);
  }
  travel_bfs(tree, print_node);
  printf("\n");
  printf("^^^\n^^^ END DUPLICATE ELEMENTS INSERT ^^^\n");
  delete_rbtree(tree);
}

void test_delete() {
  rbtree *tree = new_rbtree();
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
  delete_rbtree(tree);
}

void test_rand() {
  const size_t MAX_SIZE = 10000;
  rbtree *tree = new_rbtree();
  printf("\nvvv %s vvv\nvvv\n", __func__);

  printf("===creating random numbers...===\n");
  key_t *arr = (key_t *)malloc(MAX_SIZE * sizeof(key_t));
  srand((unsigned)time(NULL));
  for (size_t i = 0; i < MAX_SIZE; i++) {
    key_t e = rand() % 100;
    arr[i] = e;
    rbtree_insert(tree, e);
  }
  printf("\n===OK===\n");
  // printf("===dfs result: ===\n\t");
  // travel_dfs(tree, print_node);
  // printf("\n");

  printf("===find and erase...===\n");
  for (size_t i = 0; i < MAX_SIZE; ++i) {
    node_t *p = rbtree_find(tree, arr[i]);
    assert(p != NULL);
    assert(p != tree->nil);
    assert(p->key == arr[i]);
    rbtree_erase(tree, p);
    // printf("===after delete(%d): ===\n\t", arr[i]);
    // travel_dfs(tree, print_node);
    // printf("\n");
  }
  printf("===OK===\n");

  printf("===after all deletion...===\n");
  for (size_t i = 0; i < MAX_SIZE; ++i) {
    node_t *p = rbtree_find(tree, arr[i]);
    assert(p == NULL);
  }

  printf("\n^^^\n^^^ END %s ^^^\n", __func__);
  delete_rbtree(tree);
}

void test_must_fail() {
  rbtree *t = new_rbtree();
  key_t arr[] = {72, 94, 20, 77, 31, 92, 71, 25, 15, 98,
                 70, 38, 10, 8,  14, 5,  27, 50, 64, 14};
  size_t len = sizeof(arr) / sizeof(key_t);
  assert(len == 20);
  for (size_t i = 0; i < len; ++i) {
    key_t e = arr[i];
    rbtree_insert(t, e);
  }
  printf("===bfs result===:\n");
  travel_bfs(t, print_node);
  printf("\n");

  for (size_t i = 0; i < len; ++i) {
    key_t e = arr[i];
    printf("===after delete(%5d): \n", e);
    node_t *p = rbtree_find(t, e);
    rbtree_erase(t, p);
    travel_bfs(t, print_node_verbose);
    printf("\n");
  }
  delete_rbtree(t);
}

int main(int argc, char *argv[]) {
  // test_insert();
  // test_sort();
  // test_duplicates();
  // test_delete();
  test_rand();
  // test_must_fail();
}