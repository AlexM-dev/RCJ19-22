#ifndef LIGHT_H
#define LIGHT_H

#include <Arduino.h>
#include <Wire.h>
#include "../Defines.h"
#include "../libs/Log.h"
#include "../libs/AngleUtils.h"

class LightSensor{
private:
  int angle;
  bool line;

  int getValueFromSensor();

public:
  LightSensor();

  void update();

  int getAngle();

  bool isLine();
};

#endif
