#ifndef _QUEUE
#define _QUEUE
#include <stdlib.h>

typedef struct node_type node;
struct node_type{
  node* next;
  node* prev;
  NODE_VALUE_TYPE value;
};

typedef struct queue_type {
  node* head;
  node* tail;
  int num;
} queue;

queue* create_queue() {
  queue* q = (queue*)malloc(sizeof(queue));
  // head is a dummy node;
  node* head = (node*)malloc(sizeof(node));
  head->prev = (node*)NULL;
  head->next = (node*)NULL;
  q->head = head;
  q->tail = head;
  q->num = 0;
  return q;
}

void enqueue(queue* q, NODE_VALUE_TYPE v) {
  node* n = (node*)malloc(sizeof(node));
  n->value = v;
  q->tail->next = n;
  n->prev = q->tail;
  n->next = NULL;
  q->tail = n;
  q->num++;
}

NODE_VALUE_TYPE dequeue(queue* q) {
  node* n = q->head->next;
  q->head->next = n->next;
  if (n == q->tail) {
    q->tail = q->head;
  } else {
    n->next->prev = q->head;
  }
  NODE_VALUE_TYPE v = n->value;
  q->num--;
  free(n);
  return v;
}

int is_empty_queue(queue* q) {
  return q->num == 0;
}

// can only delete empty queue
void delete_queue(queue* q) {
  free(q->head);
  free(q);
}
#endif
