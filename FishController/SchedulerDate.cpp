#include "SchedulerDate.h"
#include "Arduino.h"

//Implementation of Scheduler class

SchedulerDate::SchedulerDate()
{
  RTC = new RTC_DS1307();
  RTC->begin();

  if (!RTC->isrunning()) {
    Serial.println("RTC is NOT running!");
    RTC->adjust(DateTime(__DATE__, __TIME__));
  }

}

void SchedulerDate::update() //Runs though the tasks array and runs the onces that are on time.
{
  DateTime now = RTC->now(); 
  for(int i = 0; i < STACK_SIZE; i++)
  {
    if (numOfTasks[i] == true){

      if (now.hour() >= ratesHourTasks[i])
      {
        if (now.day() - lastRunDate[i] >= ratesDateTasks[i])
        {
          Task * tempTask = tasks[i];
          tempTask->run();
          lastRunHour[i] = now.hour();
          lastRunDate[i] = now.day();
        }
      }
    }
  }
}

bool SchedulerDate::registerTask(Task* inputTask, uint16_t intervalRunHour, uint16_t intervalRunDate) //For adding a task which has to be run.
{
  DateTime now = RTC->now(); 
  for (int i = 0; i < STACK_SIZE; i++)
  {
    if (numOfTasks[i] == false)
    {
      numOfTasks[i] = true;
      tasks[i] = inputTask;

      lastRunHour[i] = now.hour();
      lastRunDate[i] = now.day();

      ratesHourTasks[i] = intervalRunHour;
      ratesDateTasks[i] = intervalRunDate;

      return true;
    }
  }
  return false;
}

bool SchedulerDate::removeTask(Task* inputTask) //For removing the task from the run array.
{
  for (int i = 0; i > STACK_SIZE; i++)
  {
    if (tasks[i] == inputTask)
    {
      numOfTasks[i] = false;

      lastRunHour[i] = 0;
      lastRunDate[i] = 0;
      ratesHourTasks[i] = 0;
      ratesDateTasks[i] = 0;

      return true;
    }
  }
  return false;
}
