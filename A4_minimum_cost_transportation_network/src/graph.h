#ifndef GRAPH_H_
#define GRAPH_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct EDGE edge;
struct EDGE{
	int u;
	int v;
	int w;
	edge* next;
};


typedef struct LIST list;
struct LIST{
	int id;
	edge* head;
	edge* tail;
};


list* create_list(int u){
	list* new_list = (list*)malloc(sizeof(list));
	new_list->id = u;
	new_list->head = NULL;
	new_list->tail = NULL;
	return new_list;
}


void add_edge_to_list(list* lst, int u, int v, int weight){
	edge* nd = (edge*)malloc(sizeof(edge));
	nd->u = u;
	nd->v = v;
	nd->w = weight;
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
	edge* p;
	for (i=0; i<num; i++){
		while(graph[i]->head){
			p = graph[i]->head;
			graph[i]->head=graph[i]->head->next;
			free(p);
		}
		free(graph[i]);
	}
}


void print_graph(list *G[], int V){
	int i;
	edge* e;
	for (i=0; i<V; i++){
    e = G[i]->head;
    printf("%d\t", i);
    while(e){
      printf("(%d, %d, %d)\t", e->u, e->v, e->w);
      e=e->next;
    }
    printf("\n");
  }
}


#endif /* GRAPH_H_ */
