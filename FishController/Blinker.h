#ifndef BLINKER_H
#define BLINKER_H

#include "Arduino.h"
#include "Task.h"

//Simple blinker class which allows to blink an LED

class Blinker : public Task
{
public:
  Blinker();
  Blinker(uint8_t);
  virtual void dateRun()
  {
    return;
  }
  virtual void run() override; //Overriding run method from Task

private:
  uint8_t pin;
  bool on;
};

#endif
