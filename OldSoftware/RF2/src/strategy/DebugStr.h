#include "Strategy.h"
#include "../Defines.h"

#ifndef DEBUGSTR_H
#define DEBUGSTR_H
class DebugStr : public Strategy
{
private:
    
public:
    DebugStr(Hardware *hw) : Strategy(hw){
        hardware->getMovement()->setGyroEnabled(true);
        hardware->getMovement()->setDirection(0);
        hardware->getMovement()->setSpeed(0);
        hardware->getMovement()->setRotationByGyro();
    }

    bool isBeenCacthed = false;
    long long prev1, prev2;

    void doStrategy() override {
        Log::info("Gyro", String(getMovement()->getRobotAngle()));
        Log::info("Line", String(getLightSensor()->isLine()));
        Log::info("LineA", String(getLightSensor()->getAngle()));
        Log::info("Cam", String(getGoalDist()));
        Log::info("Ball", String(getBallSensor()->getAngle()));
        Log::info("Ball", String(getBallSensor()->getDistanse()));
        Log::info("isBall", String(getBallSensor()->isCanSee()));
        Log::info("isBall", String(getBallSensor()->isCatched()));
    }


    int getType() override {
        return 10;
    }

    ~DebugStr(){

    }

    float getGoalDist(){
        return abs(getCamSensor()->getCamDist() * cos(radians(getCamSensor()->getCamAngle())));
    }

    float getAnotherGoalDist(){
        return abs(getCamSensor()->getAnotherCamDist() * cos(radians(getCamSensor()->getAnotherCamAngle())));
    }

     float getAngleMultipiller(){
      if(getBallSensor()->getDistanse() > 45)
      {
        if(abs(getBallSensor()->getAngle()) < 45)
          return 2;
        if(abs(getBallSensor()->getAngle()) < 90)
          return 1.85;
        if(abs(getBallSensor()->getAngle()) < 135)
          return 1.75;
        return 1.55;
      }
      return 1;
    }
};

#endif
