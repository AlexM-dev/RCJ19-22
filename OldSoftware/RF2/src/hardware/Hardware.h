#include "../Defines.h"

#include "Movement.h"
#include "BallSensor.h"
#include "Light.h"
#include "Button.h"
#include "Cam.h"
#include "Dribbler.h"

#ifndef HARDWARE_H
#define HARDWARE_H

class Hardware{
private:
    Movement movement;
    BallSensor ballSensor;
    LightSensor lightSensor;
    CamSensor camSensor;
    Button btn1;//, btn2(BUTTON_PIN2);
    Dribbler dribbler;

public:
    Hardware(){
        movement.initilizeMotors();
        btn1.init(BUTTON_PIN1);
    }

    void updateHardware(){
        movement.update();
        ballSensor.update();
        lightSensor.update();
        btn1.update();
        camSensor.update();
        dribbler.update();
        //btn2.update();
    }

    Movement * getMovement(){
        return &movement;
    }
    CamSensor * getCamSensor(){
        return &camSensor;
    }
    BallSensor * getBallSensor(){
        return &ballSensor;
    }
    LightSensor * getLightSensor(){
        return &lightSensor;
    }
    Button * getButton1(){
        return &btn1;
    }
    Dribbler * getDribbler(){
        return &dribbler;
    }
    /*Button * getButton2(){
        return &btn2;
    }*/
};

#endif
