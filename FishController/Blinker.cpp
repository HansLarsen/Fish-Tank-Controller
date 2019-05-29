#include "Blinker.h"

//Implementation of Blinker class

Blinker::Blinker() : pin(13)
{
  pinMode(pin, OUTPUT);
}

Blinker::Blinker(uint8_t _pin) : pin(_pin)
{
  pinMode(pin, OUTPUT);
}

void Blinker::run()
{
  if(on)
  {
    on = false;
  }
  else
  {
    on = true;
  }
  digitalWrite(pin, on);
  return;
}
