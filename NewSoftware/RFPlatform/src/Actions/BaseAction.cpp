#include "BaseAction.h"

void BaseAction::startAction(Action* action)
{
	controller->addAction(action);
}

void BaseAction::finish()
{
	controller->popAction();
}

void BaseAction::addVector(float angle, int speed)
{
	controller->mVector->add(Vec2(angle, speed));
}
void BaseAction::addVector(float angle)
{
	controller->mVector->add(Vec2(angle, BASE_SPEED));
}
TimerState BaseAction::getTimerState(int timerID)
{
	return timersController->getTimerState(timerID);
}
void BaseAction::createLoopTimer(int timerID, int delay)
{
	timersController->createLoopTimer(timerID, delay);
}
void BaseAction::createSimpleTimer(int timerID, int delay)
{
	timersController->createSimpleTimer(timerID, delay);
}
void BaseAction::stopTimer(int timerID)
{
	timersController->stop(timerID);
}
void BaseAction::startTimer(int timerID)
{
	timersController->start(timerID);
}