#include "Strategy.h"
#include "../Defines.h"

#ifndef GOALKEAPER2_H
#define GOALKEAPER2_H

#define TIMER_DEL 500

class GoalkeaperStr2 : public Strategy {
private:
  unsigned long long prev;
  bool isGoOnBall;
  
public:

    GoalkeaperStr2(Hardware *hw) : Strategy(hw){
        prev = millis();
        isGoOnBall = false;
    }

    void doStrategy() override {
      static int state = 0, kickflag = 0, flagg = 0;
      static unsigned long long prev = 0,  kickprev = 0, prev3 = 0;

      int rightDist = analogRead(RIGHT_SONAR_PIN); 
      int leftDist = analogRead(LEFT_SONAR_PIN);   
      Serial.println(rightDist);

      Log::info("Side", String(abs(getCamSensor()->getCamDist() * sin(radians(getCamSensor()->getCamAngle())))));

      Log::info("Goal", String(getCamSensor()->getCamDist()));
      

      if(getBallSensor()->isCanSee()){
        getMovement()->setDirection(getBallSensor()->getAngle() > 0? 
          90 : -90
        );
        if(abs(getBallSensor()->getAngle()) < 25)
          getMovement()->setSpeed(65);
        else
          getMovement()->setSpeed(GK_SPEED);
      } 

      if(abs(getBallSensor()->getAngle()) < 25 && getBallSensor()->isCanSee()){
        if(state == 0){
          prev = millis();
          state = 1;
        }
      } else {
        // if(state = 1 && abs(getBallSensor()->getAngle()) < 45 && getBallSensor()->isCanSee())
        // {
        //   state = 1;
        // }
        // else{
          state = 0;
        // }
      }

      if(abs(getBallSensor()->getAngle()) < 15 || abs(getBallSensor()->getAngle()) > 170)
        getMovement()->setSpeed(0);

      if(abs(getCamSensor()->getCamAngle()) < 140){
        getMovement()->setSpeed(100);
        getMovement()->setDirection(getCamSensor()->getCamAngle() > 0? 90 : -90);
      }      

      if(getGoalDist() > 60)
      {
        flagg = 1;
        prev3 = millis();
      }
      else {
        flagg = 0;
      }

      if(!getBallSensor()->isCanSee() && getGoalDist() < 38) {
        getMovement()->setDirection(getCamSensor()->getCamAngle() > 0? 
          90 : -90
        );
        getMovement()->setSpeed(GK_MIN_SPEED);
        if(abs(abs(getCamSensor()->getCamAngle()) - 180) < 15)
          getMovement()->setSpeed(0);
      }

<<<<<<< HEAD
      if(getGoalDist() > 38){
=======
      if(getGoalDist() > 36){
>>>>>>> 08be8824e52701fdc43f6371c9f8bb0408de8cb0
        if(flagg = 1 && millis() - prev3 < 3000)
          getMovement()->setSpeed(map(getGoalDist(), 40, 75, 30, GK_MIN_SPEED));
        else
<<<<<<< HEAD
          getMovement()->setSpeed(30);
=======
          getMovement()->setSpeed(GK_MIN_SPEED);
>>>>>>> 08be8824e52701fdc43f6371c9f8bb0408de8cb0
        getMovement()->setDirection(getCamSensor()->getCamAngle());
        if(abs(getCamSensor()->getCamAngle() - getBallSensor()->getAngle()) < 30)
          getMovement()->setDirection(getCamSensor()->getCamAngle() * 1.5);
      }
         
<<<<<<< HEAD
      if(millis() - prev > 750 && state == 1) {
        getMovement()->setSpeed(100);
        getMovement()->setDirection(0);
        if(getGoalDist() >= 75 || millis() - prev > 7000)
          state = 0;
      }

      if(getGoalDist() < 34){
=======
      if(millis() - prev > 1000 && state == 1) {
        getMovement()->setSpeed(70);
        getMovement()->setDirection(0);
        if(getGoalDist() >= 75 || millis() - prev > 7000 || abs(getCamSensor()->getCamDist() * sin(radians(getCamSensor()->getCamAngle()))) > 30)
          state = 0;
      }

      if(getGoalDist() < 32){
>>>>>>> 08be8824e52701fdc43f6371c9f8bb0408de8cb0
        getMovement()->setSpeed(GK_MIN_SPEED);
        if(abs(getBallSensor()->getAngle()) > 30)
          getMovement()->setDirection(0);
        else 
          getMovement()->setDirection(getBallSensor()->getAngle() * 1.3);
        if(getBallSensor()->isCanSee() && abs(getBallSensor()->getAngle()) < 90) {
          getMovement()->setDirection(getBallSensor()->getAngle());  
          if(getBallSensor()->isCanSee() && abs(getBallSensor()->getAngle()) > 45)
            getMovement()->setSpeed(GK_SPEED);
        }
      }

    } 
      

    int getType() override {
        return 4;
    }

    ~GoalkeaperStr2(){

    }

    float getAngleMultipiller(){
      if(abs(getBallSensor()->getAngle()) < 45)
        return 2;
      if(abs(getBallSensor()->getAngle()) < 90)
        return 1.9;
      if(abs(getBallSensor()->getAngle()) < 135)
        return 1.75;
      return 1.55;
    }

    float getGoalDist(){
        return abs(getCamSensor()->getCamDist() * cos(radians(getCamSensor()->getCamAngle())));
    }

    float getAnotherGoalDist(){
        return abs(getCamSensor()->getAnotherCamDist() * cos(radians(getCamSensor()->getAnotherCamAngle())));
    }
};

#endif