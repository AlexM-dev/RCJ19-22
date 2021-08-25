#pragma once

class ActionsController;

class Action
{
public:
	ActionsController* controller;

	Action();
	Action(ActionsController *controller);
	
	virtual void start();
	virtual void update();
	virtual void stop();

	void setActionsScontroller(ActionsController *controller);
};

