#include "rbtree.h"

#include <queue.h>
#include <stack.h>
#include <stdbool.h>
#include <stdlib.h>

#ifdef DEBUG

#include <printers.h>
#include <stdio.h>

#endif

typedef void Fn(rbtree *, node_t *);

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)malloc(sizeof(rbtree));
  p->nil = (node_t *)malloc(sizeof(node_t));
  (*p->nil) = (node_t){.color = RBTREE_BLACK,
                       .key = (1 << 31) - 1,
                       .parent = p->nil,
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

/// @brief find should return the node with the key or NULL if no such node
/// exists
node_t *rbtree_find(const rbtree *t, const key_t key) {
  node_t *cursor = t->root;

  while (cursor != t->nil || cursor->key == key) {
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
  return NULL;
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

/// @brief Using DFS travelsal
int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  Stack stack = {{NULL}, 0};
  node_t *cur = t->root;
  size_t idx = 0;

  while ((!stack_empty(&stack) || cur != t->nil) && idx < n) {
    if (cur != t->nil) {
      stack_push(&stack, cur);
      cur = cur->left;
    } else {
      cur = stack_pop(&stack);
      arr[idx] = cur->key;
      idx += 1;
      cur = cur->right;
    }
  }
}

/// @brief 노드 u를 기준으로 왼쪽 회전을 수행
void __rotate_left(rbtree *t, node_t *u) {
  if (!t || !u || u == t->nil || u->left == t->nil) {
    return;
  }
  if (u == t->root) {
    t->root = u->right;
  }
  node_t *right = u->right;
  u->right = right->left;
  right->left->parent = u;
  if (u == u->parent->left) {
    u->parent->left = right;
  } else {
    u->parent->right = right;
  }
  right->parent = u->parent;
  u->parent = right;
  right->left = u;
}

void __rotate_right(rbtree *t, node_t *u) {
  if (!t || !u || u == t->nil) {
    return;
  }
  if (u == t->root) {
    t->root = u->left;
  }
  node_t *left = u->left;
  u->left = left->right;
  left->right->parent = u;
  if (u == u->parent->left) {
    u->parent->left = left;
  } else {
    u->parent->right = left;
  }
  left->parent = u->parent;
  u->parent = left;
  left->right = u;
}

void __transplant(rbtree *t, node_t *u, node_t *v) {}

void travel_bfs(const rbtree *t,
                void (*callback)(const rbtree *t, const node_t *)) {
  Queue queue = {{NULL}, 0, 0};
  queue_push(&queue, t->root);

  while (!queue_empty(&queue)) {
    node_t *cur = queue_pop(&queue);

    callback(t, cur);  // do visit

    if (cur == t->nil) {
      continue;
    }

    queue_push(&queue, cur->left);
    queue_push(&queue, cur->right);
  }
}

void travel_dfs(const rbtree *t,
                void (*callback)(const rbtree *t, const node_t *)) {
  Stack stack = {{NULL}, 0};
  node_t *cur = t->root;

  while (!stack_empty(&stack) || cur != t->nil) {
    if (cur != t->nil) {
      stack_push(&stack, cur);
      cur = cur->left;
    } else {
      cur = stack_pop(&stack);
      callback(t, cur);
      cur = cur->right;
    }
  }
}

void travel_bfs_mut(rbtree *t, void (*callback)(const rbtree *t, node_t *)) {
  Queue queue = {{NULL}, 0, 0};
  queue_push(&queue, t->root);

  while (!queue_empty(&queue)) {
    node_t *cur = queue_pop(&queue);

    callback(t, cur);  // do visit

    if (cur == t->nil) {
      continue;
    }

    queue_push(&queue, cur->left);
    queue_push(&queue, cur->right);
  }
}

void travel_dfs_mut(rbtree *t, void (*callback)(const rbtree *, node_t *)) {
  Stack stack = {{NULL}, 0};
  node_t *cur = t->root;

  while (!stack_empty(&stack) || cur != t->nil) {
    if (cur != t->nil) {
      stack_push(&stack, cur);
      cur = cur->left;
    } else {
      cur = stack_pop(&stack);
      callback(t, cur);
      cur = cur->right;
    }
  }
}

node_t *subtree_min(rbtree *t, node_t *u) {
  node_t *cur = t->root;
  node_t *prev = cur;

  while (cur != t->nil) {
    prev = cur;
    cur = cur->left;
  }

  return prev;
}

node_t *subtree_max(rbtree *t, node_t *u) {
  node_t *cur = t->root;
  node_t *prev = cur;

  while (cur != t->nil) {
    prev = cur;
    cur = cur->right;
  }

  return prev;
}

void free_node(const rbtree *t, node_t *node) { free(node); }

#ifdef DEBUG
void print_node_verbose(const rbtree *t, const node_t *node) {
#define MAX_STR 255

  char skey[MAX_STR] = "NIL";
  char sleft[MAX_STR] = "NIL";
  char sright[MAX_STR] = "NIL";
  char sparent[MAX_STR] = "NIL";
  if (node == t->nil) {
    printf("NIL\n");
    return;
  }
  snprintf(skey, MAX_STR, "%d", node->key);
  if (node->left != t->nil) {
    snprintf(sleft, MAX_STR, "%d", node->left->key);
  }
  if (node->right != t->nil) {
    snprintf(sright, MAX_STR, "%d", node->right->key);
  }
  if (node->parent != t->nil) {
    snprintf(sparent, MAX_STR, "%d", node->parent->key);
  }
  printf("key: %s: (left: %s, right: %s, parent: %s)\n", skey, sleft, sright,
         sparent);

#undef MAX_STR
}
void print_node(const rbtree *t, const node_t *node) {
  if (node == t->nil) {
    printf("NIL, ");
    return;
  }
  printf("%d(%c), ", node->key, node->color ? 'b' : 'r');
}

/// @brief 단순 이진검색트리 삽입연산을 구현해보자.
void bst_insert(rbtree *t, const key_t key) {
  if (t->root == t->nil) {
    // empty tree
    t->root = (node_t *)malloc(sizeof(node_t));
    *t->root = (node_t){RBTREE_BLACK, key, t->nil, t->nil, t->nil};
    return;
  }
  // node_t *cur = rbtree_find(t, key);
  node_t *cur = t->root;
  node_t *prev = cur;

  while (cur != t->nil && cur->key != key) {
    prev = cur;
    if (key < cur->key) {
      // go left
      cur = cur->left;
    } else if (key > cur->key) {
      // go right
      cur = cur->right;
    } else {
      // found!
      break;
    }
  }
  if (cur != t->nil) {
    fprintf(stderr, "Currently key duplication not supported!\n END PROGRAM");
    exit(EXIT_FAILURE);
  }
  // let's create NEW node
  node_t *new = (node_t *)malloc(sizeof(node_t));
  *new = (node_t){.color = RBTREE_RED,
                  .key = key,
                  .parent = prev,
                  .left = t->nil,
                  .right = t->nil};
  if (prev->key < key) {
    // set as right child
    prev->right = new;
  } else {
    // set as left child
    prev->left = new;
  }
}
#endif
