#pragma once

#include "BaseAction.h"
#include "AtackAction.h"

class BallFollowAction : public BaseAction
{
private:	
    BallSensor *ball;
public:
	BallFollowAction(ActionsController* cont) : BaseAction(cont)
	{
        ball = getDevice<BallSensor>(BALL_DEVICE_ID);
        createSimpleTimer(0, 500);
	};

	void onUpdate() override 
	{
        // Log::info(getDevice<Cam>(CAM_DEVICE_ID)->getRivalAngle());

        if(ball->isCanSee())
        {
          if(ball->getDistanse() > 35)
            addVector(ball->getAngle() * 1.5, 50);
          else
            addVector(ball->getAngle());
        }
        if(ball->isCatched())
            startTimer(0);
        else
            stopTimer(0);
	}

	void onStart() override 
	{

	}

	void onStop() override 
	{

	}

	void OnTimerEnd(Timer *timer)
	{
        if(timer->getID() == 0)
            startAction(new AtackAction(controller));
	}

    float getAngleMultipiller(){
      if(ball->getDistanse() > 35)
      {
        // if(abs(ball->getAngle()) < 45)
        //   return 2;
        // if(abs(ball->getAngle()) < 90)
        //   return 1.9;
        // if(abs(ball->getAngle()) < 135)
        //   return 1.65;
        // return 1.55;
        return 1.5;
      }
      return 1;
    }

};
