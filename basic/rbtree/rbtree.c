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
  travel_dfs_mut(t, free_node);
  free(t->nil);
  free(t);
}

/// @brief RBTree 제약조건을 만족시키는 이진검색트리 삽입을 구현하세요.
/// @return 새로 생성된 노드의 주소
node_t *rbtree_insert(rbtree *t, const key_t key) {
  if (t->root == t->nil) {
    // empty tree
    t->root = (node_t *)malloc(sizeof(node_t));
    *t->root = (node_t){RBTREE_BLACK, key, t->nil, t->nil, t->nil};
    return t->root;
  }

  // 순회 돌면서 NIL까지 간다. 중복을 발견하면 오른쪽으로 이동.
  node_t *cur = t->root;
  node_t *prev = cur;

  while (cur != t->nil) {
    prev = cur;
    if (key < cur->key) {
      // go left
      cur = cur->left;
    } else {
      // go right
      cur = cur->right;
    }
  }

  // let's create NEW node
  node_t *new = (node_t *)malloc(sizeof(node_t));
  *new = (node_t){.color = RBTREE_RED,
                  .key = key,
                  .parent = prev,
                  .left = t->nil,
                  .right = t->nil};
  if (key < prev->key) {
    // set as left child
    prev->left = new;
  } else {
    prev->right = new;
  }

  // check if insertion violates imbalance
  if (prev->color == RBTREE_RED && new->color == RBTREE_RED) {
    rbtree_insert_fixup(t, new);
  }
  return new;
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

node_t *rbtree_min(const rbtree *t) { return subtree_min(t, t->root); }

node_t *rbtree_max(const rbtree *t) { return subtree_max(t, t->root); }

/// @brief fixup 조건은 transplant 당한 노드의 색상이 black인 경우이다. 삭제시
/// 노드의 자식이 둘일때 오른쪽 서브트리의 min을 찾아 transplant 한다.
/// @return ??? 모르겠다 그냥 key 리턴해야쥐
int rbtree_erase(rbtree *t, node_t *u) {
  color_t origin_color = u->color;
  node_t *x = u->left;

  if (u->left == t->nil) {
    x = u->right;
    __transplant(t, u, u->right);
  } else if (u->right == t->nil) {
    x = u->left;
    __transplant(t, u, u->left);
  } else {
    /**
     * # left, right children exists
     *
     * 1. find minimum node(y) from right subtree
     * 2. let x as y.right and transplant y, x even if x is NIL
     * 3. transplant p, y so that p is finally replaced
     */
    node_t *y = subtree_min(t, u->right);
    // Now we take care of y's subtree
    origin_color = y->color;

    x = y->right;

    __transplant(t, y, x);  // x might be NIL, that's ok
    // prepare y's recapture u's position
    y->right = u->right;
    y->right->parent = y;
    __transplant(t, u, y);
    y->left = u->left;
    y->left->parent = y;
    y->color = u->color;
  }

  if (origin_color == RBTREE_BLACK) {
    rbtree_delete_fixup(t, x);
  }

  key_t ret = u->key;
  free(u);
  return ret;
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
  return n;
}

void rbtree_insert_fixup(rbtree *t, node_t *u) {
  while (u != t->root && u->parent->color == RBTREE_RED) {
    node_t *pu = u->parent;
    node_t *gu = pu->parent;
    node_t *uncle = gu->right;
    if (pu == gu->right) {
      uncle = gu->left;
    }

    switch (rbtree_insert_case(t, u, pu, gu, uncle)) {
      /// ??r imbalance
      /// 단순히 색깔만 바꿔주면 된다. 뒷일은 부모가 알아서 책임질거임.
      case (InsertCase)LLr:
      case (InsertCase)LRr:
      case (InsertCase)RLr:
      case (InsertCase)RRr: {
        pu->color = RBTREE_BLACK;
        uncle->color = RBTREE_BLACK;
        gu->color = RBTREE_RED;
        u = gu;
        break;
      }
      /// ??b imbalance
      /// 회전이 들어간다.
      case (InsertCase)LRb: {
        __rotate_left(t, pu);
        node_t *tmp = u;
        u = pu;
        pu = tmp;
        // intentional fallthrough to LLb
      }
      case (InsertCase)LLb: {
        gu->color = RBTREE_RED;
        pu->color = RBTREE_BLACK;
        __rotate_right(t, gu);
        break;
      }
      case (InsertCase)RLb: {
        __rotate_right(t, pu);
        node_t *tmp = u;
        u = pu;
        pu = tmp;
        // intentional fallthrough to RRb
      }
      case (InsertCase)RRb: {
        gu->color = RBTREE_RED;
        pu->color = RBTREE_BLACK;
        __rotate_left(t, gu);
        break;
      }
    }
  }
  t->root->color = RBTREE_BLACK;
}

void rbtree_delete_fixup(rbtree *t, node_t *u) {
  node_t *x = u;
  while (x != t->root && x->color == RBTREE_BLACK) {
    node_t *p = x->parent;
    switch (rbtree_delete_case(t, x)) {
      case (DeleteCase)LType1: {
        node_t *w = p->right;
        w->color = p->color;
        p->color = RBTREE_RED;
        __rotate_left(t, p);
        continue;
      }
      case (DeleteCase)LType2: {
        node_t *w = p->right;
        w->color = RBTREE_RED;
        x = p;
        continue;
      }
      case (DeleteCase)LType3: {
        node_t *w = p->right;
        w->left->color = RBTREE_BLACK;
        w->color = RBTREE_RED;
        __rotate_right(t, w);
        // intentional fallthrough
      }
      case (DeleteCase)LType4: {
        node_t *w = p->right;
        w->right->color = RBTREE_BLACK;
        w->color = p->color;
        p->color = RBTREE_BLACK;
        __rotate_left(t, p);
        return;
      }
      case (DeleteCase)RType1: {
        node_t *w = p->left;
        w->color = p->color;
        p->color = RBTREE_RED;
        __rotate_right(t, p);
        continue;
      }
      case (DeleteCase)RType2: {
        node_t *w = p->left;
        w->color = RBTREE_RED;
        x = p;
        continue;
      }
      case (DeleteCase)RType3: {
        node_t *w = p->left;
        w->right->color = RBTREE_BLACK;
        w->color = RBTREE_RED;
        __rotate_left(t, w);
        // intentional fallthrough
      }
      case (DeleteCase)RType4: {
        node_t *w = p->left;
        w->left->color = RBTREE_BLACK;
        w->color = p->color;
        p->color = RBTREE_BLACK;
        __rotate_right(t, p);
        return;
      }
    }
  }
  x->color = RBTREE_BLACK;
}

InsertCase rbtree_insert_case(rbtree *t, node_t *u, node_t *parent,
                              node_t *grandparent, node_t *uncle) {
  if (parent == grandparent->left) {
    // L??
    if (u == parent->left) {
      // LL?
      if (uncle->color == RBTREE_RED) {
        return (InsertCase)LLr;
      }
      return (InsertCase)LLb;
    }
    // LR?
    if (uncle->color == RBTREE_RED) {
      return (InsertCase)LRr;
    }
    return (InsertCase)LRb;
  }
  // R??
  if (u == parent->left) {
    // RL?
    if (uncle->color == RBTREE_RED) {
      return (InsertCase)RLr;
    }
    return (InsertCase)RLb;
  }
  // RR?
  if (uncle->color == RBTREE_RED) {
    return (InsertCase)RRr;
  }
  return (InsertCase)RRb;
}

DeleteCase rbtree_delete_case(rbtree *t, node_t *u) {
  node_t *p = u->parent;
  node_t *w = p->left;
  if (u == p->left) {
    // LType?
    w = p->right;
    if (w->color == RBTREE_RED) {
      return (DeleteCase)LType1;
    }
    if (w->right->color == RBTREE_RED) {
      return (DeleteCase)LType4;
    }
    if (w->left->color == RBTREE_RED) {
      return (DeleteCase)LType3;
    }
    return (DeleteCase)LType2;
  }
  // RType? Type3, Type4가 LType과 반대라는 점 주의
  if (w->color == RBTREE_RED) {
    return (DeleteCase)RType1;
  }
  if (w->left->color == RBTREE_RED) {
    return (DeleteCase)RType4;
  }
  if (w->right->color == RBTREE_RED) {
    return (DeleteCase)RType3;
  }
  return (DeleteCase)RType2;
}

/// @brief 노드 u를 기준으로 왼쪽 회전을 수행
void __rotate_left(rbtree *t, node_t *u) {
  if (!t || !u || u == t->nil) {
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

/// @brief u 노드를 기존의 연결에서 제외하고 그 자리에 v를 넣는다.
void __transplant(rbtree *t, node_t *u, node_t *v) {
  node_t *parent = u->parent;
  if (parent == t->nil) {
    // u was root node
    t->root = v;
  } else if (u == parent->left) {
    parent->left = v;
  } else {
    parent->right = v;
  }
  v->parent = parent;
}

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
      node_t *tmp = stack_pop(&stack);
      cur = tmp->right;
      callback(t, tmp);
    }
  }
}

