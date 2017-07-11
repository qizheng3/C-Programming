#ifndef HEAPPQ_H_
#define HEAPPQ_H_

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"


void swap(edge* heap[], int a, int b){
	edge* k;
	k = heap[a];
	heap[a] = heap[b];
	heap[b] = k;
}

void heapify_down(edge* heap[], int i, int size){
	if (2*i >= size)
		return;
	else if (2*i+1 >= size){
		if (heap[2*i+1]->w>heap[i]->w)
			swap(heap, i, 2*i+1);
		return;
	}

	else if (heap[i]->w<heap[2*i+1]->w && heap[i]->w<heap[2*i+2]->w)
		return;

	else if (heap[2*i+1]->w<=heap[2*i+2]->w){
		swap(heap, i, 2*i+1);
		heapify_down(heap, (2*i+1), size);
	}
	else{
		swap(heap, i, 2*i+2);
        heapify_down(heap, (2*i+2), size);
    }
}

edge* heap_pop(edge* heap[], int *size){
	edge* pop = heap[0];
	heap[0] = heap[*size - 1];
    *size = *size - 1;
    heapify_down(heap, 0, *size);
    return pop;
}

void heapify_up(edge* heap[], int i){
	if (i==0)
		return;
	if (heap[i]->w<=heap[(i-1)/2]->w){
		swap(heap, i, (i-1)/2);
        heapify_up(heap, (i-1)/2);
    }
}

void heap_insert(edge* heap[], edge* new_edge, int *size){
	heap[*size] = new_edge;
	heapify_up(heap, *size);
	*size = *size + 1;
}


#endif /* HEAPPQ_H_ */