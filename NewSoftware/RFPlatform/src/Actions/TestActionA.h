#pragma once

#include "BaseAction.h"

class TestActionA : public BaseAction
{
private:
	int i;
	LineSensor *line;
public:
	TestActionA(ActionsController* cont) : BaseAction(cont)
	{
		i = 0;
		line = getDevice<LineSensor>(LINE_DEVICE_ID);
	};

	void onUpdate() override 
	{
		// addVector(0, 60);
		// Log::info(String(line->isLine()) + "  " + String(line->getAngle()));
		
	}

	void onStart() override 
	{
		getDevice<Dribbler>(DRIB_DEVICE_ID)->start(50, false);
		Log::info("Action A start");
		// createLoopTimer(0, 2000);
		// createSimpleTimer(1, 10000);
		// startTimer(0);
		// startTimer(1);
	}

	void onStop() override 
	{
		Log::info("Action A stop");
	}

	void OnTimerEnd(Timer *timer)
	{
        Log::info(String(timer->getID()) + " with delay " + String(timer->getDelay()) + "  ->  " + String(timer->getState()));
	}
};
