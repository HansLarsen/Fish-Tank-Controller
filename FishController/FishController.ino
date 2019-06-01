#include "Arduino.h"
#include "Scheduler.h"    //Scheduler class which runs tasks
#include "SchedulerDate.h"
#include "Blinker.h"  //Derived from TimedTask, blinks an LED
#include <Wire.h>
#include "RefillProgram.h"
#include "IOManager.h"


Scheduler *taskManager;  // Creating a taskManager to run things at times
SchedulerDate *rtcManager; 
Blinker *blink;   // A led blinker on pin 13
Blinker *blinker;
RefillProgram *refillProgram;
IOManager *inputOutput;

void setup() {
  Serial.begin(9600);
  
  Wire.begin();

  Serial.println("Begin");
  
  taskManager = new Scheduler();
  rtcManager = new SchedulerDate();
  blink = new Blinker(2);
  blinker = new Blinker();
  inputOutput = new IOManager();
  refillProgram = new RefillProgram(inputOutput); 

  taskManager->registerTask(blink, 1000); //Adds the blinker class which runs ever 2 second
  taskManager->registerTask(blinker, 1000);
  taskManager->registerTask(rtcManager, 5000);
  taskManager->registerTask(refillProgram, 10);

  rtcManager->registerTask(refillProgram, 9, 1);
}

void loop() {
  taskManager->update();  //Runs the scheduler, which runs the task.
}
