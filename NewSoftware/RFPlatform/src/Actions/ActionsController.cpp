#include "ActionsController.h"

void ActionsController::pop()
{
	isPopAction = false;
	if (curAction <= -1)
		return;
	actions[curAction]->stop();
	curAction--;
	if (curAction < 0)
		return;
	actions[curAction]->start();
}

void ActionsController::add()
{
	if (curAction >= ACTIONS_STACK_SIZE - 1)
	{
		actionToAdd = nullptr;
		return;
	}
	actionToAdd->setActionsScontroller(this);
	if (curAction >= 0)
		actions[curAction]->stop();
	curAction++;
	actions[curAction] = actionToAdd;
	actions[curAction]->start();
	actionToAdd = nullptr;
}

ActionsController::ActionsController(DevicesController *devices, Vec2 *mVector)
{
	this->devices = devices;
	this->mVector = mVector;

	actionToAdd = nullptr;
	curAction = -1;
	isPopAction = false;

	Log::nl();
	Log::success("Action controller created");
	Log::info("     Action stack size is " + String(ACTIONS_STACK_SIZE));
	Log::info("     Creating actions stack...");

	for (int i = 0; i < ACTIONS_STACK_SIZE; ++i)
		actions[i] = nullptr;
}

void ActionsController::update()
{
	if (isPopAction)
		pop();
	if (actionToAdd != nullptr)
		add();

	if (curAction < 0 || curAction >= ACTIONS_STACK_SIZE)
		return;

	actions[curAction]->update();
}

void ActionsController::addAction(Action *action)
{
	Log::info("Action Controller: Starting new Action");
	actionToAdd = action;
}

void ActionsController::popAction()
{
	isPopAction = true;
}
