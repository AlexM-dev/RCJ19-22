#pragma once

#include "Action.h"
#include "ActionsController.h"
#include "../Interfaces/ITimer.h"
#include "../Utils/TimersController.h"

class BaseAction : public Action, public ITimer
{
private:
	TimersController *timersController;
public:
	BaseAction(ActionsController* controller) : Action(controller)
	{
		timersController = new TimersController(this);
	};
	// Main action features
	void startAction(Action* action);
	void finish();
	void addVector(float angle, int speed);
	void addVector(float angle);
	void setVector(float angle, int speed);
	void setVector(float angle);

	// Action timers
	TimerState getTimerState(int timerID);
	void createLoopTimer(int timerID, int delay);
	void createSimpleTimer(int timerID, int delay);
	void stopTimer(int timerID);
	void startTimer(int timerID);

	template <typename T>
	T *getDevice(int deviceId)
	{
		return controller->devices->getDevice<T*>(deviceId);
	}

	void start() override
	{
		onStart();
	}
	void update() override
	{
		timersController->update();
		onUpdate();
	}
	void stop() override
	{
		onStop();
	}

	virtual void onStart() = 0;
	virtual void onUpdate() = 0;
	virtual void onStop() = 0;
};

