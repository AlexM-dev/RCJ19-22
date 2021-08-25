#pragma once

#include "Defines.h"
#include "Devices/DevicesController.h"
#include "Devices/Gyro.h"
#include "Utils/Vec2.h"
#include "Utils/Utils.h"
#include "Utils/Log.h"

class Platform 
{
private:
    // Platform parts variables
    Gyro *gyro;
    DevicesController *devicesController;
    int getRobotAngle();

    // Movement variables
    Vec2 *moveVector;
    int currentSpeed;
    bool canMove;
    void updateSpeed();
    
    // Rotation stabilization variables
    bool stabilizationEnabled;
    int targetAngle, rotationOldError, rotationI, rotationK;
    unsigned long rotationTime;
    void updateRotation();
    
    // Hardware update
    void runMotor(int motorIndex, int pwmSpeed);
    void updateMotors();

public:
    Platform(DevicesController *controller, Vec2 *vec);

    void init();
    void update();
    void setCanMove(bool b);
    bool isCanMove();
    void setStabilizationEnabled(bool enabled);
    bool isStabilizationEnabled();
    void setTargetAngle(int angle);
};