#include "Arduino.h"
#include "Scheduler.h"    //Scheduler class which runs tasks
#include "SchedulerDate.h"
#include "Blinker.h"  //Derived from TimedTask, blinks an LED
#include <Wire.h>
#include "RefillProgram.h"
#include "IOManager.h"
#include "LightManager.h"
#include "AirpumpManager.h"
#include "CO2.h"


Scheduler *taskManager;  // Creating a taskManager to run things at times
SchedulerDate *rtcManager; 
Blinker *blink;   // A led blinker on pin 13
Blinker *blinker;
RefillProgram *refillProgram;
IOManager *inputOutput;
LightManager *LightManagerMain;
AirpumpManager *AirpumpManagerMain;
COManager *COManagerMain;


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
  LightManagerMain = new LightManager(inputOutput);
  AirpumpManagerMain = new AirpumpManager(inputOutput);
  COManagerMain = new COManager(inputOutput);

  taskManager->registerTask(blink, 1000); //Adds the blinker class which runs ever 2 second
  taskManager->registerTask(blinker, 1000);
  taskManager->registerTask(rtcManager, 5000);
  taskManager->registerTask(inputOutput, 10);
  taskManager->registerTask(refillProgram, 10);

  rtcManager->registerTask(refillProgram, 9, 1); //Runs at 9, ever 1 day.
  //Time management was moved into the classes themself.
  rtcManager->registerTask(LightManagerMain, 1, 0); //Runs once an hour, with 0 days interval
  rtcManager->registerTask(AirpumpManagerMain, 1, 0); //Time manageing for the Air pump.
  rtcManager->registerTask(COManagerMain, 1, 0); //For managing the CO2.
}

void loop() {
  taskManager->update();  //Runs the scheduler, which runs the task.
}
