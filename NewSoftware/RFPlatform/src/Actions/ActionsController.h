#pragma once

#include "Action.h"
#include "../Devices/DevicesController.h"
#include "../Utils/Vec2.h"
#include "../Defines.h"
#include "../Utils/Log.h"

class ActionsController
{
private:
	Action *actions[ ACTIONS_STACK_SIZE ];
	Action *actionToAdd;
	
	int curAction;
	bool isPopAction;

	void pop();
	void add();

public:
	DevicesController *devices;
	Vec2 *mVector;

	ActionsController(DevicesController *devices, Vec2 *mVector);
	void update();
	void addAction(Action *action);
	void popAction();
};

