#pragma once

#include "BaseAction.h"
#include "GKExitAction.h"

class GKMainAction : public 
{BaseAction
private:	
    BallSensor *ball;
    Cam *cam;
    int speed;
public:
	BallFollowAction(ActionsController* cont) : BaseAction(cont)
	{
        ball = getDevice<BallSensor>(BALL_DEVICE_ID);
        cam = getDevice<Cam>(CAM_DEVICE_ID);
        createSimpleTimer(0, 2000);
        createSimpleTimer(1, 1000);
	};

	void onUpdate() override 
	{
        // Log::info(getDevice<Cam>(CAM_DEVICE_ID)->getRivalAngle());

        if(ball->isCanSee())
        {
            stopTimer(1);
            speed = map(map(abs(ball->getAngle()), 0, 90, 0, 200) + map(ball->getDistanse(), 0, 70, 0, 200), 0, 400, 0, 225);

            if(abs(ball->getAngle()) < 25)
              startTimer(0);
            else
            {
                stopTimer(0);  
                if(abs(ball->getAngle()) < 90)
                {
                if(ball->getAngle() > 0)
                    addVector(90, speed);
                else
                    addVector(-90, speed);
            }

            if(cam->getAngle() < 130 && cam->getAngle() > 0)
                setVector(90);
            else if(cam->getAngle() > -130 && cam->getAngle() < 0)
                setVector(90);

            if(cam->getDistanse() > 25)
                addVector(180);
            else if(cam->getDistanse() < 22)
                addVector(0);
                
        }  


          if(cam->getMyAngle())  
        }
        else
          startTimer(1); 



        if(ball->getDistanse() > 35)
            addVector(ball->getAngle() * 1.5, 50);
          else
            addVector(ball->getAngle());    
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
            startAction(new GKExitAction(controller));
        else if(timer->getID() == 1)
            startAction(new GKGoCenterAction(controller));
	}

};