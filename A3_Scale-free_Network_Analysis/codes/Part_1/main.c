#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct edge					//define edge structure
{
	int node_id;
	struct edge *next;
};

struct node 				//define node structure
{
	struct edge *first;
	struct edge *last;
	int degree;
};

char filename1[1024];
char filename2[1024];

struct node* baseNode(struct node* graph);

struct node* addNode(struct node* graph, int total_degree);

void insertNode(struct node* graph, int i, int j);

void outputGraph(struct node* graph, int n);

void outputHistogram(struct node* graph, int n);

void free_graph(struct node* graph, int n);

int main(int argc, char *argv[])
{
	int n = atoi(argv[1]);
    if(argc !=4)
        {
        fprintf(stderr,"Usage error\n");
        exit(EXIT_FAILURE);
        }

    strcpy(filename1, argv[2]);
    strcpy(filename2, argv[3]);

 	struct node *graph;	    								//graph node type pinter
	graph = (struct node *)malloc(n * sizeof(struct node));	//allocate memory space for n nodes
	if(graph == NULL)
	{
		printf("No enough memory\n");
		exit(0);
	}

	graph = baseNode(graph);

	int total_degree = 6;

	int i;
	for(i=3; i<=n-1; i++)
	{
		graph = addNode(graph, total_degree);
		total_degree += 2;
	}

	outputGraph(graph, n);

    outputHistogram(graph, n);

    free_graph(graph, n);

    free(graph);

	return 0;
}

struct node* baseNode(struct node* graph)
{
	//initiate node[0]
	graph[0].first = (struct edge*)malloc(sizeof(struct edge));
	graph[0].last = graph[0].first;
	graph[0].first->node_id =1;
	graph[0].first->next = NULL;

	struct edge* temp0;
	temp0 = (struct edge*)malloc(sizeof(struct edge));
    if(temp0 == NULL)
	{
		printf("No enough memory\n");
		exit(0);
	}
	temp0->node_id = 2;
	temp0->next = NULL;
	graph[0].first->next = temp0;
	graph[0].last=temp0;
	graph[0].degree = 2;

	//initiate node[1]
	graph[1].first = (struct edge*)malloc(sizeof(struct edge));
	graph[1].last = graph[1].first;
	graph[1].first->node_id =0;
	graph[1].first->next = NULL;

	struct edge* temp1;
	temp1 = (struct edge*)malloc(sizeof(struct edge));
	temp1->node_id = 2;
	temp1->next = NULL;
	graph[1].first->next = temp1;
	graph[1].last=temp1;
	graph[1].degree = 2;

	//initiate node[2]
	graph[2].first = (struct edge*)malloc(sizeof(struct edge));
	graph[2].last = graph[2].first;
	graph[2].first->node_id =0;
	graph[2].first->next = NULL;

	struct edge* temp2;
	temp2 = (struct edge*)malloc(sizeof(struct edge));
	temp2->node_id = 1;
	temp2->next = NULL;
	graph[2].first->next = temp2;
	graph[2].last=temp2;
	graph[2].degree = 2;

return graph;
}

struct node* addNode(struct node* graph, int total_degree)
{
	time_t t;
    srand((unsigned)time(&t));
    int T=rand()%total_degree + 1;

	int i, k;
	k = total_degree / 2;						//k is number of existing nodes

	for(i=0; i<=k-1; i++)
	{
		if(graph[i].degree >= T)                //adding node[k] in node[i], node[k] is a new node
		{
			insertNode(graph, i, k);
            return graph;
		}
		else
			T = T - graph[i].degree;
	}

	return graph;
}

void insertNode(struct node* graph, int i, int j)
{
	//add node[j] to node[i]'s linked list
	struct edge* p;
	p = (struct edge*)malloc(sizeof(struct edge));
	p->node_id = j;
	p->next = NULL;
	graph[i].last->next = p;
	graph[i].last = p;
	graph[i].degree ++;


	//add node[i] to node[j]'s linked list
	graph[j].first = (struct edge*)malloc(sizeof(struct edge));
	graph[j].first->node_id = i;
	graph[j].first->next = NULL;
	graph[j].last = graph[j].first;
	graph[j].degree = 1;

}

void outputGraph(struct node* graph, int n)
{
	FILE *output_file = fopen(filename1, "w");

	if(output_file == NULL)
	{
		fprintf(stderr,"Error in opening file\n");
		exit(EXIT_FAILURE);
	}
	
	fprintf(output_file, "%d\n", n);

	int i;
	for(i=0; i<=n-1; i++)
	{
		struct edge* pr = graph[i].first;

		fprintf(output_file, "%d\t%d ", graph[i].degree, i);
		while(pr != NULL)
		{
			fprintf(output_file, "%d ", pr->node_id);
			pr = pr->next;
		}
		fprintf(output_file,"\n");

	}

	fclose(output_file);

}

void outputHistogram(struct node* graph, int n)
{
    FILE *output_file = fopen(filename2, "w");

	if(output_file == NULL)
	{
		fprintf(stderr,"Error in opening file\n");
		exit(EXIT_FAILURE);
	}

    int i,j,m,k;
    for(j=1; j<n; j++)
    {
        fprintf(output_file, "%d,", j);
        m=0;
        for(i=0; i<n; i++)
        {
            if(graph[i].degree == j)
            {
                m++;
            }
        }

        fprintf(output_file, "% d,", m);

        for(k=0; k<n; k++)
        {
            if(graph[k].degree == j)
            {
                fprintf(output_file, " %d,", k);
            }
        }

        fprintf(output_file, "\n");
    }

    fclose(output_file);
}

void free_graph(struct node* graph, int n)
{
    int j;
    struct edge* temp;
    for(j=0; j<n; j++)
    {
        while(graph[j].first != NULL)
        {
            temp = graph[j].first;
            graph[j].first = graph[j].first -> next;
            free(temp);
        }
    }
}
