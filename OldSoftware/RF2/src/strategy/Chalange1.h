#include "Strategy.h"
#include "../Defines.h"
#include "../libs/AngleUtils.h"
#include <Servo.h>

Servo dribler;

#ifndef CHALANGE1_H
#define CHALANGE1_H

class Chalange1 : public Strategy {
private:

public:
    Chalange1(Hardware *hw) : Strategy(hw){
    }

    void doStrategy() override {
      
    }


    int getType() override {
        return 5;
    }

    ~Chalange1(){ 

    }

    float getGoalDist(){
        return abs(getCamSensor()->getCamDist() * cos(radians(getCamSensor()->getCamAngle())));
    }

    float getAnotherGoalDist(){
        return abs(getCamSensor()->getAnotherCamDist() * cos(radians(getCamSensor()->getAnotherCamAngle())));
    }

};

#endif
