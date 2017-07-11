/*
 * This is a program that computes an prints out the number of remaining trees
 * at the end of each "growth-fire" cycle
 * when f = 0.01, and g = 0.1
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

int Forest[N][N]={0};  //Forest matrix
float F = 0.01;    // Ignition factor f
float G = 0.1;    // Growth parameter g


int tree_num(void)   //Calculate the number of trees
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



float gener_rand()  //Generate a random float number between 0 and 1
{
	return (float)rand()/RAND_MAX;
}



void growth_phase()  //Growth phase: new growth occurs in empty cells
{
  int i, j;
  for(i = 0; i < N; i++){
    for(j = 0; j < N; j++){
      if (Forest[i][j] == EMPTY){
    	  if (gener_rand()<G){           //New growth occurs in empty cells with probability g
    		  Forest[i][j] = TREE;
    	  }
      }
    }
  }
}



void fire_start(void)  //Fire arises at the end of each growth phase
{
	int i, j;
	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			if (Forest[i][j] == TREE){
				if(gener_rand()<F){
					Forest[i][j] = BURN; //Fire arises at a cell containing a tree with probability f
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



/* Combine fire_start and fire_spread into a fire phase function */
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


/*Main function*/
int main(void){
	int i, num;
	int sum=0;
	srand(time(NULL));
	printf("Step#\tTransient forest size\t Ave forest size\n");
	for (i=1; i<=1000; i++){
		growth_phase();
		fire_phase();
		num=tree_num();
		sum+=num;
		printf("%d\t\t%d\t\t%.0f\n", i, num, (float)sum/(i));   // Print out the Step#, transient forest size and
	}
	printf("\nThe average forest size over the complete simulated period is: %.0f\n", (float)sum/(i-1));
	return 0;
}
