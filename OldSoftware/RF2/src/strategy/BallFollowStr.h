#include "Strategy.h"
#include "../Defines.h"
#include "../libs/AngleUtils.h"
#include <Servo.h>

Servo dribler;

#ifndef BALLFOLLOWINGSTR_H
#define BALLFOLLOWINGSTR_H

class BallFollowStr : public Strategy {
private:

public:
    BallFollowStr(Hardware *hw) : Strategy(hw){
    }

    void doStrategy() override {
      static bool DOn = 0, DOnM = 0;
      static unsigned long long prev = millis(), prev2 = millis();
      static int yCoord, xCoord;

      xCoord = getCamSensor()->getCamDist() * sin(getCamSensor()->getCamAngle());
      yCoord = abs(getCamSensor()->getCamDist() * cos(getCamSensor()->getCamAngle()));

      int rightDist = analogRead(RIGHT_SONAR_PIN); 
      int leftDist = analogRead(LEFT_SONAR_PIN);   

      if(getLightSensor()->isLine()) {
        getMovement()->setSpeed(BASE_SPEED);
        if(getAnotherGoalDist() < 35)
        {
          getMovement()->setDirection(180);
        }
        if(getGoalDist() < 35)
        {
          getMovement()->setDirection(0);
        }
        if(leftDist < 25)
        {
          getMovement()->setDirection(90);
        }
        if(rightDist < 25)
        {
          getMovement()->setDirection(-90);
        }
      }
      else
      { 
        if(getBallSensor()->isCatched() || getBallSensor()->isCanSee()){
          if(getBallSensor()->isCatched() || abs(getBallSensor()->getAngle()) < 30 || getBallSensor()->getDistanse() > 60){
            DOn = 1; 
            prev = millis();
            getMovement()->setSpeed(BASE_SPEED);
            if(getBallSensor()->isCatched())
            {
              getMovement()->setDirection(getCamSensor()->getAnotherCamAngle() * 2);
            }
            else
            {
              if(abs(getBallSensor()->getAngle()) < 90 && abs(getBallSensor()->getAngle()) > 15)
                getMovement()->setSpeed(50);
              else
                getMovement()->setSpeed(BASE_SPEED);
              getMovement()->setDirection(getBallSensor()->getAngle() * getAngleMultipiller());
            }
          }
          else
          {
            if(abs(getBallSensor()->getAngle()) < 90 && abs(getBallSensor()->getAngle()) > 15)
              getMovement()->setSpeed(50);
            else
              getMovement()->setSpeed(BASE_SPEED);
            getMovement()->setDirection(getBallSensor()->getAngle() * getAngleMultipiller());
            DOn = 0;
          }
        } 
        else
        {
          getMovement()->setDirection(getCamSensor()->getCamAngle());
          getMovement()->setSpeed(BASE_SPEED); 
          if(getGoalDist() <= 30)
              getMovement()->setSpeed(0);    

          if(getGoalDist() < 20){
            getMovement()->setDirection(0);
            getMovement()->setSpeed(BASE_SPEED); 
          }   

          // if(getAnotherGoalDist() < 30){
          //   getMovement()->setDirection(180);
          //   getMovement()->setSpeed(BASE_SPEED); 

          // }
        }
      }

      if(getCamSensor()->getAnotherCamAngle() < 45 && getAnotherGoalDist() < 40 && (getBallSensor()->isCatched() || abs(getBallSensor()->getAngle()) < 30 || getBallSensor()->getDistanse() > 60))
      {
        DOn = 0;
      }

       if(millis() - prev < 500)
       {
          if(DOn == 1)
            dribler.writeMicroseconds(MID_PPM - 90);
          if(DOn == 2)
            dribler.writeMicroseconds(MID_PPM + 90);
          if(DOn == 0)
            dribler.writeMicroseconds(MID_PPM);
       }
       else
       {
          DOn = 0;
          dribler.writeMicroseconds(MID_PPM);
       }      


      /*if(DOn == 1)
      {
        if(millis() - prev < 500)
          dribler.writeMicroseconds(MID_PPM - 90);
        else
          DOn = 0;      
      }
      else if(DOn == 2)
      {
        if(millis() - prev < 500)
          dribler.writeMicroseconds(MID_PPM + 90);
        else
          DOn = 0;      
      }
      else
      {
          dribler.writeMicroseconds(MID_PPM);
      }*/


      // if(getGoalDist2() <= 30){
      //   getMovement()->setDirection(180);
      //   getMovement()->setSpeed(BASE_SPEED);
      // }
    }


    int getType() override {
        return 2;
    }

    ~BallFollowStr(){ 

    }

    float getAngleMultipiller(){
      if(getBallSensor()->getDistanse() > 60)
      {
        if(abs(getBallSensor()->getAngle()) < 45)
          return 2;
        if(abs(getBallSensor()->getAngle()) < 90)
          return 1.85;
        if(abs(getBallSensor()->getAngle()) < 135)
          return 1.65;
        return 1.45;
      }
      return 1.4;
    }

    float getCamAngleMultipiller(){
        if(abs(getBallSensor()->getAngle()) < 45)
          return 2;
        if(abs(getBallSensor()->getAngle()) < 90)
          return 1.7;
        if(abs(getBallSensor()->getAngle()) < 135)
          return 1.5;
        return 1.325;
    }

    float getGoalDist(){
        return abs(getCamSensor()->getCamDist() * cos(radians(getCamSensor()->getCamAngle())));
    }

    float getAnotherGoalDist(){
        return abs(getCamSensor()->getAnotherCamDist() * cos(radians(getCamSensor()->getAnotherCamAngle())));
    }

};

#endif
