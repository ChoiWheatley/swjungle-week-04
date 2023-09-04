#include "rbtree.h"

#include <stdlib.h>

#ifdef DEBUG

#include <printers.h>
#include <stdio.h>

#endif

/**
 * helper functions
 */

void __rotate_left(rbtree *, node_t *u);
void __rotate_rght(rbtree *, node_t *u);
void __transplant(rbtree *, node_t *u, node_t *v);
void travel_bfs(const rbtree *, void (*callback)(const node_t *));
void travel_dfs(const rbtree *, void (*callback)(const node_t *));
void travel_bfs_mut(rbtree *, void (*callback)(node_t *));
void travel_dfs_mut(rbtree *, void (*callback)(node_t *));
node_t *subtree_min(rbtree *, node_t *u);
node_t *subtree_max(rbtree *, node_t *u);
void free_node(node_t *node);
#ifdef DEBUG
void print_node(const node_t *node);
void bst_insert(rbtree *t, const key_t key);
#endif

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)malloc(sizeof(rbtree));
  p->nil = (node_t *)malloc(sizeof(node_t));
  (*p->nil) = (node_t){.color = RBTREE_BLACK,
                       .key = (1 << 31) - 1,
                       .parent = NULL,
                       .left = NULL,
                       .right = NULL};
  p->root = p->nil;
  return p;
}

void delete_rbtree(rbtree *t) {
  // TODO: DFS 순회를 돌면서 free를 해주자.
  travel_dfs_mut(t, free_node);
  free(t);
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  // TODO: implement insert
  return t->root;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  node_t *cursor = t->root;

  while (cursor != t->nil && cursor->key == key) {
    if (key < cursor->key) {
      // go left
      cursor = cursor->left;
    } else if (key > cursor->key) {
      // go right
      cursor = cursor->right;
    } else {
      // found it!
      return cursor;
    }
  }
  return t->nil;
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

void travel_bfs_mut(rbtree *, void (*callback)(node_t *)) {}

void travel_dfs_mut(rbtree *, void (*callback)(node_t *)) {}

node_t *subtree_min(rbtree *t, node_t *u) { return NULL; }

node_t *subtree_max(rbtree *t, node_t *u) { return NULL; }

void free_node(node_t *node) { free(node); }

#ifdef DEBUG
void print_node(const node_t *node) { printf("%d, ", node->key); }

/// @brief 단순 이진검색트리 삽입연산을 구현해보자.
void bst_insert(rbtree *t, const key_t key) {}
#endif
