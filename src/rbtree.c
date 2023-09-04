#include "rbtree.h"

#include <stdlib.h>

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  // TODO: initialize struct if needed
  return p;
}

void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  free(t);
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  // TODO: implement insert
  return t->root;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase
  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  return 0;
}

void __rotate_left(rbtree *t, node_t *u) {}

void __rotate_rght(rbtree *t, node_t *u) {}

void __transplant(rbtree *t, node_t *u, node_t *v) {}

void travel_bfs(const rbtree *t, void (*callback)(const node_t *)) {}

void travel_dfs(const rbtree *t, void (*callback)(const node_t *)) {}

node_t *subtree_min(rbtree *t, node_t *u) { return NULL; }

node_t *subtree_max(rbtree *t, node_t *u) { return NULL; }
