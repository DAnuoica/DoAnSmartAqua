#include <ESP8266WiFi.h>  
//#include<Arduino.h>
#include "Timer.h"
#include "WorkScheduler.h"

WorkScheduler::WorkScheduler(int workPin, unsigned long times, void (*func)(int))
{
  _workPin = workPin;
  _workTime = times;
  _ellapsedTime = 0;
  this->func = func;
}

WorkScheduler::WorkScheduler(unsigned long times, void (*func)()){
  _workPin = -1;
  _workTime = times;
  _ellapsedTime = 0;
  this->func2 = func;
  }

WorkScheduler::~WorkScheduler()
{
  _workPin = 0;
  _workTime = 0;
  _ellapsedTime = 0;
  func = NULL;
  func2= NULL;
}

void WorkScheduler::update()
{
  _ellapsedTime += Timer::getInstance()->delta();
  if (_ellapsedTime >= _workTime)
  {
    _ellapsedTime -= _workTime;
    if (func != NULL || func2 != NULL)
    {
      if (_workPin == -1)
        func2();
      else
        func(_workPin);
    }
  }
}
