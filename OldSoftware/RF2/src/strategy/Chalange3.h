#include "Strategy.h"
#include "../Defines.h"
#include "../libs/AngleUtils.h"
#include <Servo.h>

Servo dribler;

#ifndef CHALANGE3_H
#define CHALANGE3_H

class Chalange3 : public Strategy {
private:

public:
    Chalange1(Hardware *hw) : Strategy(hw){
    }

    void doStrategy() override {
      
    }


    int getType() override {
        return 7;
    }

    ~Chalange3(){ 

    }

    float getGoalDist(){
        return abs(getCamSensor()->getCamDist() * cos(radians(getCamSensor()->getCamAngle())));
    }

    float getAnotherGoalDist(){
        return abs(getCamSensor()->getAnotherCamDist() * cos(radians(getCamSensor()->getAnotherCamAngle())));
    }

};

#endif
