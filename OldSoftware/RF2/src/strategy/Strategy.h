#include "../hardware/Hardware.h"

#ifndef STRATEGY_H
#define STRATEGY_H

class Strategy {
public:
    Hardware *hardware;

    Strategy(){

    }

    Strategy(Hardware *hw){
        hardware = hw;
    }

    Movement * getMovement(){
        return hardware->getMovement();
    }

    BallSensor * getBallSensor(){
        return hardware->getBallSensor();
    }

    LightSensor * getLightSensor(){
        return hardware->getLightSensor();
    }

    CamSensor * getCamSensor(){
        return hardware->getCamSensor();
    }

    Dribbler * getDribbler(){
        return hardware->getDribbler();
    }

    virtual void doStrategy(){};

    virtual int getType(){
        return 0;
    }
};

#endif
