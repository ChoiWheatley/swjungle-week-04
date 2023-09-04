#ifndef _RBTREE_H_
#define _RBTREE_H_

#include <stddef.h>

typedef enum { RBTREE_RED, RBTREE_BLACK } color_t;

typedef int key_t;

typedef struct node_t {
  color_t color;
  key_t key;
  struct node_t *parent, *left, *right;
} node_t;

typedef struct {
  node_t *root;
  node_t *nil;  // for sentinel
} rbtree;

rbtree *new_rbtree(void);
void delete_rbtree(rbtree *);

node_t *rbtree_insert(rbtree *, const key_t);
node_t *rbtree_find(const rbtree *, const key_t);
node_t *rbtree_min(const rbtree *);
node_t *rbtree_max(const rbtree *);
int rbtree_erase(rbtree *, node_t *);

int rbtree_to_array(const rbtree *, key_t *, const size_t);

/**
 * Queue
 * @brief maxlength가 정해진 단순한 원형 큐
 */
#include <stdbool.h>
#define MAX_QUEUE 100

typedef struct node_q {
  node_t *arrptr[MAX_QUEUE];
  int head;
  int tail;
} Queue;

bool is_full(const Queue *queue);
bool is_empty(const Queue *queue);
void queue_push(Queue *queue, node_t *new);
node_t *queue_pop(Queue *queue);

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
#endif  // DEBUG

#endif  // _RBTREE_H_