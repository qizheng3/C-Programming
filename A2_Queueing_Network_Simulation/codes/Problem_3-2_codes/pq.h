#ifndef _PQ_H
#define _PQ_H
#include <stdlib.h>

typedef int (*COMPARE_FUN)(ITEM_TYPE, ITEM_TYPE);   //part

typedef struct pq_node_type pq_node;
struct pq_node_type {
  ITEM_TYPE value;
  pq_node* next;
};

typedef struct pq_type {
  int num;
  pq_node* head;
  int (*compare)(ITEM_TYPE, ITEM_TYPE);
} pq;

pq* create_pq(COMPARE_FUN compare) {
  pq* a_pq = (pq*)malloc(sizeof(pq));
  a_pq->num = 0;
  a_pq->head = (pq_node*)malloc(sizeof(pq_node));
  a_pq->head->next = NULL;
  a_pq->compare = compare;
  return a_pq;
}

pq* add_item(pq* a_pq, ITEM_TYPE item) {
  ++a_pq->num;
  pq_node* pre = a_pq->head;
  while(pre->next != NULL && a_pq->compare(pre->next->value, item) < 0) {
    pre = pre->next;
  }
  pq_node* new_node = (pq_node*)malloc(sizeof(pq_node));
  new_node->value =  item;
  new_node->next = pre->next;
  pre->next = new_node;
  return a_pq;
}

ITEM_TYPE pop_item(pq* a_pq) {
  a_pq->num--;
  pq_node* n = a_pq->head->next;
  a_pq->head->next = n->next;
  ITEM_TYPE item = n->value;
  free(n);
  return item;
}

int is_empty_pq(pq* a_pq) {
  return a_pq->num == 0;
}

//can only delete empty pq;
void delete_pq(pq* a_pq) {
  free(a_pq->head);
  free(a_pq);
}
#endif
