#pragma once

#include "Defines.h"
#include "Actions/ActionsController.h"
#include "Devices/DevicesController.h"
#include "Devices/ButtonsController.h"
#include "Platform.h"
#include "Utils/Vec2.h"
#include "Utils/Utils.h"
#include "Utils/Log.h"
#include "Interfaces/IButton.h"

#include "Actions/TestActionA.h"
#include "Actions/BallFollowAction.h"

class Core : public IButton
{
private:
    Vec2 *mVector;

    void lineCorrection();
public:
    ActionsController *actionsController;
    DevicesController *devicesController;
    ButtonsController *buttonsController;
    Platform *platform;
    
    ~Core();
    Core()
    {
        mVector = new Vec2();
        devicesController = new DevicesController();
        buttonsController = new ButtonsController(this);
        actionsController = new ActionsController(devicesController, mVector);
        platform = new Platform(devicesController, mVector);
        platform->init();

        Log::nl();
        Log::success("Init competed");
        Log::nl();
        Log::nl();

        actionsController->addAction(new BallFollowAction(actionsController));
    }   
    

    void update()
    {
        // Clear Move Vector
        mVector->clear();
        // Update All Devices
        devicesController->update();
        // Update All Buttons
        buttonsController->update();
        // Update Current Action
        actionsController->update();
        // Apply line correction to move vector
        lineCorrection();
        // Update platform
        platform->update();
    }

    void OnButtonClicked(Button *btn) override 
    {
        switch (btn->getID())
        {
        case BUTTON1_ID:
            if(btn->getState() == ButtonState::CLICK)
                platform->setCanMove(!platform->isCanMove());
            else if(btn->getState() == ButtonState::LONG_CLICK)
                devicesController->getDevice<Gyro*>(GYRO_DEVICE_ID)->setOffsetAngle();
            break;
        }
    }
};

