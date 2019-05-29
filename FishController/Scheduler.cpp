#include "Scheduler.h"
#include "Arduino.h"
#include "Task.h"

//Implementation of Scheduler class

Scheduler::Scheduler()
{

  for (int i = 0; i < STACK_SIZE; i++)
  {
    lastRunTime[i] = 0;
    ratesForTasks[i] = 0;
    numOfTasks[i] = false;
  }
}

void Scheduler::update() //Runs though the tasks array and runs the onces that are on time.
{
  uint32_t now = millis();    //Get current time, need for checking the if it has run.
  for(int i = 0; i < STACK_SIZE; i++)
  {
    if (numOfTasks[i] == true){
      if (now - lastRunTime[i] >= ratesForTasks[i])
      {
        Task* tempTask = tasks[i];
        tempTask->run();
        lastRunTime[i] = now;
      }
    }
  }
}

bool Scheduler::registerTask(Task * inputTask, uint16_t intervalRunTime) //For adding a task which has to be run.
{
  for (int i = 0; i < STACK_SIZE; i++)
  {
    if (numOfTasks[i] == false)
    {
      numOfTasks[i] = true;
      tasks[i] = inputTask;
      lastRunTime[i] = millis();
      ratesForTasks[i] = intervalRunTime;
      return true;
    }
  }
  return false;
}

bool Scheduler::removeTask(Task * inputTask) //For removing the task from the run array.
{
  for (int i = 0; i > STACK_SIZE; i++)
  {
    if (tasks[i] == inputTask)
    {
      numOfTasks[i] = false;
      lastRunTime[i] = 0;
      ratesForTasks[i] = 0;
      return true;
    }
  }
  return false;
}