node_t *subtree_min(const rbtree *t, node_t *u) {
  node_t *cur = u;
  node_t *prev = cur;

  while (cur != t->nil) {
    prev = cur;
    cur = cur->left;
  }

  return prev;
}

node_t *subtree_max(const rbtree *t, node_t *u) {
  node_t *cur = t->root;
  node_t *prev = cur;

  while (cur != t->nil) {
    prev = cur;
    cur = cur->right;
  }

  return prev;
}

void free_node(const rbtree *t, node_t *node) { free(node); }

int key_comp(const void *lhs, const void *rhs) {
  key_t l = *(key_t *)lhs;
  key_t r = *(key_t *)rhs;
  return l - r;
}

#define COLOR_TO_CHAR(color) (color) ? 'b' : 'r'

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
    snprintf(sleft, MAX_STR, "%d(%c)", node->left->key,
             COLOR_TO_CHAR(node->left->color));
  }
  if (node->right != t->nil) {
    snprintf(sright, MAX_STR, "%d(%c)", node->right->key,
             COLOR_TO_CHAR(node->right->color));
  }
  if (node->parent != t->nil) {
    snprintf(sparent, MAX_STR, "%d(%c)", node->parent->key,
             COLOR_TO_CHAR(node->parent->color));
  }
  printf("key: %s(%c): (left: %s, right: %s, parent: %s)\n", skey,
         COLOR_TO_CHAR(node->color), sleft, sright, sparent);

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
