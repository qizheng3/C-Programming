#ifndef _EVENT
#define _EVENT
#include <stdlib.h>
#include "part.h"
// event represents a part finish one state.
typedef struct event_type {
  // endtime is the event finish time.
  double endtime;
  part *p;
} event;

int event_compare(event* event1, event* event2) {
  double a = event1->endtime - event2->endtime;
  if (a > 0) {
    return 1;
  }
  if (a < 0) {
    return -1;
  }
  return 0;
}

event* create_event(double endtime, part* p) {
  event* e = (event*)malloc(sizeof(event));
  e->endtime = endtime;
  e->p = p;
  return e;
}
#endif
