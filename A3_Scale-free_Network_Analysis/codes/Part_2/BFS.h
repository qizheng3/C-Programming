#include "graph.h"

typedef enum {EMPTY= 0, VISIT, LEAVE}state;

void BFS(list* graph[], int n, 	int k, int **dis, int indivMax[], int* maxdis){
	int i, pop;
	state C[n];
	int D[n];
	node* nd;

	list* fifoq = create_list();
	for(i=0; i<n; i++){
		C[i] = EMPTY;
		D[i] = 0;
	}

	indivMax[k]=0;
	C[k] = VISIT;
	add_node_to_list(fifoq, k);

	while(not_empty_q(fifoq)){
		FIFO_pop(fifoq, &pop);
		for (nd = graph[pop]->head->next; nd; nd=nd->next){
			if(C[nd->id] == EMPTY){
				D[nd->id] = D[pop]+1;
				C[nd->id] = VISIT;
				add_node_to_list(fifoq, nd->id);
			}
		}
		C[pop]=LEAVE;
	}
	
	for(i=0; i<n; i++){
		dis[k][i]=D[i];
		indivMax[k] = D[i] > indivMax[k]? D[i]:indivMax[k];
		if (*maxdis<D[i])
			*maxdis=D[i];
	}
	free(fifoq);
}