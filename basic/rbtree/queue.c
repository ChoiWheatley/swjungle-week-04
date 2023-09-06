#include <queue.h>

bool queue_full(const Queue *queue) {
  return ((queue->tail + 1) % MAX_QUEUE) == queue->head;
}

bool queue_empty(const Queue *queue) { return queue->tail == queue->head; }

void queue_push(Queue *queue, node_t *new) {
  if (queue_full(queue)) {
    // full, discard head's element
    queue->head = (queue->head + 1) % MAX_QUEUE;
  }
  queue->tail = (queue->tail + 1) % MAX_QUEUE;
  queue->arrptr[queue->tail] = new;
}

node_t *queue_pop(Queue *queue) {
  if (queue->head == queue->tail) {
    // no element
    return NULL;
  }
  queue->head = (queue->head + 1) % MAX_QUEUE;
  return queue->arrptr[queue->head];
}
