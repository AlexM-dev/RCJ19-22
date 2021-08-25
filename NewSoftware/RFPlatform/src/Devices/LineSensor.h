#pragma once

#include "Device.h"
#include "../Defines.h"
#include "../Utils/Log.h"

class LineSensor : public Device
{
private:
    int angle, iterations;
    bool line;
    
public:
    LineSensor(int id) : Device(id)
    {
        line = false;
        angle = 0;
        iterations = 0;
    }
    ~LineSensor() { }

    int updateDelay() override
    {
        return 3;  // Refresh every 3ms
    }

    void collectData() override
    { 
        if(Serial1.available())
        {
            int a = Serial1.read();

            if(!line)
            {
                if(a == 3 && analogRead(LEFT_SONAR_PIN) < 35)
                    angle = -90;
                else if(a == 1 && analogRead(RIGHT_SONAR_PIN) < 35)
                    angle = 90;
                else if(a == 0)
                    angle = 0;
                else if(a == 2)
                    angle = 180;
            }

            if(a > 0 && a < 5)
            {
                line = true;
                iterations = 0;
            }
            else 
            {
                if(iterations > 50)
                    line = false;
                else
                    iterations++;
            }
        }
    }

    void connectToDevice() override
    {
        Serial1.begin(115200);
    }
    bool isConnected() override 
    {
        return Serial1;
        // return false;
    }

    int getAngle()
    {
        return angle;
    }
    bool isLine()
    {
        return line;
    }  
};
