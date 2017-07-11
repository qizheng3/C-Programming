#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

// find the max edge along the path from u to v
// depth first search
edge* findMaxEdge(int s, int t, list *MSTG[], int visited[]){
  edge* p;
  edge* sub_max;
  int pv;
  visited[s]=1;
  p=MSTG[s]->head;
  while(p!=NULL){
    pv=p->v;
    if (pv==t)
      return p;
    if (visited[pv]){
      p=p->next;
      continue;
    }
    sub_max = findMaxEdge(pv, t, MSTG, visited);
    if (sub_max){
      if (sub_max->w > p->w)
        return sub_max;
      else
        return p;
    }
    p=p->next;
  }
}


// used to delte an edge from the graph (G[i](u, v) and G[i](v, u))
void delEdge(int u, int v, list *G[]){
    edge* curr = G[u]->head;
    edge* prev;

    if (curr != NULL && curr->v == v)
    {
        G[u]->head = curr->next;   // Changed head
        free(curr);               // free old head
        return;
    }

    // Search for the key to be deleted, keep track of the
    // previous node as we need to change 'prev->next'
    while (curr != NULL && curr->v != v)
    {
        prev = curr;
        curr = curr->next;
    }
 
    // If key was not present in linked list
    if (curr == NULL) return;
 
    // Unlink the node from linked list
    prev->next = curr->next;
 
    free(curr);  // Free memory
}




int recomputeMST(int u, int v, int nw, int V, int mincost, list *G[]){
  edge* max_edge;
  edge* curr, prev;
  int i, j, w;
  int* visited = (int*)calloc(V, sizeof(int));
  max_edge = findMaxEdge(u, v, G, visited);
  i = max_edge->u;
  j = max_edge->v;
  w = max_edge->w;

  //printf("\nrlt: %d %d %d\n\n", max_edge->u, max_edge->v, max_edge->w);
  
  free(visited);

  if (w > nw){
    delEdge(i, j, G);
    delEdge(j, i, G);
    add_edge_to_list(G[u], u, v, nw);
    add_edge_to_list(G[v], v, u, nw);
    mincost = mincost + nw - w;
    printf("\nAn edge has been replaced: (%d, %d, %d) --> (%d, %d, %d), MST changed.Check out the output file.\n\n", i, j, w, u, v, nw);
  }
  else
    printf("No edge has been replaced, MST unchanged.\n");

  return mincost;
}




int main(int argc, char *argv[]){
  char file_input[500], file_output[500];
  FILE *fr;
  FILE *fr_new;
  int V, E, num;
  int i, j, u, v, w, now, total_len=0, des = 5, mincost;
  edge* curr;
  edge* e;
  
  if (argc!=2){
    printf("Usage error, please use legal format: source_code_file_name input_file_name\n");
        exit(EXIT_FAILURE);
    }

    strcpy(file_input, "..\\data\\");
    strcat(file_input, argv[1]);
    strcat(file_input, ".txt");
   
    strcpy(file_output, "..\\data\\");
    strcat(file_output, argv[1]);
    strcat(file_output, "_new_edge.txt");


  if ((fr = fopen(file_input, "r")) == NULL){
    printf("Error: fail to open the file!\n");
    exit(1);
  }

  else{
    fscanf(fr, "%d", &mincost);
    fscanf(fr, "%d", &V); //read in the total number of vertices
    fscanf(fr, "%d", &E); //read in the total number of edges
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

  // print_graph(G, V);

  if ((fr_new = fopen("..\\data\\new_edge.txt", "r")) == NULL){
    printf("Error: fail to open the file!\n");
    exit(1);
  }
  else{
    fscanf(fr_new, "%d", &u);
    fscanf(fr_new, "%d", &v); //read in the total number of vertices
    fscanf(fr_new, "%d", &w); //read in the total number of edges
  }
  fclose(fr);

  mincost = recomputeMST(u, v, w, V, mincost, G);
  
  FILE *fw = fopen(file_output, "w");
  if(fw == NULL){
    fprintf(stderr,"Error in opening file\n");
    exit(EXIT_FAILURE);
  }
  fprintf(fw, "Min Cost: %d\n", mincost);

  for (i=0; i<V; i++){
    e = G[i]->head;
    fprintf(fw, "%d\t", i);
    while(e){
      fprintf(fw, "(%d, %d, %d)\t", e->u, e->v, e->w);
      e=e->next;
    }
    fprintf(fw,"\n");
  }

  fclose(fw);

  free_graph(G, V); 

}

