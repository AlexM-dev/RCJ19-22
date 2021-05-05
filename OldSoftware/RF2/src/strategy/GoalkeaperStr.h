#include "Strategy.h"
#include "../Defines.h"

#ifndef GOALKEAPER_H
#define GOALKEAPER_H

#define TIMER_DEL 500

class GoalkeaperStr : public Strategy {
private:
  unsigned long long prev;
  byte isGoOnBall;
  
public:

    GoalkeaperStr(Hardware *hw) : Strategy(hw){
        prev = millis();
        isGoOnBall = 0;
    }

    void doStrategy() override {

      int backDist = analogRead(BOTTOM_SONAR_PIN); //получение данных с датчиков расстояния
      int rightDist = analogRead(RIGHT_SONAR_PIN); 
      int leftDist = analogRead(LEFT_SONAR_PIN);   

      getMovement()->setSpeed(GK_SPEED);           //задаем скорость 

      if(getLightSensor()->isLine()) {             //отъезд от линии

        getMovement()->setSpeed(GK_SPEED);

        if(backDist < 30)
          getMovement()->setDirection(0);
        else if(leftDist < 30)
        {
          getMovement()->setDirection(90);
        }
        else if(rightDist < 30)
        {
          getMovement()->setDirection(-90);
        }
        else
        {
          getMovement()->setDirection(180);
        }          
      }
      else
      {
        if(isGoOnBall)                            //выезд на мяч
        {
          if(millis() - prev < GO_ON_BALL_TIME)
          {
              if(getBallSensor()->isCatched())    //в случае если мяч в захвате
              {
                getMovement()->setDirection(0);//тут должно быть смещение по камере     
              }
              else                                //в случае если мяч не в захвате
              {
                getMovement()->setSpeed(GK_SPEED);     
                getMovement()->setDirection(getBallSensor()->getAngle());      
              }  
          }
          else
          {
            isGoOnBall = 0;                       //выход из состояния езды за мячем
          }
        }
        else                                      //не надо ехать за мячем
        {
          if(backDist >= 40)                      //уехали слишком далеко от ворот
          {
            if(leftDist > 50 && rightDist > 50){
              getMovement()->setSpeed(map(backDist, 35, 100, GK_MIN_SPEED, GK_SPEED));
              getMovement()->setDirection(180);
            }
            else
            {
              getMovement()->setDirection(leftDist > rightDist? -90 : 90);
            }
          }
          else if (backDist <= 25)                //слишком близко к воротам
          {
              getMovement()->setSpeed(GK_SPEED);
              getMovement()->setDirection(0);
          }
                   
          else                                    //находимся на нормальном расстоянии от ворот
          {  
            if(getBallSensor()->isCanSee()) {     //мяч видно
              if((getBallSensor()->getDistanse() > GK_MIN_BALL_DIST && abs(getBallSensor()->getAngle()) < 15 ) || getBallSensor()->isCatched()) //мяч достаточно близко для выезда на него
              {
                  isGoOnBall = 1;
                  prev = millis();
              }
              else                                //движение вдоль белой линии
              {
                if(getBallSensor()->getAngle() > 135 || getBallSensor()->getAngle() < -135)
                  getMovement()->setSpeed(0);
                else if(getBallSensor()->getAngle() < -GK_BALL_ANG)
                  getMovement()->setDirection(-90);
                else if(getBallSensor()->getAngle() > GK_BALL_ANG)
                  getMovement()->setDirection(90);
                else getMovement()->setSpeed(0);

                getMovement()->setDirection(getBallSensor()->getAngle() > 0? 90 : -90);
              } 
            }
            else                                   //мяч не видно, смещаемся в центр ворот
            {      
              if(abs(rightDist - leftDist) < 40)
              {
                getMovement()->setSpeed(0);
              }
              else
              {
                getMovement()->setDirection(leftDist > rightDist? -90 : 90);
              }
            }
          }
        } 
      }
    }  
      

    int getType() override {
        return 4;
    }

    ~GoalkeaperStr(){

    }
};

#endif


// if(getBallSensor()->isCanSee()){
      // getMovement()->setSpeed(spd);  
      //   if (/* на центральной линии */)
      //   {
      //     if(getBallSensor()->getAngle() > 0)
      //         getMovement()->setDirection(270);
      //     else if (getBallSensor()->getAngle() < 0)
      //         getMovement()->setDirection(90);
      //     else
      //         getMovement()->setSpeed(0);          
      //   }
      //   else if (/* на правом углу центральной линии */)
      //   {
      //     if (getBallSensor()->getAngle() < 0)
      //         getMovement()->setDirection(90);
      //     else if(getBallSensor()->getAngle() > 90)
      //         getMovement()->setDirection(180);
      //     else
      //         getMovement()->setSpeed(0); 
      //   }
      //   else if (/* на левом углу центральной линии */)
      //   {
      //     if(getBallSensor()->getAngle() > 0)
      //       getMovement()->setDirection(270);
      //     else if(getBallSensor()->getAngle() < -90)
      //       getMovement()->setDirection(180);
      //     else
      //       getMovement()->setSpeed(0); 
      //   }
      //   else if (/* на правой линии */)
      //   {
      //     if(getBallSensor()->getAngle() > 90)
      //       getMovement()->setDirection(180);
      //     else if (getBallSensor()->getAngle() < 90)
      //       getMovement()->setDirection(0);
      //     else
      //       getMovement()->setSpeed(0); 
      //   }
      //   else if (/* на левой линии */)
      //   {
      //     if(getBallSensor()->getAngle() < -90)
      //       getMovement()->setDirection(180);
      //     else if (getBallSensor()->getAngle() > -90)
      //       getMovement()->setDirection(90);
      //     else
      //       getMovement()->setSpeed(0); 
      //   }
      // } 
      // else
      // {
      //   //движемся к центру белой линии
      // }
