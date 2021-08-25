#include "Timer.h"

void (*Timer::user_onTick)(void);

Timer::Timer(){
  enabled = true;
  del = 1000;
  previousMillis = millis();
}

Timer::Timer(long newDel){
  del = newDel;
  enabled = true;
  previousMillis = millis();
}

void Timer::setOnTickListener(void (*function)(void)){
  user_onTick = function;
}

void Timer::tick(){
   previousMillis = millis();
   if(!user_onTick)
    return;
  user_onTick();
}

void Timer::update(){
  if(enabled && millis() - previousMillis >= del)
    tick();
}

void Timer::setEnabled(bool en){
  enabled = en;
  previousMillis = millis();
}

void Timer::setDelay(long newDel){
  del = newDel;
  previousMillis = millis();
}

void Timer::start(){
  enabled = true;
}

void Timer::stop(){
  enabled = false;
}

bool Timer::isEnabled(){
  return enabled;
}
