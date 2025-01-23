#if !defined(DK_TIMER_H)
#define DK_TIMER_H

#include <stdbool.h>

typedef struct Timer_t {
  double time;
  double time_left;
  bool is_running;
} Timer_t;

void DKTimer_Start(Timer_t* timer, double time);

void DKTimer_Update(Timer_t* timer, double dt);

void DKTimer_Stop(Timer_t* timer);

void DKTimer_Reset(Timer_t* timer);

bool DKTimer_IsRunning(Timer_t* timer);

float DKTimer_GetPercent(Timer_t* timer);

float DKTimer_GetTimeLeft(Timer_t* timer);

float DKTimer_GetTime(Timer_t* timer);


#endif // DK_TIMER_H