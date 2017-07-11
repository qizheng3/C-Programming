/*
 * This is a program computing the average forest size P as a function of the growth parameter (probability) g
 *
 *
 *  Created on: Sep 8, 2016
 *      Author: Qi Zheng
 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 100
#define EMPTY 0
#define TREE 1
#define BURN 2

int Forest[N][N]={0};
float F;
float G;


void init(void){
	int i, j;
	for(i = 0; i < N; i++){
	  for(j = 0; j < N; j++){
		  Forest[i][j]=EMPTY;   //Initialize the forest with all cells empty
	  }
	}
}


float gener_rand()  //Generate a random float number between 0 and 1
{
	return (float)rand()/RAND_MAX;
}


void growth_phase(float G)  //Growth phase: new growth occurs in empty cells
{
  int i, j;
  for(i = 0; i < N; i++){
    for(j = 0; j < N; j++){
      if (Forest[i][j] == EMPTY){
    	  if (gener_rand()<G){           //Trees grow in empty cells with probability g
    		  Forest[i][j] = TREE;
    	  }
      }
    }
  }
}



void fire_start(void)   //Fire arises at the end of each growth phase
{
	int i, j;
	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			if (Forest[i][j] == TREE){
				if(gener_rand()<F){
					Forest[i][j] = BURN;   //Fire arises at a cell containing a tree with probability f
				}
			}
		}
	 }
}



/* Fire spreads out from burning trees */
void fire_spread(int i, int j){
	if ((i>0) && (Forest[i-1][j]==TREE)){
		Forest[i-1][j] = EMPTY;
		fire_spread(i-1, j);
	}
	if ((i<(N-1)) && (Forest[i+1][j]==TREE)){
		Forest[i+1][j] = EMPTY;
		fire_spread(i+1, j);
	}
	if ((j>0) && (Forest[i][j-1]==TREE)){
		Forest[i][j-1] = EMPTY;
		fire_spread(i, j-1);
	}
	if ((j<(N-1)) && (Forest[i][j+1]==TREE)){
		Forest[i][j+1] = EMPTY;
		fire_spread(i, j+1);
	}
}






/* Combine fire_start and fire_spread into fire phase function */
void fire_phase(void){
	int i, j;
	fire_start();
	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			if (Forest[i][j] == BURN){
				Forest[i][j] = EMPTY;
				fire_spread(i, j);
			}
		}
	}
}


/* Print out the forest matrix */
int tree_num(void)
{
	int i, j, ntree=0;
	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			if(Forest[i][j] == TREE)
				ntree++;
		}
	}
	return ntree;
}


/* main function */
int main(void){
	int i;
	int sum;
	F=0.01;
	srand(time(NULL));
	printf(" g\tAve P\n");
	printf("-------------------\n");
	for (G=0.0; G<=1.00; G+=0.02){
		/* When G ranges from 0 to 1, print out the corresponding average forest size
		   after 600 time steps */
		init();
		sum = 0;
		for (i=1; i<=600; i++){
			growth_phase(G);
			fire_phase();
			sum+=tree_num();
		}
		printf(" %.2f\t%.2f\n", G, (float)sum/(i-1));
	}

	return 0;
}
