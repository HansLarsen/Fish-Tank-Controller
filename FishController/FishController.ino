#include "Scheduler.h"    //Scheduler class which runs tasks
#include "SchedulerDate.h"
#include "Blinker.h"  //Derived from TimedTask, blinks an LED
#include <Wire.h>
#include "RefillProgram.h"


Scheduler *taskManager;  // Creating a taskManager to run things at times
SchedulerDate *rtcManager; 
Blinker *blink;   // A led blinker on pin 13
Blinker *blinker;
RefillProgram *refillProgram;

void setup() {
  Serial.begin(9600);
  
  Wire.begin();

  Serial.println("Begin");
  
  taskManager = new Scheduler();
  rtcManager = new SchedulerDate();
  blink = new Blinker(2);
  blinker = new Blinker();
  refillProgram = new RefillProgram(26, 27, 31, 33, 32, 34, 6, 7, 8, 9, 37, 38, false); 
  /* drainPin, refillPin, topFloatPin, toppestFloatPin,buttomFloatPin,buttomestFloatPin,indFillLED,indDrainLED,indAboveFull,indBelowBottom,
  buttonTopUp,buttonWaterChange, flipButtons = false*/

  taskManager->registerTask(blink, 1000); //Adds the blinker class which runs ever 2 second
  taskManager->registerTask(blinker, 1000);
  taskManager->registerTask(rtcManager, 5000);
  taskManager->registerTask(refillProgram, 10);

  rtcManager->registerTask(refillProgram, 9, 1);
}

void loop() {
  taskManager->update();  //Runs the scheduler, which runs the task.
}
