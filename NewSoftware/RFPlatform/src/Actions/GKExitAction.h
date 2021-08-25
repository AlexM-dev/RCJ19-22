#pragma once

#include "BaseAction.h"

class GKExitAction : public BaseAction
{
private:	
    BallSensor *ball;
public:
	GKExitAction(ActionsController* cont) : BaseAction(cont)
	{
        ball = getDevice<BallSensor>(BALL_DEVICE_ID);
        createSimpleTimer(0, 2000);
	};

	void onUpdate() override 
	{
        
        if(ball->isCatched())
        {
            addVector(0);
            stopTimer(0);
        }
        else
            startTimer(0);
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
            finish();
	}
};