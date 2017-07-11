#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "simulator.h"
double INTERVAL_E = 1;		//mean interarrival time (A)
double DURATION_E = 10.0;		//mean service time (S)
int PART_NUM = 500;

double urand() {
  return (double)rand() / RAND_MAX;
}

double randexp() {
  double d = -(log(1.0 - urand()));
  return d;
}


int main() {
  srand(time(NULL));
  int i;
  double in_sys_time, delay, sum_sys=0, sum_delay=0;
  double INTERVAL_E = 0.2;
  printf("1/A	Mean Sys Time	Mean Queuing Delay\n");
  for (i=1; i<10; i++){
	  sum_sys=0;
	  sum_delay=0;
	  INTERVAL_E *=2;
	  simulator* a_sim = create_simulator();
	  for (int i = 0; i < PART_NUM; ++i) {
		  next_part(a_sim, INTERVAL_E * randexp(),DURATION_E * randexp());
	  }
	  while(!is_empty_pq(a_sim->event_pq)) {
		  process_event(a_sim);
	  }
	  while(!is_empty_queue(a_sim->state_queues[SINK])) {
		  part* p = dequeue(a_sim->state_queues[SINK]);
		  in_sys_time = p->schedule_time[SINK] - p->schedule_time[SOURCE];
		  delay = in_sys_time - p->process_duration;
		  sum_sys += in_sys_time;
		  sum_delay += delay;
	  }
	  printf("%.2f\t", (double)1/INTERVAL_E);
	  printf("%f\t", (double)sum_sys/PART_NUM);
	  printf("%f\n", (double)sum_delay/PART_NUM);
	  delete_simulator(a_sim);
  }
}
