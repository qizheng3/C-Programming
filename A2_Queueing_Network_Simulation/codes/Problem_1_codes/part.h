#ifndef _PART
#define _PART
#define STATE_NUM 5
typedef enum {SOURCE = 0, STATE1, STATE2, STATE3, SINK} state;

typedef struct part_type {
  state s; // part in which state
  double process_duration;
  double schedule_time[STATE_NUM];   //process start time [State i]
  double finish_time[STATE_NUM];     //parts dismiss time [State i]
} part;
#endif
