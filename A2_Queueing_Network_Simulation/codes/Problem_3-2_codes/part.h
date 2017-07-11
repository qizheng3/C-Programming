#ifndef _PART
#define _PART
#define STATE_NUM 3
typedef enum {SOURCE = 0, STATE1, SINK} state;

typedef struct part_type {
  state s; // part in which state
  double process_duration;
  double schedule_time[STATE_NUM];   //process start time
  double finish_time[STATE_NUM];     //dismiss time
} part;
#endif
