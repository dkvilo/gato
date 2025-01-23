#include "dk_timer.h"

void DKTimer_Start(Timer_t* timer, double time)
{
  timer->time = time;
  timer->time_left = time;
  timer->is_running = true;
}

void DKTimer_Update(Timer_t* timer, double dt)
{
  if (timer->is_running) {
    timer->time_left -= dt;
    if (timer->time_left <= 0) {
      timer->is_running = false;
    }
  }
}

void DKTimer_Stop(Timer_t* timer)
{
  timer->is_running = false;
}

void DKTimer_Reset(Timer_t* timer)
{
  timer->time_left = timer->time;
  timer->is_running = true;
}

bool DKTimer_IsRunning(Timer_t* timer)
{
  return timer->is_running;
}

float DKTimer_GetPercent(Timer_t* timer)
{
  return timer->time_left / timer->time;
}

float DKTimer_GetTimeLeft(Timer_t* timer)
{
  return timer->time_left;
}

float DKTimer_GetTime(Timer_t* timer)
{
  return timer->time;
}
