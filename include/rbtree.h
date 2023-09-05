#ifndef _RBTREE_H_
#define _RBTREE_H_

#include <stddef.h>
typedef enum { RBTREE_RED, RBTREE_BLACK } color_t;
/**
 * # Insert Imbalance Cases
 *
 * XYz의 의미: X, Y는 각각 grandparent입장에서 parent의 위치, parent 입장에서
 * node의 위치를 나타낸다. z는 `b` 또는 `r`인데, 각각 uncle이 black node인지,
 * red node인지를 나타낸다.
 */
typedef enum InsertCase { LLr, LRr, RLr, RRr, LLb, LRb, RLb, RRb } InsertCase;

/**
 * # Delete Imbalance Cases
 *
 * 1. RType1: x's right sibling w is red
 *   → w의 색을 black으로 바꿔주기 위해 x.p에
 * left_rotate를 수행.
 *   → fallthrough to case 2, 3, 4
 *
 * 2. RType2: x's right sibling w is black, both of w's children are black
 *   → 잃어버린 black 하나를 x.p가 상환하도록 강제로 w를 red로 만들자.
 *   → continue to next iteration
 *
 * 3. RType3: x's right sibling w is black, left child of w is red, right child
 * of w is black
 *   → case 4로 만들기 위해 w를 기준으로 Right Rotation을 수행.
 *
 * 4. RType4: x's right sibling w is black, right child of w is red
 *   → red node를 적극적으로 활용해 추가 black을 확보한다.
 *
 * 5. LType1: x's left sibling w is red
 * 6. LType2: x's left sibling w is black, both of w's children are black
 * 7. LType3: x's left sibling w is black, left child of w is red, right child
 * of w is black
 * 8. LType4: x's left sibling w is black, right child of w is red
 */
typedef enum DeleteCase {
  RType1,
  RType2,
  RType3,
  RType4,
  LType1,
  LType2,
  LType3,
  LType4
} DeleteCase;

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
 * helper functions
 */

void rbtree_insert_fixup(rbtree *t, node_t *u);
void rbtree_delete_fixup(rbtree *t, node_t *u);
InsertCase rbtree_insert_case(rbtree *t, node_t *u, node_t *parent,
                              node_t *grandparent, node_t *uncle);
void __rotate_left(rbtree *, node_t *u);
void __rotate_right(rbtree *, node_t *u);
void __transplant(rbtree *, node_t *u, node_t *v);
void travel_bfs(const rbtree *,
                void (*callback)(const rbtree *t, const node_t *));
void travel_dfs(const rbtree *,
                void (*callback)(const rbtree *t, const node_t *));
void travel_bfs_mut(rbtree *, void (*callback)(const rbtree *t, node_t *));
void travel_dfs_mut(rbtree *, void (*callback)(const rbtree *t, node_t *));
node_t *subtree_min(const rbtree *, node_t *u);
node_t *subtree_max(const rbtree *, node_t *u);
void free_node(const rbtree *t, node_t *node);
int key_comp(const void *lhs, const void *rhs);
#ifdef DEBUG
void print_node_verbose(const rbtree *t, const node_t *node);
void print_node(const rbtree *t, const node_t *node);
void bst_insert(rbtree *t, const key_t key);
#endif  // DEBUG

#endif  // _RBTREE_H_