#include "Core.h"


Core::~Core()
{
    delete actionsController;
    delete devicesController;
    delete buttonsController;
    delete platform;
}

void Core::lineCorrection()
{
    LineSensor *sensor = devicesController->getDevice<LineSensor*>(LINE_DEVICE_ID);
    if(!sensor->isLine())
        return;

    int angle = sensor->getAngle();
    angle = Utils::getFormatedAngle(angle + 180);

    if(angle == 90 && mVector->x < 0){
        mVector->x = -mVector->x;
        mVector->y = mVector->y;
    }
    else if(angle == -90 && mVector->x > 0)
    {
        mVector->x = -mVector->x;
        mVector->y = mVector->y;
    }
    else if(angle == 0 && mVector->y > 0)
    {
        mVector->y = -mVector->y;
        mVector->x = mVector->x;
    }
    else if(angle == 180 && mVector->y < 0)
    {
        mVector->y = -mVector->y;
        mVector->x = mVector->x;
    }

    // mVector->setTo(Vec2(angle, BASE_SPEED));
}