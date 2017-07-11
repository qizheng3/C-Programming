#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "part.h"
#include "event.h"
#define ITEM_TYPE event*
#define NODE_VALUE_TYPE part*
#include "pq.h"
#include "queue.h"

typedef struct simulator_type {
  // parts queued in every state
  queue* state_queues[STATE_NUM];
  // every state's finish time
  double finish_times[STATE_NUM];
  // event priority queue
  pq* event_pq;
  // current simulator time
  double time;
} simulator;

double max(double a, double b) {
  return a > b? a: b;
}

simulator* create_simulator() {
  simulator* a_sim = (simulator*)malloc(sizeof(simulator));
  for (int i = 0; i < STATE_NUM; ++i) {
    a_sim->state_queues[i] = create_queue();
    a_sim->finish_times[i] = 0;
  }
  a_sim->event_pq = create_pq(event_compare);
  a_sim->time = 0;
  return a_sim;
}

void delete_simulator(simulator* a_sim) {
  while(!is_empty_queue(a_sim->state_queues[SINK])) {
    part* p = dequeue(a_sim->state_queues[SINK]);
    free(p);
  }
  for(int i = 0; i < STATE_NUM; ++i) {
    delete_queue(a_sim->state_queues[i]);
  }
  delete_pq(a_sim->event_pq);
  free(a_sim);
  a_sim = NULL;
}

// create the next part from source
part* next_part(simulator* a_sim, double interval, double duration) {
  part* p = (part*)malloc(sizeof(part));
  // initially the part is in source
  p->s = SOURCE;
  // it will arrive after all previous parts + interval
  p->schedule_time[SOURCE] = max(a_sim->time, a_sim->finish_times[SOURCE])
      + interval;
  // these is no processing time in SOURCE
  p->finish_time[SOURCE] = p->schedule_time[SOURCE];
  a_sim->finish_times[SOURCE] = p->schedule_time[SOURCE];
  p->process_duration = duration;
  // this event represents current part's arrive
  event* e = create_event(p->schedule_time[SOURCE], p);
  add_item(a_sim->event_pq, e);
  enqueue(a_sim->state_queues[SOURCE], p);
  return p;
}

state process_event(simulator* a_sim) {
  // process the earliest finish event
  event* e = pop_item(a_sim->event_pq);
  part* p = e->p;
  // move the simulator time to the event finish time
  a_sim->time = e->endtime;
  free(e);
  e = NULL;
  part* de_p = dequeue(a_sim->state_queues[p->s]);
  // the earliest finish event should always be the first one
  // of its state queue in simulator, otherwise the first one
  // in its state queue will finish this state earlier.
  assert(p == de_p);
  // part go to next state
  p->s =(state)(p->s + 1);
  if (p->s == SINK) {
    // if next state is SINK, this part finished.
    p->schedule_time[SINK] = a_sim->time;
    p->finish_time[SINK] = a_sim->time;
    enqueue(a_sim->state_queues[p->s], p);
    return SINK;
  }

  // the part's schedule time for the next state.
  // The reason we use max(simulator->time, and simulator->finish_times[state])
  // is:
  // 1. if there is no parts in next state, we should use the simualtor time,
  // since the last finish part may be finished long time ago
  // 2. if there are some parts in next state, we should use the finish time of
  // the state, since we need to wait all previous parts finish in this state.
  p->schedule_time[p->s] = max(a_sim->time, a_sim->finish_times[p->s]);
  p->finish_time[p->s] = p->schedule_time[p->s] + p->process_duration;
  a_sim->finish_times[p->s] = p->finish_time[p->s];
  // Create event for this part to finish in this state.
  e = create_event(p->finish_time[p->s], p);
  add_item(a_sim->event_pq, e);
  enqueue(a_sim->state_queues[p->s], p);
  return p->s;
}
