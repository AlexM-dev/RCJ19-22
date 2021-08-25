#include "Strategy.h"
#include "../Defines.h"
#include "../hardware/Timer.h"

#ifndef HOMESTR_H
#define HOMESTR_H
class HomeStr : public Strategy
{
private:
    unsigned long prev;
    int dir = 0;
public:
    HomeStr(Hardware *hw) : Strategy(hw){
        hardware->getMovement()->setGyroEnabled(true);
        hardware->getMovement()->setCanMove(true);
        hardware->getMovement()->setDirection(0);
        hardware->getMovement()->setSpeed(0);

        hardware->getMovement()->setRotationByGyro();
    }

    void doStrategy() override {
        if(hardware->getBallSensor()->isCanSee() )
            //Serial.println(hardware->getBallSensor()->getAngle());
            hardware->getMovement()->moveM(45,hardware->getBallSensor()->getAngle());
        else 
            hardware->getMovement()->setSpeed(0);
        //Serial.println(String(hardware->getMovement()->getRobotAngle()) + " | " + String(hardware->getMovement()->getTargetRobotAngle()));

        //Serial.println(hardware->getMovement()->getRobotAngle());
        /*(millis() - prev >= 200){
            if(dir == 1){
                hardware->getMovement()->setSpeed(100);
                hardware->getMovement()->setDirection(hardware->getMovement()->getDirection() + 90);
                dir = 0;
            } else {
                hardware->getMovement()->setSpeed(0);
                dir = 1;
            }
            prev = millis();
        }*/
    }

    int getType() override {
        return 1;
    }

     

    ~HomeStr(){

    }
};

#endif
