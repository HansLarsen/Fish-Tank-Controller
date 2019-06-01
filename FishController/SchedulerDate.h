#ifndef SCHEDULERDATE_H
#define SCHEDULERDATE_H

#include "Arduino.h"
#include "RTClib.h"
#include "Task.h"
#define STACK_SIZE 20

//Scheduler to run tasks

class SchedulerDate : public Task
{
public:
  SchedulerDate();
  void update();
  virtual void run()
  {
    update();
  }

  virtual void dateRun(int hour)
  {
    return;
  }

  bool registerTask(Task * inputTask, uint16_t intervalRunHour, uint16_t intervalRunDate);
  bool removeTask(Task * inputTask);
private:
  RTC_DS1307 *RTC;
  Task * tasks [STACK_SIZE]; //Array for pointers to tasks.
  bool numOfTasks[STACK_SIZE]; //For figuring out if a place in the tasks is occupied.

  uint32_t lastRunHour[STACK_SIZE]; //Array for the last time a task was run.
  uint32_t lastRunDate[STACK_SIZE]; //Array for the last time a task was run.

  uint16_t ratesHourTasks[STACK_SIZE]; //The interval at which tasks have to run.
  uint16_t ratesDateTasks[STACK_SIZE]; //The interval at which tasks have to run.
};

#endif
