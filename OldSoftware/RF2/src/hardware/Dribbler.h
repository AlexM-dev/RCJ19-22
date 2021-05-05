
#ifndef DRIBBLER_H
#define DRIBBLER_H

#include <Arduino.h>
#include "../Defines.h"
#include "../libs/Log.h"
#include <Servo.h>

class Dribbler {
    private:    
        bool calibrated;
        int speed;
        Servo *servo;
        //Servo motor;

    public:
        Dribbler() {
            calibrated = false;
            speed = 0;

            Log::info("Dribbler","Calibrated Success");
        }

        void setMotor(Servo * srv){
            servo = srv;
        }

        void update(){
            
        }

        void setSpeed(int spd){
            if(this->speed != spd && servo != NULL){
                this->speed = spd;
                servo->write(this->speed);
            }
        }

};

#endif
