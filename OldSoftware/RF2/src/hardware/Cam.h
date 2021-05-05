#ifndef CAM_H
#define CAM_H

#include <Arduino.h>
#include "../Defines.h"
#include "../libs/Log.h"

class CamSensor{
private:

  int getFormatedAngle(int ang);
  int goal;

public:
  int data[4] = {0};

  CamSensor();

  void update();

  void setGoal(int a);

  int getYAngle();

  int getBAngle();

  int getYDist();

  int getBDist();

  int getCamDist();

  int getCamAngle();

  int getAnotherCamDist();

  int getAnotherCamAngle();
};

#endif
