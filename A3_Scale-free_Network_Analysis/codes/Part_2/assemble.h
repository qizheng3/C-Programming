#ifndef ASSEMBLE_H_
#define ASSEMBLE_H_
#include "graph.h"

void read_in(list *graph[], char file_name[], int* n){
	FILE *fp;
	int i, deg=0, k=0, val;

	if ((fp = fopen(file_name, "r")) == NULL){
		printf("Cannot open the file.\n");
		exit(1);
	}
	else{
		fscanf(fp, "%d", n);
	}
    while(!feof(fp)){
    	fscanf(fp, "%d", &deg);
    	graph[k] = create_list();
    	for(i=0; i<= deg; i++){
    		fscanf(fp, "%d", &val);
    		add_node_to_list(graph[k], val);
    	}
    	graph[k]->degree = deg;
    	k++;
    }

  fclose(fp);
}


#endif /* ASSEMBLE_H_ */
