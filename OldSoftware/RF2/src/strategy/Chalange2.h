#include "Strategy.h"
#include "../Defines.h"
#include "../libs/AngleUtils.h"
#include <Servo.h>

Servo dribler;

#ifndef CHALANGE2_H
#define CHALANGE2_H

class Chalange2 : public Strategy {
private:

public:
    Chalange2(Hardware *hw) : Strategy(hw){
    }

    void doStrategy() override {
      
    }


    int getType() override {
        return 6;
    }

    ~Chalange2(){ 

    }

    float getGoalDist(){
        return abs(getCamSensor()->getCamDist() * cos(radians(getCamSensor()->getCamAngle())));
    }

    float getAnotherGoalDist(){
        return abs(getCamSensor()->getAnotherCamDist() * cos(radians(getCamSensor()->getAnotherCamAngle())));
    }

};

#endif
