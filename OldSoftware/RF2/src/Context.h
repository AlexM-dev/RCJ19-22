#include "hardware/Hardware.h"
#include "Defines.h"
#include "strategy/Strategy.h"

#include "strategy/BallFollowStr.h"
#include "strategy/GoalkeaperStr2.h"
#include "strategy/DebugStr.h"
#include "strategy/AttackStr.h"
#include "strategy/HomeStr.h"
#include "libs/Log.h"

#ifndef CONTEXT_H
#define CONTEXT_H

class Context
{
private:
    Hardware hardware;
    Strategy *curStrategy;
    char command;

    int strategySelector(){
        if(hardware.getBallSensor()->isCatched())
            return 3;
        return 2;
    }
public:
    Context(Servo * drib){
        command = ' ';
        hardware.getDribbler()->setMotor(drib);
<<<<<<< HEAD
        curStrategy = new DebugStr(&hardware);
=======
        curStrategy = new BallFollowStr(&hardware);
>>>>>>> 08be8824e52701fdc43f6371c9f8bb0408de8cb0
    }

    void updateHardware(){
        hardware.updateHardware();
    }

    void updareStrategy(){
        if(hardware.getButton1()->isClick()){ //System Buttons
            hardware.getMovement()->setCanMove(!hardware.getMovement()->isCanMove());
            Log::info("Buttons", hardware.getMovement()->isCanMove()? "Can Move" : "Stop");
            if(hardware.getMovement()->isCanMove())
                delay(5000);
        }
        if(hardware.getButton1()->isLongClick()){
            hardware.getMovement()->setRotationByGyro();
            Log::info("Buttons", "Set Gyro");
        }

        //Update selected Strategy
        curStrategy->doStrategy();

        //Serial Commands After Str
        serialCommands();
    }

    void selectStrategy(){
        /*int type = strategySelector();
        if(type != curStrategy->getType())
            switch (type){
                case 1:
                    curStrategy = new HomeStr(&hardware);
                    break;
                case 2:
                    curStrategy = new BallFollowStr(&hardware);
                    break;
                case 3:
                    curStrategy = new AttackStr(&hardware);
                    break;
            }*/
    }

    void setup(){

    }

    //Control from Serial Port
    void serialCommands(){
        if(Serial.available()) {
            command = Serial.read();
            Log::info("Commands", "Command Recieved"); 
        }
        switch (command){
                case 'm':
                    hardware.getMovement()->setCanMove(!hardware.getMovement()->isCanMove());
                    Log::info("Commands", hardware.getMovement()->isCanMove()? "Can Move" : "Stop");
                    command = ' ';
                    break;
                case 'b':
                    hardware.getMovement()->moveM(70, 180);
                    break;
                case 'f':
                    hardware.getMovement()->moveM(70, 0);
                    break;
                case 's':
                    hardware.getMovement()->setSpeed(0);
                    break;
                case 'c':
                    command = ' ';
                    Log::info("Commands", "Continue");
                    break;
                case 'g':
                    hardware.getMovement()->setRotationByGyro();
                    Log::info("Commands", "Set Gyro");
                    command = ' ';
                    break;
            }
    }
};

#endif
