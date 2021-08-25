#include "Strategy.h"
#include "../Defines.h"
// #include <Servo.h>
// Servo dribler;


#ifndef ATTACKSTR_H
#define ATTACKSTR_H

class AttackStr : public Strategy {
private:

public:
    AttackStr(Hardware *hw) : Strategy(hw){
    }

    void doStrategy() override {
      int backDist = analogRead(BOTTOM_SONAR_PIN);
      int rightDist = analogRead(RIGHT_SONAR_PIN);
      int leftDist = analogRead(LEFT_SONAR_PIN);
      static int st = 0, n = -1, DOn = 0, DOnM = 0, prev = 0;

    //  if(getBallSensor()->isCanSee()){
    //    if 
    //     getMovement()->setSpeed(BASE_SPEED);
    //     getMovement()->setDirection(getBallSensor()->getAngle() * getAngleMultipiller());
    //   } else getMovement()->setSpeed(0);
    DOn = 1;
    getMovement()->setSpeed(0);
    getMovement()->setRotation(90);

      // Serial.println(getLightSensor()->isLine());

      // if(getBallSensor()->isCatched())
      // {
      //   getMovement()->setSpeed(35);
      //   DOn = 1;
      //   prev = millis();
      // if(!getLightSensor()->isLine())
      // {
      //   getMovement()->setRotation(n*90);
      //   getMovement()->setDirection(0);
      // }
      // else if((rightDist > 50 && n == -1) || (leftDist > 50 && n == 1))
      // {
      //   getMovement()->setRotation(n*90);
      //   getMovement()->setDirection(-n*115);
      // }
      // else if((rightDist < 45 && n == -1) || (leftDist < 45 && n == 1))
      // {
      //   getMovement()->setRotation(n*90);
      //   getMovement()->setDirection(n*125);
      // }
      // else
      // {
      //   getMovement()->setSpeed(0);
      //   getMovement()->setRotation(n*(90 - 30));
      // }
      // }
      // else
      // {
      //   DOn = 0;
      //   getMovement()->setSpeed(0);
      // }

      // if(DOnM)
      // {
      // if(millis()-prev < 500)
      //   dribler.writeMicroseconds(MID_PPM - DriblerOn);
      // else
      //   DOnM = 0;  
      // }
      // else if(DOn)
      // {
      // if(millis()-prev < 500)
      //   dribler.writeMicroseconds(MID_PPM + DriblerOn);
      // else
      //   DOn = 0;      
      // }
      // else 
      // {
      //    dribler.writeMicroseconds(MID_PPM);
      // }
      
      
// if(abs(rightDist - leftDist) > 20)
// {
//   getMovement()->setDirection(leftDist > rightDist? -15 : 15);
// }
// else
// {
//   getMovement()->setDirection(0);с
// }
// if(getLightSensor()->isLine()) {
//   getMovement()->setSpeed(GK_SPEED);
//   if(backDist < 30)
//     getMovement()->setDirection(0);
//   else
//     getMovement()->setDirection(leftDist > rightDist? -90 : 90);
// }

    }

    int getType() override {
        return 3;
    }

    ~AttackStr(){

    }
};

#endif
