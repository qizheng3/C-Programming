#include "graph.h"
#include "assemble.h"
#include <string.h>
#include "BFS.h"
#define NUM 100000


int main(int argc, char *argv[]){
	char file_input[500], file_output[500];
	int n, i, j, k, maxdis=0;
	node* p;
	list* graph[NUM];

	if ((argc!=4)&&(argc!=2)){
		printf("Usage error, legal format: input_file_name -o output_file_name(optional)\n");
        exit(EXIT_FAILURE);
    }

    strcpy(file_input, argv[1]);
    strcat(file_input, ".txt");


	// read the graph into an adjacency list
	read_in(graph, file_input, &n);

	int **dis = malloc(n * sizeof(int *));
	for(i = 0; i < n; i++)
	    dis[i] = malloc(n * sizeof(int));

	int *indivMax = malloc(n * sizeof(int *));


	// perform BFS and generate the upper triangular distance matrix
	for(k=0; k<n; k++)
		BFS(graph, n, k, dis, indivMax, &maxdis);	


	// check the command line and print out the resu
	if(argc==4){
		strcpy(file_output, argv[3]);
		strcat(file_output, ".txt");

		FILE *fw = fopen(file_output, "w");
		if(fw == NULL){
			fprintf(stderr,"Error in opening file\n");
			exit(EXIT_FAILURE);
		}

		fprintf(fw, "Network Diameter: %d\n", maxdis);
		for(i=0; i<n; i++){
			fprintf(fw, "%d\t%d\t( ", i, indivMax[i]);
			for (j=0; j<n; j++)
				if (dis[i][j]==indivMax[i])
					fprintf(fw, "%d ", j);
			fprintf(fw, ")\n");
		}
		fprintf(fw, "\n");
		fclose(fw);
	}


	else{
		printf("Network Diameter: %d\n", maxdis);
		for(i=0; i<n; i++){
			printf("%d\t%d\t( ", i, indivMax[i]);
			for (j=0; j<n; j++)
				if (dis[i][j]==indivMax[i])
					printf("%d ", j);
			printf(")\n");
		}
	printf("\n");
	}


	/********************** COMMENTED OUT ***************************
	 * Optional operation:											*
	 *	 Print out the assembled adjacency linked list read from	*
	 *	 the file;												*
	 *	 Print out the symmetric distance matrix.					*
	 ****************************************************************/
	/* 
	// print out the assembled adjacency linked list
	for(i=0; i<n; i++){
		for(p=graph[i]->head; p; p=p->next){
			rintf("%d ", p->id);
		}
		rintf("\n");
	}
	rintf("\n");

	// print out the distance matrix
	for(i=0; i<n; i++){
		for(j=0; j<n; j++)
			rintf("%d ", dis[i][j]);
		rintf("\n");
	}
	rintf("\n");

	****************************************************************/


	free_graph(graph, n);

	for (i=0; i<n; i++)
		free(dis[i]);
	free(dis);

	free(indivMax);
	
	return 0;
}