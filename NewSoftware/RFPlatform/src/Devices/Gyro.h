#pragma once

#include "Device.h"
#include "../Defines.h"
#include "../Utils/Log.h"
#include "../Utils/Utils.h"

class Gyro : public Device
{
private:
    int angle, offsetAngle;
    bool calibrated;

public:
    Gyro(int id) : Device(id)
    { 
        angle = 0;
        offsetAngle = 0;
        calibrated = false;
    }
    ~Gyro() { }

    int updateDelay() override
    {
        return 1;  // Refresh every 5ms
    }

    void collectData() override
    {
        // get data from Gyro
        if (Serial3.available())
            angle = Utils::getFormatedAngle(Serial3.read() * 2);
        if(!calibrated)
        {
            setOffsetAngle();
            calibrated = true;
        }
    }

    void connectToDevice() override
    {
        // Connect to Gyro
        Serial3.begin(115200);
        calibrated = false;
    }

    bool isConnected() override 
    {
        // Check Gyro connection 
        return Serial3;
        // return false; 
    }

    int getAngle() 
    {
        return angle - offsetAngle;    
    }

    int getOffsetAngle()
    {
        return offsetAngle;
    }

    void setOffsetAngle(int a)
    {
        offsetAngle = a;
    }

    void setOffsetAngle()
    {
        offsetAngle = angle;
    }    
};
