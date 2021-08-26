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
		startTimer(0);
	};

	void onUpdate() override 
	{
    	addVector(ball->getAngle() * 1.2);
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