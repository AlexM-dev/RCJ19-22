#include "Action.h"

Action::Action()
{
	controller = nullptr;
}

Action::Action(ActionsController *controller)
{
	this->controller = controller;
}

void Action::start()
{
}

void Action::update()
{
}

void Action::stop()
{
}

void Action::setActionsScontroller(ActionsController* controller)
{
	this->controller = controller;
}
