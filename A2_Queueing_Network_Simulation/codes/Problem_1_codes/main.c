#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "simulator.h"
double INTERVAL_E = 5.0;		//mean interarrival time (A)
double DURATION_E = 10.0;		//mean service time (S)
int PART_NUM = 5;

/*
 *
double urand() {
  return (double)rand() / RAND_MAX;
}

double randexp() {
  double d = -(log(1.0 - urand()));
  return d;
}
 */

int main() {
  srand(time(NULL));
  int i, count=0;
  simulator* a_sim = create_simulator();
  for (int i = 0; i < PART_NUM; ++i) {
    next_part(a_sim, INTERVAL_E,DURATION_E);
  }
  while(!is_emtpy_pq(a_sim->event_pq)) {
    process_event(a_sim);
  }

  printf("Constant Interarrival Time(A):\t%f\n", INTERVAL_E);
  printf("Constant Service Time(S):\t%f\n", DURATION_E);
  printf("Total Part Number is:\t\t%d\n\n", PART_NUM);


  while(!is_empty_queue(a_sim->state_queues[SINK])) {
    part* p = dequeue(a_sim->state_queues[SINK]);
    printf("Part #%d:    Process Start Time  -->  Finish Time\n",++count);
    printf("Source Time:    %f\n", p->schedule_time[SOURCE]);
    for (i=1; i<4; i++)
    	printf("Station #%d\t%f\t-->\t%f\n", i, p->schedule_time[i], p->finish_time[i]);
    printf("Sink Time:      %f\n", p->schedule_time[SINK]);
    printf("\n");
  }
  printf("End of Simulation.");
  delete_simulator(a_sim);
}

