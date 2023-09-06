#pragma once
/**
 * Stack
 * @brief maxlength가 정해진 단순 스택
 */
#include <stdbool.h>

#include "rbtree.h"
#define MAX_STACK 20000

typedef struct node_stack {
  node_t *arrptr[MAX_STACK];
  int top;
} Stack;

bool stack_full(const Stack *stack);
bool stack_empty(const Stack *stack);
bool stack_push(Stack *stack, node_t *new);
node_t *stack_pop(Stack *stack);
