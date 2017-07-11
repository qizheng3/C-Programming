#ifndef GRAPH_H_
#define GRAPH_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct NODE node;
struct NODE{
	int id;
	node* next;
};

typedef struct LIST list;
struct LIST{
	int degree;
	node* head;
	node* tail;
};


/* graph construction */
list* create_list(){
	list* new_list = (list*)malloc(sizeof(list));
	new_list->head=NULL;
	new_list->tail=NULL;
	return new_list;
}

void add_node_to_list(list* lst, int val){
	node* nd = (node*)malloc(sizeof(node));
	nd->id = val;
	nd->next = NULL;
	if (lst->head == NULL){
		lst->head = lst->tail = nd;
	}
	else{
		lst->tail->next = nd;
		lst->tail = nd;
	}
}

void free_graph(list* graph[], int num){
	int i;
	node* p;
	for (i=0; i<num; i++){
		while(graph[i]->head){
			p = graph[i]->head;
			graph[i]->head=graph[i]->head->next;
			free(p);
		}
		free(graph[i]);
	}
}


/* addition operations regarding FIFO queue */
list* FIFO_pop(list* q, int* val_pop) {
	node* node = q->head;
	q->head = node->next;
	if (q->head == NULL) {
		q->tail = NULL;
	}
	*val_pop = node->id;
	free(node);
	return q;
}

int not_empty_q(list* q) {
  return (q->head != NULL);
}

#endif /* GRAPH_H_ */
