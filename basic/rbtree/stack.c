#include <stack.h>

bool stack_full(const Stack* stack) { return stack->top >= MAX_STACK; }

bool stack_empty(const Stack* stack) { return stack->top <= 0; }

bool stack_push(Stack* stack, node_t* new) {
  if (stack_full(stack)) {
    return false;
  }
  stack->arrptr[stack->top] = new;
  stack->top += 1;
  return true;
}

node_t* stack_pop(Stack* stack) {
  if (stack_empty(stack)) {
    return NULL;
  }
  stack->top -= 1;
  return stack->arrptr[stack->top];
}
