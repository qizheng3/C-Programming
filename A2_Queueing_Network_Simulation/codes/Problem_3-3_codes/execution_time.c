#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#define N 1000
#define M 10000000


typedef struct NODE node;
struct NODE{
	  node* next;
	  double value;
};

long long current_timestamp() {
    struct timeval te;
    gettimeofday(&te, NULL); // get current time
    long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000; // caculate milliseconds
    // printf("milliseconds: %lld\n", milliseconds);
    return milliseconds;
}

node* create_list(void){
	node *head = NULL;
	return head;
}

node* create_new_node(double timeStamp){
	node* new_node;
	new_node = (node*)malloc(sizeof(node));
	if (new_node == NULL){
		printf("Error: malloc failed. Not enough memory.");
		exit(EXIT_FAILURE);
	}
	new_node->next = NULL;
	new_node->value = timeStamp;
	return new_node;
}

node* insert_new(node *list, node* new_node){
	node* prev, *curr;
	for(curr = list, prev = NULL;
		curr != NULL && curr->value < new_node->value;
		prev = curr, curr = curr->next)
		;

	if (prev == NULL){
		new_node->next = curr;
		return new_node;
	}
	else{
		prev->next = new_node;
		new_node->next = curr;
		return list;
	}
}

void freeList(node* list){
	node *current;
	while(list!= NULL){
		current = list;
		list = list->next;
		free(current);
	}
}

int main(){
	srand(time(NULL));
	int i;
	double timeStamp;
	node *new_node, *list, *head;
	double t_start, t_end, delt_t;
	list = create_list();

	//generate a sorted list containing N nodes
	for(i=0; i<N; i++){
		timeStamp = (double)rand()/RAND_MAX;
		new_node = create_new_node(timeStamp);
		list = insert_new(list, new_node);
	}

	t_start = current_timestamp(); //convert to ms

	//insert a new and delete the first node for M times
	for (i=0; i<M; i++){
		timeStamp = (double)rand()/RAND_MAX;
		new_node = create_new_node(timeStamp);
		list = insert_new(list, new_node);
		head = list;
		list = list->next;
		free(head);
	}

	t_end = current_timestamp(); //convert to ms
	delt_t= t_end-t_start;
	freeList(list);

	printf("Running Log:\n");
	printf("----------------------------------------------\n");
	printf("Num of events in the prior queue (N) = %d\n", N);
	printf("Num of complete operation loops: %d\n", M);
	printf("Total execution time(ms):  %f\n", delt_t);
	printf("Average time for a single loop(ms):  %f\n", delt_t/M);


}
