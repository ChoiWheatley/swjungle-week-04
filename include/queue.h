#pragma once
/**
 * Queue
 * @brief maxlength가 정해진 단순한 원형 큐
 */
#include <rbtree.h>
#include <stdbool.h>
#define MAX_QUEUE 1000

typedef struct node_q {
  node_t *arrptr[MAX_QUEUE];
  int head;
  int tail;
} Queue;

bool queue_full(const Queue *queue);
bool queue_empty(const Queue *queue);
void queue_push(Queue *queue, node_t *new);
node_t *queue_pop(Queue *queue);
