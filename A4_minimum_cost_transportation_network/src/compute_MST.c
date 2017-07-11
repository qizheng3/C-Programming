#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "heappq.h"
#include "graph.h"


int main(int argc, char *argv[]){

	char file_input[500], file_output[500];
	FILE *fr;
	int V, E, num;
	int i, j, u, v, w, now, nw, total_len=0, des = 5;
	edge* curr;
	edge* e;


	if (argc!=2){
		printf("Usage error, please use legal format: source_code_file_name input_file_name\n");
        exit(EXIT_FAILURE);
    }
	
    strcpy(file_input, "..\\data\\");
    strcat(file_input, argv[1]);
    strcat(file_input, ".gr");
   
   	strcpy(file_output, "..\\data\\");
   	strcat(file_output, argv[1]);
   	strcat(file_output, "_MST.txt");



	if ((fr = fopen(file_input, "r")) == NULL){
		printf("Error: fail to open the file!\n");
		exit(1);
	}
	else{
		fscanf(fr, "%d", &V);	//read in the total number of vertices
		fscanf(fr, "%d", &E);	//read in the total number of edges
	}

	// construct the graph arraylist G
	// each element of G is a linked list of adjacent vertices
	list** G = (list**)malloc(V * sizeof(list));

	// initialize the graph arrayList:
	for (i=0; i<V; i++)
		G[i] = create_list(i);

	// read in the graph from the input file
    while(!feof(fr)){
    	fscanf(fr, "%d", &u);
    	fscanf(fr, "%d", &v);
    	fscanf(fr, "%d", &w);
    	add_edge_to_list(G[u], u, v, w);
    	add_edge_to_list(G[v], v, u, w);   
    }
    fclose(fr);

	
/********************************************************************/
/*		     Compute the minimum spanning tree (MST)				*/
/********************************************************************/

	// create an arraylist to store the selected edges for MST
	edge** MST = malloc((V-1)*sizeof(edge));
	// construct the heap prior queue: heapq
	edge** heapq = malloc(2*E*sizeof(edge));
	// construct an array to store the visited node numbers
	int *S = (int*)calloc(V, sizeof(int));

	// Compute MST and assemble the graph
	num = 0;
	now = 0;
	S[now] = 1;

	for (i=0; i<V-1; i++){		
		e = G[now]->head;
		while(e){
			v = e->v;
			if (!S[v])
				heap_insert(heapq, e, &num);
			e = e->next;
		}

		while (1){
			curr = heap_pop(heapq, &num);
			u = curr->u;
			v = curr->v;
			if (S[u] && !S[v]){
				S[v] = 1;
				now = v;
				MST[i] = curr;
				total_len+=curr->w;
				break;
			}
			else if (!S[u] && S[v]){
				S[u] = 1;
				now = u;
				MST[i] = curr;
				total_len+=curr->w;
				break;
			}
		}
	}

	list** MSTG = (list**)malloc((V-1) * sizeof(list));
	for (i=0; i<V; i++)
		MSTG[i] = create_list(i);

	for (i=0; i<V-1; i++){
		u = MST[i]->u;
		v = MST[i]->v;
		add_edge_to_list(MSTG[u], u, v, MST[i]->w);
		add_edge_to_list(MSTG[v], v, u, MST[i]->w);		
	}

	printf("\nMinimum cost: %d\n\n", total_len);
	
	print_graph(MSTG, V);
	printf("\n");

	FILE *fw = fopen(file_output, "w");
	if(fw == NULL){
		fprintf(stderr,"Error in opening file\n");
		exit(EXIT_FAILURE);
	}

	fprintf(fw, "%d\n", total_len);
	fprintf(fw, "%d %d\n", V, V-1);
	
	for(i=0; i<V-1; i++){
		fprintf(fw, "%d %d %d\n", MST[i]->u, MST[i]->v, MST[i]->w);
	}
	fclose(fw);


	free_graph(G, V);
	free_graph(MSTG, V);
 	free(MST);
 	free(heapq);
	free(S);

	return 0;
}