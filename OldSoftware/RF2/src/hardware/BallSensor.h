#ifndef BALLSENSOR_H
#define BALLSENSOR_H

#include <Arduino.h>
#include <SoftwareSerial.h>
#include "../libs/Log.h"
#include "../Defines.h"

class BallSensor{
private:
  float angle;
  float distanse;
  bool canSee;
  bool ballCatched;

  SoftwareSerial *tsopSerial;

  int getValueFromSensor();

  bool isBallCatched();
public:
  BallSensor();

  void update();

  float getAngle();
  float getDistanse();

  bool isCanSee();

  bool isCatched();
};

#endif
