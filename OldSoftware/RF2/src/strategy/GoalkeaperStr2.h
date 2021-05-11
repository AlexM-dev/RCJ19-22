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
      //static int err = 0;

      if(getBallSensor()->isCanSee()){
        getMovement()->setDirection(getBallSensor()->getAngle() > 0? 
          90 : -90
        );
        if(abs(getBallSensor()->getAngle()) < 90)
          getMovement()->setSpeed(GK_SPEED);//map(abs(getBallSensor()->getAngle()), 0, 90, 35, 100));
        else
          getMovement()->setSpeed(70);
      } 
      else {
        getMovement()->setDirection(getCamSensor()->getCamAngle() > 0? 
          90 : -90
        );
        getMovement()->setSpeed(GK_SPEED);
        if(abs(abs(getCamSensor()->getCamAngle()) - 180) < 15)
          getMovement()->setSpeed(0);
      }

      if(abs(getBallSensor()->getAngle()) < 30 && getBallSensor()->isCanSee()){
        if(state == 0){
          prev = millis();
          state = 1;
          // if(getBallSensor()->getDistanse() < 35) {
          //   state = 0;
          //   Serial.println("cansel timer");
          // }
        }
      } else {
        if(state = 1 && abs(getBallSensor()->getAngle()) < 90 && getBallSensor()->isCanSee())
        {
          state = 1;
        }
        else{
          state = 0;
        }
      }

      if(abs(getBallSensor()->getAngle()) < 10)
        getMovement()->setSpeed(0);

      if(abs(getCamSensor()->getCamAngle()) < 140){
        getMovement()->setSpeed(GK_MIN_SPEED);
        getMovement()->setDirection(getCamSensor()->getCamAngle() > 0? 90 : -90);
      }      

      if(getGoalDist() > 65)
      {
        flagg = 1;
        prev3 = millis();
      }
      else {
        flagg = 0;
      }

      if(getGoalDist() > 34){
        if(flagg = 1 && millis() - prev3 < 3000)
          getMovement()->setSpeed(map(getGoalDist(), 30, 75, 17, GK_MIN_SPEED));
        else
          getMovement()->setSpeed(23);
        getMovement()->setDirection(getCamSensor()->getCamAngle());
        if(abs(getCamSensor()->getCamAngle() - getBallSensor()->getAngle()) < 30)
          getMovement()->setDirection(getCamSensor()->getCamAngle() * 1.5);
      }
         
      if(millis() - prev > 1500 && state == 1) {
        getMovement()->setDirection(getBallSensor()->getAngle() * 2);
        getMovement()->setSpeed(70);
        if(getGoalDist() >= 75 || millis() - prev > 5000 || abs(getCamSensor()->getCamDist() * sin(radians(getCamSensor()->getCamAngle()))) < 0)
          state = 0;
      }

      if(getGoalDist() < 30){
        getMovement()->setSpeed(GK_MIN_SPEED);
        getMovement()->setDirection(0);
        if(getBallSensor()->isCanSee())
          getMovement()->setDirection(getBallSensor()->getAngle() > 0? 45 : -45);  
      }

    } 
      

    int getType() override {
        return 4;
    }

    ~GoalkeaperStr2(){

    }

    //  int takeTargetAngleFromTrajectory(){

    //   static int cta = getBallSensor()->getAngle(), ota = 0, cd = getBallSensor()->getDistance(), od = 0, p = millis();
      
    //   if(millis() - p > 10)
    //   {
    //     ota = cta;
    //     od = cd; 
    //   }
    //   else if(millis() - p > 500)
    //   {
        

    //     cta = getBallSensor()->getAngle();
    //     cd = getBallSensor()->getDistance();
    //     p = millis();
    //   }
    // }

    float getGoalDist(){
        return abs(getCamSensor()->getCamDist() * cos(radians(getCamSensor()->getCamAngle())));
    }

    float getAnotherGoalDist(){
        return abs(getCamSensor()->getAnotherCamDist() * cos(radians(getCamSensor()->getAnotherCamAngle())));
    }
};

#endif